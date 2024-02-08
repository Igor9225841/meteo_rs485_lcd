/*
 * loop.c
 *
 *  Created on: 08.06.2023 �.
 *      Author: Igor
 *  ��������: ��������� ����������� �� stm32f103c8t6, ����� LCD1602.
 *  ����������� ������� BMP280 � CJMCU8118.
 *  1. ��� ������� �������� �� ���������� I2C1.
 *  1.1. ����� BMP280- 0x76.
 *  1.2. ����� CCS811- 0x5A.
 *  1.3. ����� HDC1080-0x40.
 *  2. TIM4 ������������ ��� ������� ������� ������� �������� �
 *     ��������� ���������� �������� � UART1.
 *  3. TIM3 ������������ ��� ����������� ������ rs-485.
 *  4. �������� ModBus RTU �� ���������� freemodbus.
 *  5. ��������� ������ �� ����� �� �������������.
 *  6. ���������� �������: ��� ���������� ������������ ��������
 *     ����������� ��������� ������ �� 5-� ��������, ������
 *     ������������ ���������� � ������� ������� �������� ��������.
 *
 */

#include <stdio.h>
#include "loop.h"
#include "uart_usb.h"
#include "setup.h"
#include "filter.h"
#include "iwdg.h"

char msg[30];					// ������������ ������ �� ����� UART
volatile uint8_t flag_Tim4 = 0;	// ���� ����������� ���������� ��� ������� ������� 10 ������
uint16_t data = 0;
char rx_str[30];
char tx_str[30];

char dsg_str_t[] = {"T="};		// ����������� ���������� ����������� (designation)
char dim_str_t[] = {"C "};		// ����������� ���������� ����������� (dimension)
char dsg_str_p[] = {"P="};		// ����������� ���������� �������� (designation)
char dim_str_p[] = {"hPa"};		// ����������� ���������� �������� (dimension)
char dsg_str_voc[] = {"VO="};	// ����������� ���������� ��������� (designation)
char dim_str_voc[] = {"ppb"};	// ����������� ���������� ��������� (designation)
char dsg_str_co2[] = {"CO2="};	// ����������� ���������� ��������� (designation)
char dim_str_co2[] = {"ppm"};	// ����������� ���������� ��������� (dimension)
char dsg_str_h[] = {"H="};		// ����������� ���������� ��������� (designation)
char dim_str_h[] = {"%"};		// ����������� ���������� ��������� (dimension)

char tx_str_t[16];				// ������ ����������� ��� ��������� � UART
char tx_str_p[16];				// ������ �������� ��� ��������� � UART
char tx_str_voc[16];			// ������ VOC ��� ��������� � UART
char tx_str_co2[16];			// ������ CO2 ��� ��������� � UART
char tx_str_h[16];				// ������ ��������� ��� ��������� � UART

//�������������� ������ �� ��������
int8_t raw_val_t_bmp280 = 25;	// ����������� � ��������� � �� BPM280
int8_t raw_val_t_hdc = 30;		// ����������� � ��������� � �� HDC1080
int8_t raw_val_t_ccs = 22;		// ����������� � ��������� � �� HDC1080
uint16_t raw_val_p_atm = 1000; 	// ����������� �������� � ���
uint8_t raw_val_h_hdc = 40;		// ��������� � ���������� %
uint16_t raw_val_voc = 1;	// �������� ������� 0-1187 ppb
uint16_t raw_val_co2 = 400;	// ���������� CO2 400-8192 ppm

int8_t t_bmp280 = 20;			// ����������� � ��������� � �� BPM280
int8_t t_hdc = 21;				// ����������� � ��������� � �� HDC1080
int8_t t_ccs = 22;				// ����������� � ��������� � �� HDC1080
uint16_t p_atm = 1012; 			// ����������� �������� � ���
uint8_t h_hdc = 50;				// ��������� � ���������� %
uint16_t voc = 1435;			// �������� ������� 0-1187 ppb
uint16_t co2 = 1843;			// ���������� CO2 400-8192 ppm

uint16_t buffer_t_bmp280[NUM_READ_MEDIAN];	 // ����� ������� bmp280
uint16_t buffer_t_hdc[NUM_READ_MEDIAN];  	// ����� ������� hdc
uint16_t buffer_t_ccs[NUM_READ_MEDIAN]; 	 // ����� ������� ccs
uint16_t buffer_p_atm[NUM_READ_MEDIAN]; 	 // ����� ������� p_atm
uint16_t buffer_h_hdc[NUM_READ_MEDIAN]; 	 // ����� ������� h_hdc
uint16_t buffer_voc[NUM_READ_MEDIAN];   	 // ����� ������� voc
uint16_t buffer_co2[NUM_READ_MEDIAN]; 		 // ����� ������� co2

uint16_t vals_t_bmp280[NUM_READ_AVERAGE];	 // ����� �������� bmp280
uint16_t vals_t_hdc[NUM_READ_AVERAGE]; 		 // ����� �������� hdc
uint16_t vals_t_ccs[NUM_READ_AVERAGE]; 		 // ����� �������� ccs
uint16_t vals_p_atm[NUM_READ_AVERAGE]; 		 // ����� �������� p_atm
uint16_t vals_h_hdc[NUM_READ_AVERAGE]; 		 // ����� �������� h_hdc
uint16_t vals_voc[NUM_READ_AVERAGE];  		 // ����� �������� voc
uint16_t vals_co2[NUM_READ_AVERAGE]; 		 // ����� �������� co2

uint8_t count_median = 0;			//������� �������
uint8_t t_middle = 0;				//������� ��������


// ������ �������� ModBus RTU
static USHORT usRegInputStart = REG_INPUT_START;
static USHORT usRegInputBuf[REG_INPUT_NREGS] = {'M', 'o', 'd', 'b', 'u', 's', 0, 0};
uint16_t time_rs485 = 0;		// ���������� ��� ������� ������� ������

// ���������� ��� ������ � lcd1602 �� i2c
uint16_t i;
char str01[6];

// ��������� �������
void SendData(void);			// �������� ������ uart
void ReciveData(void);			// ��������� ������ �� ��������
void FilterData(void);			// ���������� ������ �� ��������

void Rs485Data(void);			// ��������� ���������� �� ModBus RTU �������

/*********************************************
 *       �������� ����
*********************************************/
void Loop(void)
{
	while(1)
	{
		Rs485Data();

		if(flag_Tim4 == 1)
		{
			HAL_IWDG_Refresh(&hiwdg);		// ����� IWDG
			ledTog();
			flag_Tim4 = 0;

			ReciveData();
			FilterData();
			SendData();
			ledTog();
		}
	}
}

// ��������� ���������� ��� ������� 4 ������ (������ ��������� ��������� ����������)
void Callback_Tim4(void)
{
	flag_Tim4 = 1;
}

// �������� ������ uart1->usb
void SendData(void)
{
	// ������������� ������ � ������
	sprintf(tx_str_t, "\r\n%s%-2i%s\r\n", dsg_str_t, t_hdc, dim_str_t);
	sprintf(tx_str_p, "%s%-4u%s\r\n", dsg_str_p, p_atm, dim_str_p);
	sprintf(tx_str_voc, "%s%-4u%s\r\n", dsg_str_voc, voc, dim_str_voc);
	sprintf(tx_str_co2, "%s%-4u%s\r\n\n", dsg_str_co2, co2, dim_str_co2);
	sprintf(tx_str_h, "%s%-2u%s\r\n", dsg_str_h, h_hdc, dim_str_h);

	//������ ���������� UART2 (RS485/ModBus) �� ����� �������� ������ �� I2C � UART1
	NVIC_DisableIRQ(USART2_IRQn);

	// ��������� ������ � UART1
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

//���������� ���������� UART2 (RS485/ModBus)
	NVIC_EnableIRQ(USART2_IRQn);
}

// ��������� ������ �� ��������
void ReciveData(void)
{
//������ ���������� UART2 (RS485/ModBus) �� ����� ������ �������� �� I2C
	NVIC_DisableIRQ(USART2_IRQn);
	raw_val_t_bmp280 = BMP280_ReadTemperature();
	raw_val_p_atm = BMP280_ReadPressure();
	hdc1080_start_measurement(&raw_val_t_hdc, &raw_val_h_hdc);
	ccs811_start_measurement(&raw_val_co2, &raw_val_voc, t_bmp280, h_hdc);
//���������� ���������� UART2 (RS485/ModBus)
	NVIC_EnableIRQ(USART2_IRQn);
}

//���������� ������ �� ��������
void FilterData(void)
{
// ��� �������� CO2 � TVOC ������� ������������� ���������� �������, ����� �������
	t_bmp280 = findMedianN(runMiddleArifm(raw_val_t_bmp280, vals_t_bmp280), buffer_t_bmp280);
	p_atm = findMedianN(runMiddleArifm(raw_val_p_atm, vals_p_atm), buffer_p_atm);
	t_hdc = findMedianN(runMiddleArifm(raw_val_t_hdc, vals_t_hdc), buffer_t_hdc);
	h_hdc = findMedianN(runMiddleArifm(raw_val_h_hdc, vals_h_hdc), buffer_h_hdc);
	co2 = findMedianN(runMiddleArifm(raw_val_co2, vals_co2), buffer_co2);
	voc = findMedianN(runMiddleArifm(raw_val_voc, vals_voc), buffer_voc);
}

// ������� �������� � �������� ModBus
// � ��������� ��� �������� ������� �����, ��������� � ������� ��������� ������� - � � � ��
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

// Callback'� ��� ������ ��� ����������� ��������������� ��������
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

/*������ �������� � �������*/
eMBErrorCode eMBRegHoldingCB(UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs,
                             eMBRegisterMode eMode)
{
//������ � ������� �� �������� � �������� ����, ������ � ������� �� *pucRegBuffer
  return MB_ENOREG;
}

/*������ �������� ���� � �������*/
eMBErrorCode eMBRegCoilsCB(UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,
                           eMBRegisterMode eMode)
{
  return MB_ENOREG;
}

/*������ ���������� ������*/
eMBErrorCode eMBRegDiscreteCB(UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete)
{
  return MB_ENOREG;
}
