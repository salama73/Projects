/*
 * Pwm_PBcfg.c
 *
 *  Created on: Oct 6, 2023
 *      Author: ELBOSTAN
 */

#include "Pwm.h"
void CH3(void)
{
	uint8 b;
	b=0;
}
Pwm_ConfigType PWM_Config=
{
	{
		{
			{PWM_FIXED_PERIOD,PwmChannelId_0,Default_Dutycycle,PWM_LOW,NULL_PTR,Default_Period,PWM_HIGH},
			{PWM_FIXED_PERIOD,PwmChannelId_1,Default_Dutycycle,PWM_LOW,NULL_PTR,Default_Period,PWM_HIGH},
			{PWM_FIXED_PERIOD,PwmChannelId_2,Default_Dutycycle,PWM_LOW,NULL_PTR,Default_Period,PWM_HIGH},
			{PWM_FIXED_PERIOD,PwmChannelId_3,Default_Dutycycle,PWM_LOW,NULL_PTR,Default_Period,PWM_HIGH}
		}
	}
};


