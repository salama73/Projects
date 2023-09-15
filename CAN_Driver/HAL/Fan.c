/*
 * Fan.h
 *  Created on: 5/7/2023
 *  Author: Salama mohamed
 */


#include "Fan.h"

void Fan_Init(void)
{
	uint16_t top;
	//Frequency 50 hz
	top=( ( 0.02 *  MCAL_Get_PCLC1_FREQ() ) / 8 );
	TIMx_config_t  TIMx_Config;
	TIMx_Config.COUNT_MODE=TIMx_COUNT_MODE_UP;
	TIMx_Config.MODE=TIMx_MODE_PWM2;
	TIMx_Config.Prescalers=7;  // timer clock 1mhz
	MCAL_TIMx_Init(TIM2, &TIMx_Config , CH3);
	MCAL_TIMx_Set_Compare_Value(TIM2,0,CH3);
	MCAL_TIMx_Set_TOP_Value(TIM2, top);
}
void Fan_Speed(uint8_t speed)
{
	uint16_t compared;
	compared=speed*4000;
	MCAL_TIMx_Set_Compare_Value(TIM2,compared,CH3);
}
