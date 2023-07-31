/*
 * LDR.c
 *
 * Created: 12/6/2022 2:59:24 PM
 *  Author: Salama Mohammed
 */ 

#include "LDR.h"

void LDR_Init(void)
{
	ADC_config_t* ADC_Config;
	ADC_Config->Voltage_Reference =ADC_Voltage_Reference_AVCC ;
	ADC_Config->Prescaler =ADC_Prescaler_64 ;
	MCAL_ADC_Init(ADC_Config);
}

uint16_t LDR_Get_Val(enum NUM_CH CH)
{
	uint16_t DATA;
	DATA=MCAL_ADC_Read( CH );
	return DATA ;
}