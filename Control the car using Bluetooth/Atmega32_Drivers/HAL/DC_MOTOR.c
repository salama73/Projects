/*
 * DC_MOTOR.c
 *
 * Created: 12/4/2022 11:30:01 PM
 *  Author: Salama Mohammed
 */ 

#include "DC_MOTOR.h"

uint16_t TOP=0;
void MOTOR_Init(void) 
{
		PWM_config_t PWM_Config ;
		PWM_Config.Compare_Value_CH_B = 0 ;
		PWM_Config.Compare_Value_CH_A = 0 ;
		PWM_Config.Output_Compare_pin_A = PWM_Output_Compare_pin_A_Clear_At_Compare_Value_Set_At_TOP ;
		PWM_Config.Output_Compare_pin_B = PWM_Output_Compare_pin_B_Disable ;
		PWM_Config.Clock_Source = PWM_Clock_Source_clk_64 ;
		PWM_Config.TOP_Value = (uint16_t)((F_CPU/(64*50))-1) ;
		PWM_Config.OCIE1A_EN = PWM_OCIE1A_ENABLE_Disable ;
		PWM_Config.OCIE1B_EN = PWM_OCIE1B_ENABLE_Disable ;
		PWM_Config.TOIE1_EN = PWM_TOIE1_ENABLE_Disable ;
		PWM_Config.P_OCIE1A_CALL = NULL ;
		PWM_Config.P_OCIE1B_CALL = NULL ;
		PWM_Config.P_TOIE1_CALL = NULL ;
		MCAL_PWM_Init(&PWM_Config) ;
		TOP = PWM_Config.TOP_Value+1;
}

void MOTOR_Speed(uint8_t speed) 
{
	uint16_t Compare_Value=0 ;
	Compare_Value=TOP;
	Compare_Value /=5;
	if (speed==0)
	{
		Compare_Value = (TOP*speed);
	}
	else
	{
		Compare_Value = (Compare_Value*speed)-1;
	}
	MCAL_PWM_Set_Compare_Value(Compare_Value,A) ;
}