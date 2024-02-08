/*
 * hdc1080.c
 *
 *  Created on: Feb 14, 2023
 *      Author: Игорь
 */

#include "hdc1080.h"

static const uint8_t HDC1080_ADDR = 0x40 << 1;	// Используется 7 битный адрес

//Прототипы***********************************************************************************************
void hdc1080_init(uint8_t addr,Temp_Reso Temperature_Resolution_x_bit,Humi_Reso Humidity_Resolution_x_bit);



// Функции***************************************************************************************************
void hdc1080_Setup(void)
{
	hdc1080_init(HDC1080_ADDR, Temperature_Resolution_11_bit, Humidity_Resolution_8_bit);
}

void hdc1080_init(uint8_t addr,Temp_Reso Temperature_Resolution_x_bit,Humi_Reso Humidity_Resolution_x_bit)
{
	/* Temperature and Humidity are acquired in sequence, Temperature first
	 * Default:   Temperature resolution = 14 bit,
	 *            Humidity resolution = 14 bit
	 */

	/* Set the acquisition mode to measure both temperature and humidity by setting Bit[12] to 1 */
	uint16_t config_reg_value=0x1000;
	uint8_t data_send[2];

	if(Temperature_Resolution_x_bit == Temperature_Resolution_11_bit)
	{
		config_reg_value |= (1<<10); //11 bit
	}

	switch(Humidity_Resolution_x_bit)
	{
	case Humidity_Resolution_11_bit:
		config_reg_value|= (1<<8);
		break;
	case Humidity_Resolution_8_bit:
		config_reg_value|= (1<<9);
		break;
	}

	data_send[0]= (config_reg_value>>8);
	data_send[1]= (config_reg_value&0x00ff);

	I2Cx_WriteData16(HDC1080_ADDR, config_reg_value, data_send);
}


void hdc1080_start_measurement(int8_t* temperature, uint8_t* humidity)
{
	uint8_t receive_data[4];
	uint16_t temp_x,humi_x;
	uint8_t send_data = Temperature_register_add;

	I2Cx_WriteRegHdc(HDC1080_ADDR, send_data);

	/* Delay here 15ms for conversion compelete.
	 * Note: datasheet say maximum is 7ms, but when delay=7ms, the read value is not correct
	 */
	LL_mDelay(15);

	/* Read temperature and humidity */
	I2Cx_ReadData32Hdc(HDC1080_ADDR, send_data, receive_data);

	temp_x =((receive_data[0]<<8)|receive_data[1]);
	humi_x =((receive_data[2]<<8)|receive_data[3]);

	*temperature=((temp_x/65536.0)*165.0)-40.0;
	*humidity=(uint8_t)((humi_x/65536.0)*100.0);

//	return 0;

}


