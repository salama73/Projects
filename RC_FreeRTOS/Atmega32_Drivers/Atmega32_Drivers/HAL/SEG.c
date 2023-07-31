/*
 * _SEG.c
 *
 * Created: 12/7/2022 3:27:17 AM
 *  Author: Salama Mohammed
 */ 

#include "SEG.h"

uint8_t num[11]={126,96,182,158,204,218,250,14,254,222};

void SEG_Init(void)
{
	GPIO_Pinconfig_t GPIO_Conf ;
	GPIO_Conf.pinNumber = GPIO_PIN_1 ;
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	MCAL_GPIO_Init(GPIOA , &GPIO_Conf ) ;
	
	GPIO_Conf.pinNumber = GPIO_PIN_2 ;
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	MCAL_GPIO_Init(GPIOA , &GPIO_Conf ) ;
	
	GPIO_Conf.pinNumber = GPIO_PIN_3 ;
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	MCAL_GPIO_Init(GPIOA , &GPIO_Conf ) ;
	
	GPIO_Conf.pinNumber = GPIO_PIN_4 ;
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	MCAL_GPIO_Init(GPIOA , &GPIO_Conf ) ;
	
	GPIO_Conf.pinNumber = GPIO_PIN_5 ;
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	MCAL_GPIO_Init(GPIOA , &GPIO_Conf ) ;
	
	GPIO_Conf.pinNumber = GPIO_PIN_6 ;
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	MCAL_GPIO_Init(GPIOA , &GPIO_Conf ) ;
	
	GPIO_Conf.pinNumber = GPIO_PIN_7 ;
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	MCAL_GPIO_Init(GPIOA , &GPIO_Conf ) ;
}

void SEG_Display(uint8_t Num)
{
	uint8_t Number;
	Number = num[Num];
	MCAL_GPIO_WritePort(GPIOA,Number);
}