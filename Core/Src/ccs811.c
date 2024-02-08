/*
 * ccs811.c
 *
 *  Created on: 17 февр. 2023 г.
 *      Author: Игорь
 */

#include "ccs811.h"

char msg_ccs811[50];					// Произвольное сообщение

static const uint8_t CCS811_ADDR = 0x5A << 1;	// Используется 7 битный адрес

uint16_t baseline;

// Прототипы******************************************************
uint16_t GetBaseline(void);
void SetBaseline(uint16_t baseline);

// Инициализация**************************************************
void ccs811_init(void)
{
	uint8_t ccs811_Data = 0;

// Программный сброс датчика
	uint8_t seq[] = {0x11, 0xE5, 0x72, 0x8A};
	size_t number_seq = sizeof(seq) / sizeof(seq[0]);
	I2Cx_WriteDataX(CCS811_ADDR, CCS811_SW_RESET, seq, number_seq);
	LL_mDelay(500);

// Получение ID датчика
	ccs811_Data = I2Cx_ReadData(CCS811_ADDR, CCS811_HW_ID);
	sprintf(msg_ccs811, "\r\nCCS811 init OK\r\nCCS811 ID 0x%x\r\n\r\n", ccs811_Data);
	UART_TX_Str((uint8_t*)msg_ccs811);

// Старт датчика
	I2Cx_WriteReg(CCS811_ADDR, CCS811_BOOTLOADER_APP_START);
	LL_mDelay(300);

// Установка Meas Mode, постоянное измерение раз в 10 секунд
	I2Cx_WriteData(CCS811_ADDR, CCS811_MEAS_MODE, CCS811_DRIVE_MODE_10SEC);
	LL_mDelay(100);

// Получение ID датчика
	ccs811_Data = I2Cx_ReadData(CCS811_ADDR, CCS811_MEAS_MODE);
	sprintf(msg_ccs811, "\r\nCCS811 Meas_Mode: 0x%x\r\n\r\n", ccs811_Data);
	UART_TX_Str((uint8_t*)msg_ccs811);

// Получение Baseline при включении (требуется включать в чистом воздухе
	baseline = GetBaseline();
}

void ccs811_start_measurement(uint16_t* co2, uint16_t* voc, int8_t t_in, uint16_t h_in)
{
// Востановление срединной линии
	SetBaseline(baseline);

// Компенсация по влажности и температуре
	uint16_t hum_conv = h_in * 512;
	uint16_t temp_conv = (t_in + 25) * 512;

	uint8_t t_h[] = {
			(uint8_t)((hum_conv >> 8) & 0xFF), (uint8_t)(hum_conv & 0xFF),
		    (uint8_t)((temp_conv >> 8) & 0xFF), (uint8_t)(temp_conv & 0xFF)};
	size_t number_t_h = sizeof(t_h) / sizeof(t_h[0]);

	I2Cx_WriteDataX(CCS811_ADDR, CCS811_SW_RESET, t_h, number_t_h);

// Проверка получения данных от датчика
	uint8_t receive_data[8];	// Проверка получения данных от датчика
	size_t number = sizeof(receive_data) / sizeof(receive_data[0]);

	I2Cx_ReadDataX(CCS811_ADDR, CCS811_ALG_RESULT_DATA, receive_data, number);

	*co2= ((uint16_t)receive_data[0] << 8) | ((uint16_t)receive_data[1]);
	*voc= ((uint16_t)receive_data[2] << 8) | ((uint16_t)receive_data[3]);
}

// Получение данных baseline
uint16_t GetBaseline(void)
{
	uint8_t buf[2];
	size_t number = sizeof(buf) / sizeof(buf[0]);

	I2Cx_ReadDataX(CCS811_ADDR, CCS811_BASELINE, buf, number);
	return ((uint16_t)buf[0] << 8) | ((uint16_t)buf[1]);
}

// Запись данных baseline полученных при старте в мк
void SetBaseline(uint16_t baseline)
{
	uint8_t buf[] = {(uint8_t)((baseline >> 8) & 0xFF),
	                   (uint8_t)(baseline & 0xFF)};
	size_t number = sizeof(buf) / sizeof(buf[0]);
	I2Cx_WriteDataX(CCS811_ADDR, CCS811_SW_RESET, buf, number);
}





