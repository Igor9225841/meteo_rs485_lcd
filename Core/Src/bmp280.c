/*
 * bmp280.c
 *
 *  Created on: 13 февр. 2023 г.
 *      Author: Игорь
 */

#include "bmp280.h"
//------------------------------------------------

extern char str1[50];
BMP280_CalibData CalibData;
int32_t temper_int;

//------------------------------------------------
void BMP280_WriteReg(uint8_t Reg, uint8_t Value)
{
  I2Cx_WriteData(BMP280_ADDRESS, Reg, Value);
}
//------------------------------------------------
uint8_t BMP280_ReadReg(uint8_t Reg)
{
  uint8_t res = I2Cx_ReadData(BMP280_ADDRESS,Reg);
  return res;
}
//------------------------------------------------
void BMP280_ReadReg_U16(uint8_t Reg, uint16_t *Value)
{
  I2Cx_ReadData16(BMP280_ADDRESS,Reg,Value);
}
//------------------------------------------------
void BMP280_ReadReg_S16(uint8_t Reg, int16_t *Value)
{
  I2Cx_ReadData16(BMP280_ADDRESS,Reg, (uint16_t*) Value);
}
//------------------------------------------------
void BMP280_ReadReg_BE_S16(uint8_t Reg, int16_t *Value)
{
  I2Cx_ReadData16(BMP280_ADDRESS,Reg,(uint16_t*)Value);
  *(uint16_t *) Value = be16toword(*(uint16_t *) Value);
}
//------------------------------------------------
void BMP280_ReadReg_U24(uint8_t Reg, uint32_t *Value)
{
  I2Cx_ReadData24(BMP280_ADDRESS,Reg,Value);
  *(uint32_t *) Value &= 0x00FFFFFF;
}
//------------------------------------------------
void BMP280_ReadReg_BE_U24(uint8_t Reg, uint32_t *Value)
{
  I2Cx_ReadData24(BMP280_ADDRESS,Reg,Value);
  *(uint32_t *) Value = be24toword(*(uint32_t *) Value) & 0x00FFFFFF;
}
//------------------------------------------------
uint8_t BMP280_ReadStatus(void)
{
  //clear unuset bits
  uint8_t res = BMP280_ReadReg(BMP280_REGISTER_STATUS)&0x09;
  return res;
}
//------------------------------------------------

void BMP280_ReadCoefficients(void)
{
  BMP280_ReadReg_U16(BMP280_REGISTER_DIG_T1,&CalibData.dig_T1);
  sprintf(str1, "DIG_T1: %u\r\n", CalibData.dig_T1);
  UART_TX_Str((uint8_t*)str1);
  BMP280_ReadReg_S16(BMP280_REGISTER_DIG_T2,&CalibData.dig_T2);
  sprintf(str1, "DIG_T2: %d\r\n", CalibData.dig_T2);
  UART_TX_Str((uint8_t*)str1);
  BMP280_ReadReg_S16(BMP280_REGISTER_DIG_T3,&CalibData.dig_T3);
  sprintf(str1, "DIG_T3: %d\r\n", CalibData.dig_T3);
  UART_TX_Str((uint8_t*)str1);
  BMP280_ReadReg_U16(BMP280_REGISTER_DIG_P1,&CalibData.dig_P1);
  sprintf(str1, "DIG_P1: %u\r\n", CalibData.dig_P1);
  UART_TX_Str((uint8_t*)str1);
  BMP280_ReadReg_S16(BMP280_REGISTER_DIG_P2,&CalibData.dig_P2);
  sprintf(str1, "DIG_P2: %d\r\n", CalibData.dig_P2);
  UART_TX_Str((uint8_t*)str1);
  BMP280_ReadReg_S16(BMP280_REGISTER_DIG_P3,&CalibData.dig_P3);
  sprintf(str1, "DIG_P3: %d\r\n", CalibData.dig_P3);
  UART_TX_Str((uint8_t*)str1);
  BMP280_ReadReg_S16(BMP280_REGISTER_DIG_P4,&CalibData.dig_P4);
  sprintf(str1, "DIG_P4: %d\r\n", CalibData.dig_P4);
  UART_TX_Str((uint8_t*)str1);
  BMP280_ReadReg_S16(BMP280_REGISTER_DIG_P5,&CalibData.dig_P5);
  sprintf(str1, "DIG_P5: %d\r\n", CalibData.dig_P5);
  UART_TX_Str((uint8_t*)str1);
  BMP280_ReadReg_S16(BMP280_REGISTER_DIG_P6,&CalibData.dig_P6);
  sprintf(str1, "DIG_P6: %d\r\n", CalibData.dig_P6);
  UART_TX_Str((uint8_t*)str1);
  BMP280_ReadReg_S16(BMP280_REGISTER_DIG_P7,&CalibData.dig_P7);
  sprintf(str1, "DIG_P7: %d\r\n", CalibData.dig_P7);
  UART_TX_Str((uint8_t*)str1);
  BMP280_ReadReg_S16(BMP280_REGISTER_DIG_P8,&CalibData.dig_P8);
  sprintf(str1, "DIG_P8: %d\r\n", CalibData.dig_P8);
  UART_TX_Str((uint8_t*)str1);
  BMP280_ReadReg_S16(BMP280_REGISTER_DIG_P9,&CalibData.dig_P9);
  sprintf(str1, "DIG_P9: %d\r\n", CalibData.dig_P9);
  UART_TX_Str((uint8_t*)str1);

}
//------------------------------------------------
void BMP280_SetStandby(uint8_t tsb) {
  uint8_t reg;
  reg = BMP280_ReadReg(BMP280_REG_CONFIG) & ~BMP280_STBY_MSK;
  reg |= tsb & BMP280_STBY_MSK;
  BMP280_WriteReg(BMP280_REG_CONFIG,reg);
}
//------------------------------------------------
  void BMP280_SetFilter(uint8_t filter) {
  uint8_t reg;
  reg = BMP280_ReadReg(BMP280_REG_CONFIG) & ~BMP280_FILTER_MSK;
  reg |= filter & BMP280_FILTER_MSK;
  BMP280_WriteReg(BMP280_REG_CONFIG,reg);
}
//------------------------------------------------
void BMP280_SetOversamplingTemper(uint8_t osrs)
{
  uint8_t reg;
  reg = BMP280_ReadReg(BMP280_REG_CTRL_MEAS) & ~BMP280_OSRS_T_MSK;
  reg |= osrs & BMP280_OSRS_T_MSK;
  BMP280_WriteReg(BMP280_REG_CTRL_MEAS,reg);
}
//------------------------------------------------
void BMP280_SetOversamplingPressure(uint8_t osrs)
{
  uint8_t reg;
  reg = BMP280_ReadReg(BMP280_REG_CTRL_MEAS) & ~BMP280_OSRS_P_MSK;
  reg |= osrs & BMP280_OSRS_P_MSK;
  BMP280_WriteReg(BMP280_REG_CTRL_MEAS,reg);
}

//------------------------------------------------
void BMP280_SetMode(uint8_t mode) {
  uint8_t reg;
  reg = BMP280_ReadReg(BMP280_REG_CTRL_MEAS) & ~BMP280_MODE_MSK;
  reg |= mode & BMP280_MODE_MSK;
  BMP280_WriteReg(BMP280_REG_CTRL_MEAS,reg);
}
//------------------------------------------------
float BMP280_ReadTemperature(void)
{
	float temper_float = 0.0f;
	uint32_t temper_raw;
	int32_t val1, val2;
	BMP280_ReadReg_BE_U24(BMP280_REGISTER_TEMPDATA,&temper_raw);
	temper_raw >>= 4;
	val1 = ((((temper_raw>>3) - ((int32_t)CalibData.dig_T1 <<1))) *
		((int32_t)CalibData.dig_T2)) >> 11;
/*
	val2 = (((((temper_raw>>4) - ((int32_t)CalibData.dig_T1)) *
			((temper_raw>>4) - ((int32_t)CalibData.dig_T1))) >> 12) *
			((int32_t)CalibData.dig_T3)) >> 14;
*/
	val2 = (((((temper_raw>>4) - ((int32_t)CalibData.dig_T1)) *
				((temper_raw>>4) - ((int32_t)CalibData.dig_T1))) >> 12) *
				50) >> 14;	// Формула изменена, коэффициент взят от другого датчика
	temper_int = val1 + val2;

	temper_float = ((temper_int * 5 + 128) >> 8);
// Вывод значения без коррекции*****************************
//Удалить для включения коррекции
//	temper_float = ((temper_int * 5 + 128) >> 10);	// Все коррекции отключены
//*********************************************************
	temper_float /= 100.0f;
  return temper_float;
}
//------------------------------------------------
float BMP280_ReadPressure(void)
{
  float press_float = 0.0f;
	uint32_t press_raw, pres_int;
	int64_t val1, val2, p;
	BMP280_ReadTemperature(); // must be done first to get t_fine
	BMP280_ReadReg_BE_U24(BMP280_REGISTER_PRESSUREDATA,&press_raw);
	press_raw >>= 4;
	val1 = ((int64_t) temper_int) - 128000;
	val2 = val1 * val1 * (int64_t)CalibData.dig_P6;
	val2 = val2 + ((val1 * (int64_t)CalibData.dig_P5) << 17);
	val2 = val2 + ((int64_t)CalibData.dig_P4 << 35);
	val1 = ((val1 * val1 * (int64_t)CalibData.dig_P3) >> 8) + ((val1 * (int64_t)CalibData.dig_P2) << 12);
	val1 = (((((int64_t)1) << 47) + val1)) * ((int64_t)CalibData.dig_P1) >> 33;
	if (val1 == 0) {
		return 0; // avoid exception caused by division by zero
	}
	p = 1048576 - press_raw;
	p = (((p << 31) - val2) * 3125) / val1;
	val1 = (((int64_t)CalibData.dig_P9) * (p >> 13) * (p >> 13)) >> 25;
	val2 = (((int64_t)CalibData.dig_P8) * p) >> 19;
	p = ((p + val1 + val2) >> 8) + ((int64_t)CalibData.dig_P7 << 4);
	pres_int = p >> 8;
	press_float = pres_int / 100.0f;
  return press_float;
}

//------------------------------------------------
void BMP280_Init(void)
{
	uint8_t value=0;
	uint16_t value32=0;
  	value = BMP280_ReadReg(BMP280_REG_ID);
  	sprintf(str1, "\r\n\r\nID_BMP280: 0x%02X\r\n", value);
	UART_TX_Str((uint8_t*)str1);
	BMP280_WriteReg(BMP280_REG_SOFTRESET,BMP280_SOFTRESET_VALUE);
	while (BMP280_ReadStatus() & BMP280_STATUS_IM_UPDATE) ;
	BMP280_ReadCoefficients();
	BMP280_SetStandby(BMP280_STBY_1000);
	BMP280_SetFilter(BMP280_FILTER_4);
	BMP280_SetOversamplingTemper(BMP280_OSRS_T_x4);
	BMP280_SetOversamplingPressure(BMP280_OSRS_P_x2);
	value32 = BMP280_ReadReg(BMP280_REG_CTRL_MEAS);
	sprintf(str1, "Measurements status: %04X\r\n", value32);
	UART_TX_Str((uint8_t*)str1);
	sprintf(str1, "Temperature: %s\r\nPressure: %s\r",
	(value32 & BMP280_OSRS_T_MSK) ? "ON" : "OFF",
	(value32 & BMP280_OSRS_P_MSK) ? "ON" : "OFF");
	UART_TX_Str((uint8_t*)str1);
	BMP280_SetMode(BMP280_MODE_NORMAL);
}
//------------------------------------------------
