/*
 * setup.c
 *
 *  Created on: 08.06.2023 �.
 *      Author: Igor
 */
#include "setup.h"

extern char msg[30];								// ������������ ������ �� ����� UART

extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart2;
// ������������� ��������
void Init(void)
{
	sprintf(msg, "\r\nStart init OK\r\n");
	UART_TX_Str((uint8_t*)msg);
// ����� ������� 4 ��� ������� ���������� ������� ����� ����������� ��������
	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH1);
	LL_TIM_EnableCounter(TIM4);
	LL_TIM_EnableIT_UPDATE(TIM4);  				// ���������� ����������

	LCD_ini();
	sprintf(msg, "LCD init OK\r\n");
	UART_TX_Str((uint8_t*)msg);

	BMP280_Init();
	sprintf(msg, "\r\nBMP280 init OK\r\n");
	UART_TX_Str((uint8_t*)msg);

	ccs811_init();

//	LL_mDelay(2000);
	hdc1080_Setup();
	sprintf(msg, "\r\nHDC1080 init OK\r\n");
	UART_TX_Str((uint8_t*)msg);

// ��������� UART2 � TIM3 ��� ������ ModBus RTU
	MT_PORT_SetTimerModule(&htim3);
	MT_PORT_SetUartModule(&huart2);

	eMBErrorCode eStatus;
	eStatus = eMBInit(MB_RTU, 0x01, 0, 9600, MB_PAR_NONE);	// 0x0A ����� Slave ����������������
	eStatus = eMBEnable();

	if (eStatus != MB_ENOERR)
	{
	    // Error handling
	}

	//��������� ������ RS-485
	rs485Off();

	sprintf(msg, "\r\n\r\nInit OK\r\n");
	UART_TX_Str((uint8_t*)msg);
}

// ������� ������������ ��������� ����������
void ledOn(void)
{
	LL_GPIO_SetOutputPin(Led_GPIO_Port, Led_Pin);
}

void ledOff(void)
{
	LL_GPIO_ResetOutputPin(Led_GPIO_Port, Led_Pin);
}

void ledTog(void)
{
	LL_GPIO_TogglePin(Led_GPIO_Port, Led_Pin);
}

// ������� ������������ ��������/����� RS485
void rs485On(void)
{
	LL_GPIO_SetOutputPin(TxRxRs485_GPIO_Port, TxRxRs485_Pin);
}

void rs485Off(void)
{
	LL_GPIO_ResetOutputPin(TxRxRs485_GPIO_Port, TxRxRs485_Pin);
}






