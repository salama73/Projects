/*
 * Pwm_Irq.c
 *
 *  Created on: Oct 6, 2023
 *      Author: ELBOSTAN
 */
#include "Pwm.h"

#include "../Common_Module/stm32f103x6.h"
extern Pwm_ConfigType Pwm_Config;
extern uint8 Flag_Notifications;

void TIM2_IRQHandler(void)
{
	if(Pwm_Config.Config_Pwm.Channel_Config[PwmChannelId_0].PwmPolarity==PWM_HIGH)
	{
		//overflow act as a RISING EDGE
		// counter matches the compare value act as a FALLING EDGE
		//ch 1
		switch (Flag_Notifications&0b11)
		{
			case PWM_RISING_EDGE:
				if((TIM2->SR&(1<<0))!=0)
				{
					TIM2->SR|=1<<0;
					Pwm_Config.Config_Pwm.Channel_Config[0].PwmNotification();
				}
				else
				{
					//
				}
				break;
			case PWM_FALLING_EDGE:
				if((TIM2->SR&(1<<1))!=0)
				{
					TIM2->SR|=1<<1;
					Pwm_Config.Config_Pwm.Channel_Config[0].PwmNotification();
				}
				else
				{
					//
				}
				break;
			case PWM_BOTH_EDGES:
				if((TIM2->SR&(1<<0))!=0)
				{
					TIM2->SR|=1<<0;
					Pwm_Config.Config_Pwm.Channel_Config[0].PwmNotification();
				}
				else if((TIM2->SR&(1<<1))!=0)
				{
					TIM2->SR|=1<<1;
					Pwm_Config.Config_Pwm.Channel_Config[0].PwmNotification();
				}
				else
				{
					//
				}
				break;
			default:
				//
				break;
		}
		//ch 2
		switch ((Flag_Notifications&(0b11<<2))>>2)
		{
			case PWM_RISING_EDGE:
				if((TIM2->SR&(1<<0))!=0)
				{
					TIM2->SR|=1<<0;
					Pwm_Config.Config_Pwm.Channel_Config[1].PwmNotification();
				}
				else
				{
					//
				}
				break;
			case PWM_FALLING_EDGE:
				if((TIM2->SR&(1<<2))!=0)
				{
					TIM2->SR|=1<<2;
					Pwm_Config.Config_Pwm.Channel_Config[1].PwmNotification();
				}
				else
				{
					//
				}
				break;
			case PWM_BOTH_EDGES:
				if((TIM2->SR&(1<<0))!=0)
				{
					TIM2->SR|=1<<0;
					Pwm_Config.Config_Pwm.Channel_Config[1].PwmNotification();
				}
				else if((TIM2->SR&(1<<2))!=0)
				{
					TIM2->SR|=1<<2;
					Pwm_Config.Config_Pwm.Channel_Config[1].PwmNotification();
				}
				else
				{
					//
				}
				break;
			default:
				//
				break;
		}
		//ch 3
		switch ((Flag_Notifications&(0b11<<4))>>4)
		{
			case PWM_RISING_EDGE:
				if((TIM2->SR&(1<<0))!=0)
				{
					TIM2->SR|=1<<0;
					Pwm_Config.Config_Pwm.Channel_Config[2].PwmNotification();
				}
				else
				{
					//
				}
				break;
			case PWM_FALLING_EDGE:
				if((TIM2->SR&(1<<3))!=0)
				{
					TIM2->SR|=1<<3;
					Pwm_Config.Config_Pwm.Channel_Config[2].PwmNotification();
				}
				else
				{
					//
				}
				break;
			case PWM_BOTH_EDGES:
				if((TIM2->SR&(1<<0))!=0)
				{
					TIM2->SR|=1<<0;
					Pwm_Config.Config_Pwm.Channel_Config[2].PwmNotification();
				}
				else if((TIM2->SR&(1<<3))!=0)
				{
					TIM2->SR|=1<<3;
					Pwm_Config.Config_Pwm.Channel_Config[2].PwmNotification();
				}
				else
				{
					//
				}
				break;
			default:
				//
				break;
		}
		//ch 4
		switch ((Flag_Notifications&(0b11<<6))>>6)
		{
			case PWM_RISING_EDGE:
				if((TIM2->SR&(1<<0))!=0)
				{
					TIM2->SR|=1<<0;
					Pwm_Config.Config_Pwm.Channel_Config[3].PwmNotification();
				}
				else
				{
					//
				}
				break;
			case PWM_FALLING_EDGE:
				if((TIM2->SR&(1<<4))!=0)
				{
					TIM2->SR|=1<<4;
					Pwm_Config.Config_Pwm.Channel_Config[3].PwmNotification();
				}
				else
				{
					//
				}
				break;
			case PWM_BOTH_EDGES:
				if((TIM2->SR&(1<<0))!=0)
				{
					TIM2->SR|=1<<0;
					Pwm_Config.Config_Pwm.Channel_Config[3].PwmNotification();
				}
				else if((TIM2->SR&(1<<4))!=0)
				{
					TIM2->SR|=1<<4;
					Pwm_Config.Config_Pwm.Channel_Config[3].PwmNotification();
				}
				else
				{
					//
				}
				break;
			default:
				//
				break;
		}
	}
	else if(Pwm_Config.Config_Pwm.Channel_Config[PwmChannelId_0].PwmPolarity==PWM_LOW)
	{
		//counter matches the compare value act as a RISING EDGE
		// overflow act as a FALLING EDGE
		//ch 1
		switch (Flag_Notifications&0b11)
		{
			case PWM_RISING_EDGE:
				if((TIM2->SR&(1<<1))!=0)
				{
					TIM2->SR|=1<<1;
					Pwm_Config.Config_Pwm.Channel_Config[0].PwmNotification();
				}
				else
				{
					//
				}
				break;
			case PWM_FALLING_EDGE:
				if((TIM2->SR&(1<<0))!=0)
				{
					TIM2->SR|=1<<0;
					Pwm_Config.Config_Pwm.Channel_Config[0].PwmNotification();
				}
				else
				{
					//
				}
				break;
			case PWM_BOTH_EDGES:
				if((TIM2->SR&(1<<0))!=0)
				{
					TIM2->SR|=1<<0;
					Pwm_Config.Config_Pwm.Channel_Config[0].PwmNotification();
				}
				else if((TIM2->SR&(1<<1))!=0)
				{
					TIM2->SR|=1<<1;
					Pwm_Config.Config_Pwm.Channel_Config[0].PwmNotification();
				}
				else
				{
					//
				}
				break;
			default:
				//
				break;
		}
		//ch2
		switch ((Flag_Notifications&(0b11<<2))>>2)
		{
			case PWM_RISING_EDGE:
				if((TIM2->SR&(1<<2))!=0)
				{
					TIM2->SR|=1<<2;
					Pwm_Config.Config_Pwm.Channel_Config[1].PwmNotification();
				}
				else
				{
					//
				}
				break;
			case PWM_FALLING_EDGE:
				if((TIM2->SR&(1<<0))!=0)
				{
					TIM2->SR|=1<<0;
					Pwm_Config.Config_Pwm.Channel_Config[1].PwmNotification();
				}
				else
				{
					//
				}
				break;
			case PWM_BOTH_EDGES:
				if((TIM2->SR&(1<<0))!=0)
				{
					TIM2->SR|=1<<0;
					Pwm_Config.Config_Pwm.Channel_Config[1].PwmNotification();
				}
				else if((TIM2->SR&(1<<2))!=0)
				{
					TIM2->SR|=1<<2;
					Pwm_Config.Config_Pwm.Channel_Config[1].PwmNotification();
				}
				else
				{
					//
				}
				break;
			default:
				//
				break;
		}
		//ch 3
		switch ((Flag_Notifications&(0b11<<4))>>4)
		{
			case PWM_RISING_EDGE:
				if((TIM2->SR&(1<<3))!=0)
				{
					TIM2->SR|=1<<3;
					Pwm_Config.Config_Pwm.Channel_Config[2].PwmNotification();
				}
				else
				{
					//
				}
				break;
			case PWM_FALLING_EDGE:
				if((TIM2->SR&(1<<0))!=0)
				{
					TIM2->SR|=1<<0;
					Pwm_Config.Config_Pwm.Channel_Config[2].PwmNotification();
				}
				else
				{
					//
				}
				break;
			case PWM_BOTH_EDGES:
				if((TIM2->SR&(1<<0))!=0)
				{
					TIM2->SR|=1<<0;
					Pwm_Config.Config_Pwm.Channel_Config[2].PwmNotification();
				}
				else if((TIM2->SR&(1<<3))!=0)
				{
					TIM2->SR|=1<<3;
					Pwm_Config.Config_Pwm.Channel_Config[2].PwmNotification();
				}
				else
				{
					//
				}
				break;
			default:
				//
				break;
		}
		//ch 4
		switch ((Flag_Notifications&(0b11<<6))>>6)
		{
			case PWM_RISING_EDGE:
				if((TIM2->SR&(1<<4))!=0)
				{
					TIM2->SR|=1<<4;
					Pwm_Config.Config_Pwm.Channel_Config[3].PwmNotification();
				}
				else
				{
					//
				}
				break;
			case PWM_FALLING_EDGE:
				if((TIM2->SR&(1<<0))!=0)
				{
					TIM2->SR|=1<<0;
					Pwm_Config.Config_Pwm.Channel_Config[3].PwmNotification();
				}
				else
				{
					//
				}
				break;
			case PWM_BOTH_EDGES:
				if((TIM2->SR&(1<<0))!=0)
				{
					TIM2->SR|=1<<0;
					Pwm_Config.Config_Pwm.Channel_Config[3].PwmNotification();
				}
				else if((TIM2->SR&(1<<4))!=0)
				{
					TIM2->SR|=1<<4;
					Pwm_Config.Config_Pwm.Channel_Config[3].PwmNotification();
				}
				else
				{
					//
				}
				break;
			default:
				//
				break;
		}
	}
	else
	{
		//
	}
}

