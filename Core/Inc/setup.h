/*
 * setup.h
 *
 *  Created on: 08.06.2023 г.
 *      Author: Igor
 */

#ifndef INC_SETUP_H_
#define INC_SETUP_H_

#include "main.h"
#include <stdio.h>
#include "uart_usb.h"
#include "bmp280.h"
#include "ccs811.h"
#include "hdc1080.h"
#include "lcd1602.h"
//Подключение файлов библиотеки freemodbus
#include "mb.h"
#include "mbport.h"
#include "mt_port.h"

#endif /* INC_SETUP_H_ */

void Init(void);							// Инициализация

void ledOn(void);							// Включение светодиода
void ledOff(void);							// Выключение светодиода
void ledTog(void);							// Переключение состояния светодиода
void rs485On(void);							// Передача данных RS-485 (высоуий уровень)
void rs485Off(void);						// Прием данных RS-485 (низкий уровень)

#define REG_INPUT_START 3001				// Стартовый адрес регистров ModBusRTU
#define REG_INPUT_NREGS 8					// Количество регистров для чтения


