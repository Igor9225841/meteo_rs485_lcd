/*
 * lsd1602.c
 *
 *  Created on: Feb 11, 2023
 *      Author: �����
 */

#include "lcd1602.h"
#include "i2c_user.h"

void I2C_SendByteByADDR(I2C_TypeDef * i2c, uint8_t c,uint8_t addr)
{
	I2C_SendStart(I2C1);
	I2C_SendAdrWr(I2C1, addr);
	I2C_SendByte(I2C1, c);
	I2C_SendStop(I2C1);
}


//------------------------------------------------
char str1[100];
uint8_t portlcd;
//------------------------------------------------
__STATIC_INLINE void DelayMicro(__IO uint32_t micros)
{
	micros *=(SystemCoreClock / 1000000) / 9;
	while (micros--);
}
//------------------------------------------------
void LCD_WriteByteI2CLCD(uint8_t bt)
{
  I2C_SendByteByADDR(I2C1, bt,0x4E);
}
//------------------------------------------------
void sendhalfbyte(uint8_t c)
{
  c<<=4;
  LCD_WriteByteI2CLCD(portlcd|c);
  LCD_WriteByteI2CLCD((portlcd|=0x04)|c);
  DelayMicro(1);
  LCD_WriteByteI2CLCD((portlcd&=~0x04)|c);
  DelayMicro(50);
}
//------------------------------------------------
void sendbyte(uint8_t c, uint8_t mode)
{
	if(mode==0) rs_reset();
	else rs_set();
	uint8_t hc=0;
	hc=c>>4;
	sendhalfbyte(hc);
	sendhalfbyte(c);
}
//------------------------------------------------
void LCD_Clear(void)
{
	sendbyte(0x01,0);
	LL_mDelay(2);
}
//------------------------------------------------
void LCD_SendChar(char ch)
{
	sendbyte(ch,1);
}
//------------------------------------------------
void LCD_String(char* st)
{
	uint8_t i = 0;

	while ((*(uint8_t*) (st+i) != '\r'))
	{
		sendbyte(st[i],1);
		i++;
	}
}

//------------------------------------------------
void LCD_SetPos(uint8_t x, uint8_t y)
{
	switch(y)
	{
		case 0:
			sendbyte(x|0x80,0);
			break;
		case 1:
			sendbyte((0x40+x)|0x80,0);
			break;
		case 2:
			sendbyte((0x14+x)|0x80,0);
			break;
		case 3:
			sendbyte((0x54+x)|0x80,0);
			break;
	}
}
//------------------------------------------------
void LCD_ini(void)
{
  LL_mDelay(50);
  LCD_WriteByteI2CLCD(0);
  LL_mDelay(100);
  sendhalfbyte(0x03);
  DelayMicro(4500);
  sendhalfbyte(0x03);
  DelayMicro(4500);
  sendhalfbyte(0x03);
  DelayMicro(200);
  sendhalfbyte(0x02);
  sendbyte(0x28,0);		//����� 4 ���, 2 ����� (��� ������ �������� ������� ��� 4 �����, ����� 5�8
  sendbyte(0x0C,0);		//������� �������� (D=1), ������� ������� �� �����
  LL_mDelay(1);
  sendbyte(0x01,0);		// ������ �����
  LL_mDelay(2);
  sendbyte(0x06,0);		// ����� �����
  LL_mDelay(1);
  sendbyte(0x02,0);		//������ �� �����
  LL_mDelay(2);
  setled();//���������
  setwrite();//������
}
