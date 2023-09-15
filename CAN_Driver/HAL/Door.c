/*
 * Door.c
 *  Created on: 5/7/2023
 *  Author: Salama mohamed
 */

#include "Door.h"

void Door_Init(void)
{
	Servo_Init();
}
void Door_Open(void)
{
	My_Servo(90);
	delay_ms(20);
	MCAL_TIMx_Set_Compare_Value(TIM2,0,CH2);
}
void Door_close(void)
{
	My_Servo(0);
	delay_ms(20);
	MCAL_TIMx_Set_Compare_Value(TIM2,0,CH2);
}

