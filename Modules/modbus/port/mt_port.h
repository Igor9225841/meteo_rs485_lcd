/*
 * mt_port.h
 *
 *  Created on: Jun 5, 2023
 *      Author: Igor
 */

#ifndef MODBUS_PORT_MT_PORT_H_
#define MODBUS_PORT_MT_PORT_H_

#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
#include "stm32f1xx_hal.h"
/* Functions -----------------------------------------------------------------*/
extern void MT_PORT_SetTimerModule(TIM_HandleTypeDef* timer);
extern void MT_PORT_SetUartModule(UART_HandleTypeDef* uart);

#endif /* MODBUS_PORT_MT_PORT_H_ */
