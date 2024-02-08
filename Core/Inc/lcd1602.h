/*
 * lcd1602.h
 *
 *  Created on: Feb 11, 2023
 *      Author: »горь
 */

#ifndef INC_LCD1602_H_
#define INC_LCD1602_H_
//------------------------------------------------
#include "stm32f1xx.h"
#include "stm32f1xx_ll_utils.h"
#include "main.h"
//------------------------------------------------
#define e_set() LCD_WriteByteI2CLCD(portlcd|=0x04)  //установка линии ≈ в 1
#define e_reset() LCD_WriteByteI2CLCD(portlcd&=~0x04) //установка линии ≈ в 0
#define rs_set() LCD_WriteByteI2CLCD(portlcd|=0x01) //установка линии RS в 1
#define rs_reset() LCD_WriteByteI2CLCD(portlcd&=~0x01) //установка линии RS в 0
#define setled() LCD_WriteByteI2CLCD(portlcd|=0x08) //установка линии RS в 1
#define setwrite() LCD_WriteByteI2CLCD(portlcd&=~0x02) //установка линии RS в 0
//------------------------------------------------
//void I2C_SendByteByADDR(I2C_TypeDef * i2c, uint8_t c,uint8_t addr);
void LCD_ini(void);
void LCD_Clear(void);
void LCD_SendChar(char ch);
void LCD_String(char* st);
void LCD_SetPos(uint8_t x, uint8_t y);
//------------------------------------------------



#endif /* INC_LCD1602_H_ */
