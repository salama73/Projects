/*
 * IR_Sensor.h
 *  Created on: 5/7/2023
 *  Author: Salama mohamed
 */

#include "IR_Sensor.h"

void IR_Sensor_Init(void)
{
	//gpio init
	GPIO_Pinconfig_t pinconfig ;
	pinconfig.GPIO_MODE = GPIO_MODE_INPUT_PU ;
	pinconfig.pinNumber = GPIO_PIN_3 ;
	MCAL_GPIO_Init(GPIOA, &pinconfig) ;
}
uint8_t IR_Sensor_Read(void)
{
	return MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3);
}

