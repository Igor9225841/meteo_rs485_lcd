/*
 * i2c_user.c
 *
 *  Created on: 13 февр. 2023 г.
 *      Author: Игорь
 */

#include "i2c_user.h"

//------------------------------------------------
#define I2C_REQUEST_WRITE                       0x00
#define I2C_REQUEST_READ                        0x01

//------------------------------------------------
void I2C_SendStart(I2C_TypeDef * i2c)
{
  //Disable Pos
  LL_I2C_DisableBitPOS(I2C1);							// Бит ACK управляет ACK (NACK) текущего байта, получаемого в регистре сдвига.
  LL_I2C_AcknowledgeNextData(i2c, LL_I2C_ACK);			// Разрешает модулю генерировать условие ACK после приёма байтов
  LL_I2C_GenerateStartCondition(i2c);					// Генерируем условие START
  while(!LL_I2C_IsActiveFlag_SB(i2c)){};				// Ожидание установки бита SB в регистре SR1
  (void) i2c->SR1;										// Считаем регистр SR1
}
//-------------------------------------------------

void I2C_SendAdrWr(I2C_TypeDef * i2c, uint8_t addr)
{
  LL_I2C_TransmitData8(i2c, addr | I2C_REQUEST_WRITE);	// Отправляем адрес устройства в шину
  while(!LL_I2C_IsActiveFlag_ADDR(i2c)){};				// Ожидание установки бита ADDR в регистре SR1, окончание передачи адреса SLAVE в шину
  LL_I2C_ClearFlag_ADDR(i2c);							// Очистим флаг ADDR
}
//------------------------------------------------

void I2C_SendByte(I2C_TypeDef * i2c, uint8_t c)
{
  LL_I2C_TransmitData8(i2c, c);							// Отправляем данные в шину
  while(!LL_I2C_IsActiveFlag_TXE(i2c)){};				// Ожидание установки бита TXE, очистки регистра DR
}
//------------------------------------------------

void I2C_SendByteX(I2C_TypeDef * i2c, uint8_t *buf, uint16_t bytes_count)
{
	uint16_t i;
	for(i=0;i<bytes_count;i++)
	{
	  if(i<(bytes_count-1))
	  {
		while(!LL_I2C_IsActiveFlag_TXE(i2c)){};				// Ожидание установки бита TXE, очистки регистра DR
	    LL_I2C_TransmitData8(i2c, buf[i]);					// Отправка байта i
	  }
	  else
	  {
	    LL_I2C_GenerateStopCondition(I2C1);				// Генерируем условие STOP
	  }
	}
}

//************************************************
void I2C_SendStop(I2C_TypeDef * i2c)
{
  LL_I2C_GenerateStopCondition(i2c);					// Генерируем условие STOP
}
//------------------------------------------------

void I2C_SendAdrRd(I2C_TypeDef * i2c, uint8_t addr)
{
  LL_I2C_TransmitData8(i2c, addr | I2C_REQUEST_READ);	// Отправляем адрес устройства в шину
  while(!LL_I2C_IsActiveFlag_ADDR(i2c)){};				// Ожидание установки бита ADDR в регистре SR1, окончание передачи адреса SLAVE в шину
  LL_I2C_ClearFlag_ADDR(i2c);							// Очистим флаг ADDR
}
//------------------------------------------------

void I2C_ReadByte(I2C_TypeDef * i2c, uint8_t *buf, uint16_t bytes_count)	// Функция принимает шину, фдрес данных, кол-во принимаемых байт
{
	uint16_t i;
	for(i=0;i<bytes_count;i++)
	  {
	    if(i<(bytes_count-1))
	    {
	      while(!LL_I2C_IsActiveFlag_RXNE(I2C1)){};			// Ожидание установки флага регистра данных в режиме приема
	      buf[i] = LL_I2C_ReceiveData8(I2C1);				// Сохранение принятого байта
	    }
	    else
	    {
	      LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_NACK);	// Разрешение генерации NASK
	      LL_I2C_GenerateStopCondition(I2C1);				// Генерируем условие STOP
	      while(!LL_I2C_IsActiveFlag_RXNE(I2C1)){};			// Ожидание установки флага регистра данных в режиме приема
	      buf[i] = LL_I2C_ReceiveData8(I2C1);				// Сохранение последнего принятого байта
	    }
	  }
}

//------------------------------------------------
// Запись 1 байта по адресу регистра
void I2Cx_WriteData(uint16_t Addr, uint8_t Reg, uint8_t Value)
{
	I2C_SendStart(I2C1);
	I2C_SendAdrWr(I2C1, Addr);
	I2C_SendByte(I2C1, Reg);
	I2C_SendByte(I2C1, Value);
	I2C_SendStop(I2C1);
}

//------------------------------------------------
// Запись 2-х байт по адресу регистра
void I2Cx_WriteData16(uint16_t Addr, uint8_t Reg, uint8_t *Value)
{
	I2C_SendStart(I2C1);
	I2C_SendAdrWr(I2C1, Addr);
	I2C_SendByte(I2C1, Reg);
	I2C_SendByteX(I2C1, (uint8_t *)Value, 2);
}

//------------------------------------------------
// Запись 2-х байт по адресу регистра
void I2Cx_WriteDataX(uint16_t Addr, uint8_t Reg, uint8_t *Value, uint8_t num_byte)
{
	I2C_SendStart(I2C1);
	I2C_SendAdrWr(I2C1, Addr);
	I2C_SendByte(I2C1, Reg);
	I2C_SendByteX(I2C1, (uint8_t *)Value, num_byte);
}

//------------------------------------------------
// Передача адреса регистра для чтения
void I2Cx_WriteReg(uint16_t Addr, uint8_t Reg)
{
	I2C_SendStart(I2C1);
	I2C_SendAdrWr(I2C1, Addr);
	I2C_SendByte(I2C1, Reg);
	I2C_SendStop(I2C1);
}

//------------------------------------------------
// Передача адреса регистра для чтения для чтения данных hdc
void I2Cx_WriteRegHdc(uint16_t Addr, uint8_t Reg)
{
	I2C_SendStart(I2C1);
	I2C_SendAdrWr(I2C1, Addr);
	I2C_SendByte(I2C1, Reg);
//	I2C_SendStop(I2C1);
}

//------------------------------------------------
// Чтение одного байта данных из регистра по адресу
uint8_t I2Cx_ReadData(uint16_t Addr, uint8_t Reg)
{
	uint8_t value = 0;
	I2C_SendStart(I2C1);
	I2C_SendAdrWr(I2C1, Addr);
	I2C_SendByte(I2C1, Reg);
	I2C_SendStart(I2C1);
	I2C_SendAdrRd(I2C1, Addr);
	I2C_ReadByte(I2C1, &value, 1);
	return value;
}

//------------------------------------------------
// Чтение двух байт данных из регистров по адресу
void I2Cx_ReadData16(uint16_t Addr, uint8_t Reg, uint16_t *Value)
{
	I2C_SendStart(I2C1);
	I2C_SendAdrWr(I2C1, Addr);
	I2C_SendByte(I2C1, Reg);
	I2C_SendStart(I2C1);
	I2C_SendAdrRd(I2C1, Addr);
	I2C_ReadByte(I2C1, (uint8_t *)Value, 2);
}
//------------------------------------------------
// Чтение трех байт данных из регистров по адресу
void I2Cx_ReadData24(uint16_t Addr, uint8_t Reg, uint32_t *Value)
{
	I2C_SendStart(I2C1);
	I2C_SendAdrWr(I2C1, Addr);
	I2C_SendByte(I2C1, Reg);
	I2C_SendStart(I2C1);
	I2C_SendAdrRd(I2C1, Addr);
	I2C_ReadByte(I2C1, (uint8_t *)Value, 3);
}

void I2Cx_ReadData32(uint16_t Addr, uint8_t Reg, uint8_t *Value)
{
	I2C_SendStart(I2C1);
	I2C_SendAdrWr(I2C1, Addr);
	I2C_SendByte(I2C1, Reg);
	I2C_SendStart(I2C1);
	I2C_SendAdrRd(I2C1, Addr);
	I2C_ReadByte(I2C1, (uint8_t *)Value, 4);
}

void I2Cx_ReadData32Hdc(uint16_t Addr, uint8_t Reg, uint8_t *Value)
{
	I2C_SendStart(I2C1);
	I2C_SendAdrRd(I2C1, Addr);
	I2C_ReadByte(I2C1, (uint8_t *)Value, 4);
}

void I2Cx_ReadDataX(uint16_t Addr, uint8_t Reg, uint8_t *Value, uint8_t num_byte)
{
	I2C_SendStart(I2C1);
	I2C_SendAdrWr(I2C1, Addr);
	I2C_SendByte(I2C1, Reg);
	I2C_SendStart(I2C1);
	I2C_SendAdrRd(I2C1, Addr);
	I2C_ReadByte(I2C1, (uint8_t *)Value, num_byte);
}
