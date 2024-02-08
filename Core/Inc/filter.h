/*
 * filter.h
 *
 *  Created on: Jun 11, 2023
 *      Author: Igor
 */

#ifndef INC_FILTER_H_
#define INC_FILTER_H_

#include "main.h"

#endif /* INC_FILTER_H_ */

#define NUM_READ_MEDIAN 5   // порядок медианы
#define NUM_READ_AVERAGE 7  // количество усреднений для средних арифм. фильтров

uint16_t findMedianN(uint16_t newVal, uint16_t *buffer);
uint16_t runMiddleArifm(uint16_t newVal, uint16_t *vals);
