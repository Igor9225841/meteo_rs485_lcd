/*
 * uart_usb.c
 *
 *  Created on: Feb 10, 2023
 *      Author: Игорь
 */

#include "uart_usb.h"

void UART_TX_Str(uint8_t* dt)
{
	uint8_t ind = 0;

	while ((*(uint8_t*) (dt+ind) != '\0'))
	{
		while (!LL_USART_IsActiveFlag_TXE(USART1)) {}
		LL_USART_TransmitData8(USART1,*(uint8_t*) (dt+ind));

		ind++;
	}
	return;
}
