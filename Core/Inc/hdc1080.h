/*
 * hdc1080.h
 *
 *  Created on: Feb 14, 2023
 *      Author: Игорь
 */

#ifndef INC_HDC1080_H_
#define INC_HDC1080_H_

#include "main.h"
#include "loop.h"
#include "i2c_user.h"

//#define         HDC_1080_ADD                            0x40
#define         Configuration_register_add              0x02
#define         Temperature_register_add                0x00
#define         Humidity_register_add                   0x01


typedef enum
{
//  Temperature_Resolution_14_bit = 0,
  Temperature_Resolution_11_bit = 1
}Temp_Reso;

typedef enum
{
//  Humidity_Resolution_14_bit = 0,
  Humidity_Resolution_11_bit = 1,
  Humidity_Resolution_8_bit =2
}Humi_Reso;

void hdc1080_Setup(void);
void hdc1080_start_measurement(int8_t* temperature, uint8_t* humidity);


#endif /* INC_HDC1080_H_ */
