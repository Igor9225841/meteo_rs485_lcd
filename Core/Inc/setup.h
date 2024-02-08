/*
 * setup.h
 *
 *  Created on: 08.06.2023 �.
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
//����������� ������ ���������� freemodbus
#include "mb.h"
#include "mbport.h"
#include "mt_port.h"

#endif /* INC_SETUP_H_ */

void Init(void);							// �������������

void ledOn(void);							// ��������� ����������
void ledOff(void);							// ���������� ����������
void ledTog(void);							// ������������ ��������� ����������
void rs485On(void);							// �������� ������ RS-485 (������� �������)
void rs485Off(void);						// ����� ������ RS-485 (������ �������)

#define REG_INPUT_START 3001				// ��������� ����� ��������� ModBusRTU
#define REG_INPUT_NREGS 8					// ���������� ��������� ��� ������


