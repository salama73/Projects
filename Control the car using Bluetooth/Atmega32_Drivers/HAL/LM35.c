/*
 * LM35.c
 *
 * Created: 12/6/2022 3:05:39 PM
 *  Author: Salama Mohammed
 */ 

#include "LM35.h"

void LM35_Init(enum NUM_CH CH)
{
	GPIO_Pinconfig_t GPIO_Conf ;
	switch(CH)
	{
		case 0:
		{
			GPIO_Conf.pinNumber = GPIO_PIN_0 ;
			break ;
		}
		case 1:
		{
			GPIO_Conf.pinNumber = GPIO_PIN_1 ;
			break ;
		}
		case 2:
		{
			GPIO_Conf.pinNumber = GPIO_PIN_2 ;
			break ;
		}
		case 3:
		{
			GPIO_Conf.pinNumber = GPIO_PIN_3 ;
			break ;
		}
		case 4:
		{
			GPIO_Conf.pinNumber = GPIO_PIN_4 ;
			break ;
		}
		case 5:
		{
			GPIO_Conf.pinNumber = GPIO_PIN_5 ;
			break ;
		}
		case 6:
		{
			GPIO_Conf.pinNumber = GPIO_PIN_6 ;
			break ;
		}
		case 7:
		{
			GPIO_Conf.pinNumber = GPIO_PIN_7 ;
			break ;
		}
	}
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_INPUT_FLO ;
	MCAL_GPIO_Init(GPIOA , &GPIO_Conf ) ;
		
	ADC_config_t* ADC_Config;
	ADC_Config->Voltage_Reference =ADC_Voltage_Reference_AVCC ;
	ADC_Config->Prescaler =ADC_Prescaler_64 ;
	MCAL_ADC_Init(ADC_Config);
}

uint16_t LM35_Get_Tem(enum NUM_CH CH)
{
	uint16_t DATA;
	DATA=MCAL_ADC_Read( CH );
	DATA=((DATA*(5.0/1024))/0.01)+0.5; // add 0.5 to raise the greater than half to integer
	return DATA ;
}