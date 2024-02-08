/*
 * loop.c
 *
 *  Created on: 08.06.2023 г.
 *      Author: Igor
 *  Описание: программа метеостанци на stm32f103c8t6, эклан LCD1602.
 *  Применяемые датчики BMP280 и CJMCU8118.
 *  1. Все датчики работают по интерфейсу I2C1.
 *  1.1. Адрес BMP280- 0x76.
 *  1.2. Адрес CCS811- 0x5A.
 *  1.3. Адрес HDC1080-0x40.
 *  2. TIM4 используется для задания периода опросов датчиков и
 *     выведения измеренных значений в UART1.
 *  3. TIM3 используется для обеспечения работы rs-485.
 *  4. Протокол ModBus RTU на библиотеке freemodbus.
 *  5. Выведение данных на экран не предусмотрено.
 *  6. Фильтрация сигнала: для фильтрации значительных выбросов
 *     применяется медианный фильтр из 5-х значений, первым
 *     производится усреднение с помощью фильтра бегущего среднего.
 *
 */

#include <stdio.h>
#include "loop.h"
#include "uart_usb.h"
#include "setup.h"
#include "filter.h"
#include "iwdg.h"

char msg[30];					// Произвольная строка на вывод UART
volatile uint8_t flag_Tim4 = 0;	// Флаг обработчика прерывания для отсчета периода 10 секунд
uint16_t data = 0;
char rx_str[30];
char tx_str[30];

char dsg_str_t[] = {"T="};		// Обозначение измеряемой температуры (designation)
char dim_str_t[] = {"C "};		// Размерность измеряемой температуры (dimension)
char dsg_str_p[] = {"P="};		// Обозначение измеряемой давления (designation)
char dim_str_p[] = {"hPa"};		// Размерность измеряемой давления (dimension)
char dsg_str_voc[] = {"VO="};	// Обозначение измеряемой влажности (designation)
char dim_str_voc[] = {"ppb"};	// Обозначение измеряемой влажности (designation)
char dsg_str_co2[] = {"CO2="};	// Обозначение измеряемой влажности (designation)
char dim_str_co2[] = {"ppm"};	// Размерность измеряемой влажности (dimension)
char dsg_str_h[] = {"H="};		// Обозначение измеряемой влажности (designation)
char dim_str_h[] = {"%"};		// Размерность измеряемой влажности (dimension)

char tx_str_t[16];				// Строка температуры для выведения в UART
char tx_str_p[16];				// Строка давления для выведения в UART
char tx_str_voc[16];			// Строка VOC для выведения в UART
char tx_str_co2[16];			// Строка CO2 для выведения в UART
char tx_str_h[16];				// Строка влажности для выведения в UART

//Необработанные данные от датчиков
int8_t raw_val_t_bmp280 = 25;	// Температура в помещении С от BPM280
int8_t raw_val_t_hdc = 30;		// Температура в помещении С от HDC1080
int8_t raw_val_t_ccs = 22;		// Температура в помещении С от HDC1080
uint16_t raw_val_p_atm = 1000; 	// Атмосферное давление в гПа
uint8_t raw_val_h_hdc = 40;		// Влажность в помещениии %
uint16_t raw_val_voc = 1;	// Качаство воздуха 0-1187 ppb
uint16_t raw_val_co2 = 400;	// Содержание CO2 400-8192 ppm

int8_t t_bmp280 = 20;			// Температура в помещении С от BPM280
int8_t t_hdc = 21;				// Температура в помещении С от HDC1080
int8_t t_ccs = 22;				// Температура в помещении С от HDC1080
uint16_t p_atm = 1012; 			// Атмосферное давление в гПа
uint8_t h_hdc = 50;				// Влажность в помещениии %
uint16_t voc = 1435;			// Качаство воздуха 0-1187 ppb
uint16_t co2 = 1843;			// Содержание CO2 400-8192 ppm

uint16_t buffer_t_bmp280[NUM_READ_MEDIAN];	 // буфер медианы bmp280
uint16_t buffer_t_hdc[NUM_READ_MEDIAN];  	// буфер медианы hdc
uint16_t buffer_t_ccs[NUM_READ_MEDIAN]; 	 // буфер медианы ccs
uint16_t buffer_p_atm[NUM_READ_MEDIAN]; 	 // буфер медианы p_atm
uint16_t buffer_h_hdc[NUM_READ_MEDIAN]; 	 // буфер медианы h_hdc
uint16_t buffer_voc[NUM_READ_MEDIAN];   	 // буфер медианы voc
uint16_t buffer_co2[NUM_READ_MEDIAN]; 		 // буфер медианы co2

uint16_t vals_t_bmp280[NUM_READ_AVERAGE];	 // буфер среднего bmp280
uint16_t vals_t_hdc[NUM_READ_AVERAGE]; 		 // буфер среднего hdc
uint16_t vals_t_ccs[NUM_READ_AVERAGE]; 		 // буфер среднего ccs
uint16_t vals_p_atm[NUM_READ_AVERAGE]; 		 // буфер среднего p_atm
uint16_t vals_h_hdc[NUM_READ_AVERAGE]; 		 // буфер среднего h_hdc
uint16_t vals_voc[NUM_READ_AVERAGE];  		 // буфер среднего voc
uint16_t vals_co2[NUM_READ_AVERAGE]; 		 // буфер среднего co2

uint8_t count_median = 0;			//Счетчик медианы
uint8_t t_middle = 0;				//Счетчик среднего


// Данные реистров ModBus RTU
static USHORT usRegInputStart = REG_INPUT_START;
static USHORT usRegInputBuf[REG_INPUT_NREGS] = {'M', 'o', 'd', 'b', 'u', 's', 0, 0};
uint16_t time_rs485 = 0;		// Переменная для отсчета времени работы

// Переменные для работы с lcd1602 по i2c
uint16_t i;
char str01[6];

// Прототипы функций
void SendData(void);			// Отправка данных uart
void ReciveData(void);			// Получение данных от датчиков
void FilterData(void);			// фильтрация данных от датчиков

void Rs485Data(void);			// Обработка получаемой по ModBus RTU команды

/*********************************************
 *       ОСНОВНОЙ ЦИКЛ
*********************************************/
void Loop(void)
{
	while(1)
	{
		Rs485Data();

		if(flag_Tim4 == 1)
		{
			HAL_IWDG_Refresh(&hiwdg);		// Сброс IWDG
			ledTog();
			flag_Tim4 = 0;

			ReciveData();
			FilterData();
			SendData();
			ledTog();
		}
	}
}

// Обработка прерывания для отсчета 4 секунд (период изменения состояния светодиода)
void Callback_Tim4(void)
{
	flag_Tim4 = 1;
}

// Отправка данных uart1->usb
void SendData(void)
{
	// Преобразоване данных в строку
	sprintf(tx_str_t, "\r\n%s%-2i%s\r\n", dsg_str_t, t_hdc, dim_str_t);
	sprintf(tx_str_p, "%s%-4u%s\r\n", dsg_str_p, p_atm, dim_str_p);
	sprintf(tx_str_voc, "%s%-4u%s\r\n", dsg_str_voc, voc, dim_str_voc);
	sprintf(tx_str_co2, "%s%-4u%s\r\n\n", dsg_str_co2, co2, dim_str_co2);
	sprintf(tx_str_h, "%s%-2u%s\r\n", dsg_str_h, h_hdc, dim_str_h);

	//Запрет прерываний UART2 (RS485/ModBus) на время передачи данных по I2C и UART1
	NVIC_DisableIRQ(USART2_IRQn);

	// Выведение данных в UART1
	UART_TX_Str((uint8_t*)tx_str_t);
	UART_TX_Str((uint8_t*)tx_str_p);
	UART_TX_Str((uint8_t*)tx_str_voc);
	UART_TX_Str((uint8_t*)tx_str_co2);
	UART_TX_Str((uint8_t*)tx_str_h);

	LCD_SetPos(0, 0);
	sprintf(tx_str_t, "%2i%s\r\n", t_hdc, dim_str_t);
	LCD_String(tx_str_t);

	LCD_SetPos(5, 0);
	sprintf(tx_str_h, "%2u%s\r\n", h_hdc, dim_str_h);
	LCD_String(tx_str_h);

	LCD_SetPos(9, 0);
	sprintf(tx_str_p, "%4u%s\r\n", p_atm, dim_str_p);
	LCD_String(tx_str_p);

	LCD_SetPos(0, 1);
	sprintf(tx_str_voc, "%s%-4u\r\n", dsg_str_voc, voc);
	LCD_String(tx_str_voc);

	LCD_SetPos(8, 1);
	sprintf(tx_str_co2, "%s%-4u\r\n\n", dsg_str_co2, co2);
	LCD_String(tx_str_co2);

//Разрешение прерываний UART2 (RS485/ModBus)
	NVIC_EnableIRQ(USART2_IRQn);
}

// Получение данных от датчиков
void ReciveData(void)
{
//Запрет прерываний UART2 (RS485/ModBus) на время опроса датчиков по I2C
	NVIC_DisableIRQ(USART2_IRQn);
	raw_val_t_bmp280 = BMP280_ReadTemperature();
	raw_val_p_atm = BMP280_ReadPressure();
	hdc1080_start_measurement(&raw_val_t_hdc, &raw_val_h_hdc);
	ccs811_start_measurement(&raw_val_co2, &raw_val_voc, t_bmp280, h_hdc);
//Разрешение прерываний UART2 (RS485/ModBus)
	NVIC_EnableIRQ(USART2_IRQn);
}

//Фильтрация данных от датчиков
void FilterData(void)
{
// Для датчиков CO2 и TVOC сначала расчитывается скользящее среднее, затем медиана
	t_bmp280 = findMedianN(runMiddleArifm(raw_val_t_bmp280, vals_t_bmp280), buffer_t_bmp280);
	p_atm = findMedianN(runMiddleArifm(raw_val_p_atm, vals_p_atm), buffer_p_atm);
	t_hdc = findMedianN(runMiddleArifm(raw_val_t_hdc, vals_t_hdc), buffer_t_hdc);
	h_hdc = findMedianN(runMiddleArifm(raw_val_h_hdc, vals_h_hdc), buffer_h_hdc);
	co2 = findMedianN(runMiddleArifm(raw_val_co2, vals_co2), buffer_co2);
	voc = findMedianN(runMiddleArifm(raw_val_voc, vals_voc), buffer_voc);
}

// Заносим значения в регистры ModBus
// В последние два регистра заносим время, прошедшее с момента включения питания - в с и мс
void Rs485Data(void)
{
	 eMBPoll();
	 time_rs485 = HAL_GetTick() / 60000 ;
	 usRegInputBuf[REG_INPUT_NREGS - 7] =  time_rs485;
	 usRegInputBuf[REG_INPUT_NREGS - 6] =  time_rs485/60;
	 usRegInputBuf[REG_INPUT_NREGS - 5] =  t_hdc;
	 usRegInputBuf[REG_INPUT_NREGS - 4] =  h_hdc;
	 usRegInputBuf[REG_INPUT_NREGS - 3] =  voc;
	 usRegInputBuf[REG_INPUT_NREGS - 2] =  co2;
	 usRegInputBuf[REG_INPUT_NREGS - 1] =  p_atm;
}

// Callback'и для вызова при поступлении соответствующих запросов
eMBErrorCode eMBRegInputCB(UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs)
{
	eMBErrorCode eStatus = MB_ENOERR;
	int iRegIndex;

	if ((usAddress >= REG_INPUT_START) &&
		(usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS))
	{
	  iRegIndex = (int)(usAddress - usRegInputStart);

	  while(usNRegs > 0)
	  {
		  *pucRegBuffer++ = (unsigned char)(usRegInputBuf[iRegIndex] >> 8);
		  *pucRegBuffer++ = (unsigned char)(usRegInputBuf[iRegIndex] & 0xFF);

		  iRegIndex++;
		  usNRegs--;
	  }
	}
	else
	{
	  eStatus = MB_ENOREG;
	}
return eStatus;
}

/*Запись значения в регистр*/
eMBErrorCode eMBRegHoldingCB(UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs,
                             eMBRegisterMode eMode)
{
//Запись в регистр по аналогии с функцией выше, писать в регистр из *pucRegBuffer
  return MB_ENOREG;
}

/*Запись битового поля в регистр*/
eMBErrorCode eMBRegCoilsCB(UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,
                           eMBRegisterMode eMode)
{
  return MB_ENOREG;
}

/*Чтение дискретных входов*/
eMBErrorCode eMBRegDiscreteCB(UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete)
{
  return MB_ENOREG;
}
