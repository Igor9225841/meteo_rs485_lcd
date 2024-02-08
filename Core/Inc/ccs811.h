/*
 * ccs811.h
 *
 *  Created on: 17 февр. 2023 г.
 *      Author: »горь
 */

#ifndef INC_CCS811_H_
#define INC_CCS811_H_

#include "main.h"
#include "loop.h"
#include "i2c_user.h"
#include "uart_usb.h"


#endif /* INC_CCS811_H_ */

void ccs811_init(void);
void ccs811_start_measurement(uint16_t* co2, uint16_t* voc, int8_t t_in, uint16_t h_in);

/*=========================================================================
    REGISTERS
    -----------------------------------------------------------------------*/
enum {
  CCS811_STATUS = 0x00,
  CCS811_MEAS_MODE = 0x01,
  CCS811_ALG_RESULT_DATA = 0x02,
  CCS811_RAW_DATA = 0x03,
  CCS811_ENV_DATA = 0x05,
  CCS811_NTC = 0x06,
  CCS811_THRESHOLDS = 0x10,
  CCS811_BASELINE = 0x11,
  CCS811_HW_ID = 0x20,
  CCS811_HW_VERSION = 0x21,
  CCS811_FW_BOOT_VERSION = 0x23,
  CCS811_FW_APP_VERSION = 0x24,
  CCS811_ERROR_ID = 0xE0,
  CCS811_SW_RESET = 0xFF,
};

// bootloader registers
enum {
  CCS811_BOOTLOADER_APP_ERASE = 0xF1,
  CCS811_BOOTLOADER_APP_DATA = 0xF2,
  CCS811_BOOTLOADER_APP_VERIFY = 0xF3,
  CCS811_BOOTLOADER_APP_START = 0xF4
};

enum {
  CCS811_DRIVE_MODE_IDLE = 0x00,
  CCS811_DRIVE_MODE_1SEC = 0x10,
  CCS811_DRIVE_MODE_10SEC = 0x20,
  CCS811_DRIVE_MODE_60SEC = 0x30,
  CCS811_DRIVE_MODE_250MS = 0x04,
};
