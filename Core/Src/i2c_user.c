/*
 * i2c_user.c
 *
 *  Created on: 13 ����. 2023 �.
 *      Author: �����
 */

#include "i2c_user.h"

//------------------------------------------------
#define I2C_REQUEST_WRITE                       0x00
#define I2C_REQUEST_READ                        0x01

//------------------------------------------------
void I2C_SendStart(I2C_TypeDef * i2c)
{
  //Disable Pos
  LL_I2C_DisableBitPOS(I2C1);							// ��� ACK ��������� ACK (NACK) �������� �����, ����������� � �������� ������.
  LL_I2C_AcknowledgeNextData(i2c, LL_I2C_ACK);			// ��������� ������ ������������ ������� ACK ����� ����� ������
  LL_I2C_GenerateStartCondition(i2c);					// ���������� ������� START
  while(!LL_I2C_IsActiveFlag_SB(i2c)){};				// �������� ��������� ���� SB � �������� SR1
  (void) i2c->SR1;										// ������� ������� SR1
}
//-------------------------------------------------

void I2C_SendAdrWr(I2C_TypeDef * i2c, uint8_t addr)
{
  LL_I2C_TransmitData8(i2c, addr | I2C_REQUEST_WRITE);	// ���������� ����� ���������� � ����
  while(!LL_I2C_IsActiveFlag_ADDR(i2c)){};				// �������� ��������� ���� ADDR � �������� SR1, ��������� �������� ������ SLAVE � ����
  LL_I2C_ClearFlag_ADDR(i2c);							// ������� ���� ADDR
}
//------------------------------------------------

void I2C_SendByte(I2C_TypeDef * i2c, uint8_t c)
{
  LL_I2C_TransmitData8(i2c, c);							// ���������� ������ � ����
  while(!LL_I2C_IsActiveFlag_TXE(i2c)){};				// �������� ��������� ���� TXE, ������� �������� DR
}
//------------------------------------------------

void I2C_SendByteX(I2C_TypeDef * i2c, uint8_t *buf, uint16_t bytes_count)
{
	uint16_t i;
	for(i=0;i<bytes_count;i++)
	{
	  if(i<(bytes_count-1))
	  {
		while(!LL_I2C_IsActiveFlag_TXE(i2c)){};				// �������� ��������� ���� TXE, ������� �������� DR
	    LL_I2C_TransmitData8(i2c, buf[i]);					// �������� ����� i
	  }
	  else
	  {
	    LL_I2C_GenerateStopCondition(I2C1);				// ���������� ������� STOP
	  }
	}
}

//************************************************
void I2C_SendStop(I2C_TypeDef * i2c)
{
  LL_I2C_GenerateStopCondition(i2c);					// ���������� ������� STOP
}
//------------------------------------------------

void I2C_SendAdrRd(I2C_TypeDef * i2c, uint8_t addr)
{
  LL_I2C_TransmitData8(i2c, addr | I2C_REQUEST_READ);	// ���������� ����� ���������� � ����
  while(!LL_I2C_IsActiveFlag_ADDR(i2c)){};				// �������� ��������� ���� ADDR � �������� SR1, ��������� �������� ������ SLAVE � ����
  LL_I2C_ClearFlag_ADDR(i2c);							// ������� ���� ADDR
}
//------------------------------------------------

void I2C_ReadByte(I2C_TypeDef * i2c, uint8_t *buf, uint16_t bytes_count)	// ������� ��������� ����, ����� ������, ���-�� ����������� ����
{
	uint16_t i;
	for(i=0;i<bytes_count;i++)
	  {
	    if(i<(bytes_count-1))
	    {
	      while(!LL_I2C_IsActiveFlag_RXNE(I2C1)){};			// �������� ��������� ����� �������� ������ � ������ ������
	      buf[i] = LL_I2C_ReceiveData8(I2C1);				// ���������� ��������� �����
	    }
	    else
	    {
	      LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_NACK);	// ���������� ��������� NASK
	      LL_I2C_GenerateStopCondition(I2C1);				// ���������� ������� STOP
	      while(!LL_I2C_IsActiveFlag_RXNE(I2C1)){};			// �������� ��������� ����� �������� ������ � ������ ������
	      buf[i] = LL_I2C_ReceiveData8(I2C1);				// ���������� ���������� ��������� �����
	    }
	  }
}

//------------------------------------------------
// ������ 1 ����� �� ������ ��������
void I2Cx_WriteData(uint16_t Addr, uint8_t Reg, uint8_t Value)
{
	I2C_SendStart(I2C1);
	I2C_SendAdrWr(I2C1, Addr);
	I2C_SendByte(I2C1, Reg);
	I2C_SendByte(I2C1, Value);
	I2C_SendStop(I2C1);
}

//------------------------------------------------
// ������ 2-� ���� �� ������ ��������
void I2Cx_WriteData16(uint16_t Addr, uint8_t Reg, uint8_t *Value)
{
	I2C_SendStart(I2C1);
	I2C_SendAdrWr(I2C1, Addr);
	I2C_SendByte(I2C1, Reg);
	I2C_SendByteX(I2C1, (uint8_t *)Value, 2);
}

//------------------------------------------------
// ������ 2-� ���� �� ������ ��������
void I2Cx_WriteDataX(uint16_t Addr, uint8_t Reg, uint8_t *Value, uint8_t num_byte)
{
	I2C_SendStart(I2C1);
	I2C_SendAdrWr(I2C1, Addr);
	I2C_SendByte(I2C1, Reg);
	I2C_SendByteX(I2C1, (uint8_t *)Value, num_byte);
}

//------------------------------------------------
// �������� ������ �������� ��� ������
void I2Cx_WriteReg(uint16_t Addr, uint8_t Reg)
{
	I2C_SendStart(I2C1);
	I2C_SendAdrWr(I2C1, Addr);
	I2C_SendByte(I2C1, Reg);
	I2C_SendStop(I2C1);
}

//------------------------------------------------
// �������� ������ �������� ��� ������ ��� ������ ������ hdc
void I2Cx_WriteRegHdc(uint16_t Addr, uint8_t Reg)
{
	I2C_SendStart(I2C1);
	I2C_SendAdrWr(I2C1, Addr);
	I2C_SendByte(I2C1, Reg);
//	I2C_SendStop(I2C1);
}

//------------------------------------------------
// ������ ������ ����� ������ �� �������� �� ������
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
// ������ ���� ���� ������ �� ��������� �� ������
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
// ������ ���� ���� ������ �� ��������� �� ������
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
