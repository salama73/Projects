/*
 * Flame_Sensor.c
 *  Created on: 5/7/2023
 *  Author: Salama mohamed
 */

#include "Flame_Sensor.h"

void Flame_Sensor_Init(void)
{
	ADC_config_t ADC_ch0;
	//gpio init
	GPIO_Pinconfig_t pinconfig ;
	pinconfig.GPIO_MODE = GPIO_MODE_Analog  ;
	pinconfig.pinNumber = GPIO_PIN_0 ;
	MCAL_GPIO_Init(GPIOA, &pinconfig) ;
	//ADC init
	ADC_ch0.MODE=ADC_MODE_Single;
	ADC_ch0.Data_alignment=ADC_Data_alignment_Right;
	ADC_ch0.sampling_time=ADC_sampling_time_1_5;
	ADC_ch0.Channel=Ch0;
	MCAL_ADC_Init(&ADC_ch0);
}


uint16_t Flame_Sensor_Read(void)
{
	return MCAL_ADC_Read(Ch0);
}
