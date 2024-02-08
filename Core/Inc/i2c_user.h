/*
 * i2c_user.h
 *
 *  Created on: 13 февр. 2023 г.
 *      Author: »горь
 */

#ifndef INC_I2C_USER_H_
#define INC_I2C_USER_H_

#include "main.h"

void I2C_SendStart(I2C_TypeDef * i2c);
void I2C_SendAdrWr(I2C_TypeDef * i2c, uint8_t addr);
void I2C_SendByte(I2C_TypeDef * i2c, uint8_t c);
void I2C_SendByteX(I2C_TypeDef * i2c, uint8_t *buf, uint16_t bytes_count);
void I2C_SendStop(I2C_TypeDef * i2c);
void I2C_SendAdrRd(I2C_TypeDef * i2c, uint8_t addr);
void I2C_ReadByte(I2C_TypeDef * i2c, uint8_t *buf, uint16_t bytes_count);
void I2Cx_WriteRegHdc(uint16_t Addr, uint8_t Reg);

void I2Cx_WriteData(uint16_t Addr, uint8_t Reg, uint8_t Value);
void I2Cx_WriteData16(uint16_t Addr, uint8_t Reg, uint8_t *Value);
uint8_t I2Cx_ReadData(uint16_t Addr, uint8_t Reg);
void I2Cx_ReadData16(uint16_t Addr, uint8_t Reg, uint16_t *Value);
void I2Cx_ReadData24(uint16_t Addr, uint8_t Reg, uint32_t *Value);
void I2Cx_ReadData32(uint16_t Addr, uint8_t Reg, uint8_t *Value);
void I2Cx_ReadData32Hdc(uint16_t Addr, uint8_t Reg, uint8_t *Value);
void I2Cx_WriteReg(uint16_t Addr, uint8_t Reg);
void I2Cx_ReadDataX(uint16_t Addr, uint8_t Reg, uint8_t *Value, uint8_t num_byte);
void I2Cx_WriteDataX(uint16_t Addr, uint8_t Reg, uint8_t *Value, uint8_t num_byte);

#endif /* INC_I2C_USER_H_ */
