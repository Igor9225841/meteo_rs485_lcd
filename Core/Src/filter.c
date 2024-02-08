/*
 * filter.c
 *
 *  Created on: Jun 11, 2023
 *      Author: Igor
 */

#include "filter.h"
#include "main.h"


// ���������� ������� 3 �������� ��� ��������� ������ ��������� ��������
uint16_t findMedianN(uint16_t newVal, uint16_t* buffer)
{

	for (uint8_t i = NUM_READ_MEDIAN; i >= 1; i--)
	{
		buffer[i] = buffer[i-1];      // �������� �������� ������� ������
	}
	buffer[0] = newVal;          	  // ��������� � ������ ����� ��������

	uint16_t median_arr[NUM_READ_MEDIAN]; // ������ ��� ������� �������

	//�������� ������ ������ ������� � ��������� ������
	for (uint8_t cnt_arr = 0; cnt_arr <= NUM_READ_MEDIAN; cnt_arr++)
	{
		median_arr[cnt_arr] = buffer[cnt_arr];
	}

	uint8_t i_med, j_med;			  //�������� ��� ���������� �������
	uint16_t z_med;					  // ���������� ��� ������������ ��������� �������
	for (i_med = 0; i_med < NUM_READ_MEDIAN-1; i_med++)
	{
		for (j_med = i_med+1; j_med < NUM_READ_MEDIAN; j_med++)
		{
			if (median_arr[i_med] > median_arr[j_med])
	        {
				z_med=median_arr[i_med];
				median_arr[i_med]=median_arr[j_med];
				median_arr[j_med]=z_med;
	         }
		}
	}
	if ((NUM_READ_MEDIAN % 2) == 0)
		return (median_arr[NUM_READ_MEDIAN/2]+median_arr[NUM_READ_MEDIAN/2-1])/2;
	 else
		 return median_arr[NUM_READ_MEDIAN/2];
}

// ������� ������� ��������������
uint16_t runMiddleArifm(uint16_t newVal, uint16_t* vals)
{
	uint16_t average = 0;

	for (uint8_t i_av = NUM_READ_AVERAGE; i_av >= 1; i_av--)
	{
	    vals[i_av] = vals[i_av-1];      // �������� �������� ������� ������
	}

	vals[0] = newVal;          	  // ��������� � ������ ����� ��������

	for (uint8_t j_av = 0; j_av < NUM_READ_AVERAGE; j_av++)
	{
	    average += vals[j_av];        // ���������
	}
	return ((uint16_t)average / NUM_READ_AVERAGE);
}


