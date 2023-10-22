/******************************************************************************
* @Module      :	 PWM
* @File Name   :	 Pwm.c
* @Description :	This specification specifies the functionality, API and the configuration of the
					AUTOSAR Basic Software module PWM driver.
* Author       :	Salama Mohamed
*******************************************************************************/
/******************************************************************************
* Project				: ---------------
* Platform				: STM32F103C8
* Autosar Version		: 4.8.0
* SW Version		    : 1.0.0
******************************************************************************/
/*****************************************************************************
							Includes
*****************************************************************************/
#include "Pwm.h"

#include "../Common_Module/stm32f103x6.h"
/******************************************************************************
 	 	 	 	 	 	 	 	 	 Variables
******************************************************************************/
uint8 PWM_State=PWM_NOT_INITIALIZED;
uint8 Flag_Mutex=0;
Pwm_ConfigType Pwm_Config;
/*
 2bit for each channel
 00--->PWM_RISING_EDGE
 01--->PWM_FALLING_EDGE
 10--->PWM_BOTH_EDGES
 11--->Disable
 */
uint8 Flag_Notifications=0;
/*************************************************************************************
 	 	 	 	 	 	 	 	 Local function
**************************************************************************************/
void Mutex_Lock(Pwm_ChannelType CH_ID)
{

}
void Mutex_Unlock(Pwm_ChannelType CH_ID)
{

}
/*************************************************************************************
 	 	 	 	 	 	 	 	 APIS
*************************************************************************************/
/***********************************************************************************
 * Service name     	: Pwm_Init
 * Service ID[hex]   	: 0x00
 * Sync/Async        	: Synchronous
 * Reentrancy        	: Non Reentrant
 * Parameters (in)   	: ConfigPtr
                          Pointer to configuration set
 * Parameters (inout)	: None
 * Parameters (out)  	: None
 * Return value     	: None
 * Description       	: Service for PWM initialization
 ********************************************************************************/
void Pwm_Init (const Pwm_ConfigType* ConfigPtr)
{
	uint32 Max_Counter=0;
	uint32 Duty_cycle=0;
	Pwm_Config=*ConfigPtr;
#if(PwmDevErrorDetect==TRUE)
	/*
	 [SWS_Pwm_00118] If development error detection is enabled, calling the routine
	 Pwm_Init while the PWM driver and hardware are already initialized will cause a development
	 error PWM_E_ALREADY_INITIALIZED. The desired functionality shall be left without any action.
	 */
	if(PWM_State==PWM_INITIALIZED)
	{
		/*
		 [SWS_Pwm_00121] A re-initialization of the Pwm driver by executing the
		 Pwm_Init() function requires a de-initialization before by executing a Pwm_DeInit().
		*/
		Det_ReportError(PWM_VERSION_ID,PwmIndex_Zero, PWM_INIT_ID, PWM_E_ALREADY_INITIALIZED);
	}
	else
	{
		//
	}
	//API Pwm_GetVersionInfo is called with a NULL parameter.
	if(ConfigPtr==NULL_PTR)
	{
		Det_ReportError(PWM_VERSION_ID,PwmIndex_Zero, PWM_INIT_ID, PWM_E_PARAM_POINTER);
	}
	else
	{
		//
	}
#endif
	//enable interrupt
	NVIC_IRQ28_TIM2_Enable();
	for(int ch_index=0;ch_index<=Max_Num_CH;ch_index++)
	{
		TIM2->DIER|=1<<(Pwm_Config.Config_Pwm.Channel_Config[ch_index].PwmChannelId);
	}
	/*
	 [SWS_Pwm_00052] The function Pwm_Init shall disable all notifications.
	 */
	for(int ch_index=0;ch_index<Max_Num_CH;ch_index++)
	{
		Flag_Notifications|=0b11<<ch_index;
	}
	// Only counter overflow/underflow generates an update interrupt
	TIM2->CR1|=1<<2;
	// Auto-reload preload enable
	TIM2->CR1|=1<<7;
	// output state of the PWM after the signal is stopped
	for(int ch_index=0;ch_index<Max_Num_CH;ch_index++)
	{
		if(ConfigPtr->Config_Pwm.Channel_Config[ch_index].PwmIdleState==PWM_HIGH)
		{
			//1: OC1 active low.
			TIM2->CCER|=1<<(1+(ch_index*4));
		}
		else if(ConfigPtr->Config_Pwm.Channel_Config[ch_index].PwmIdleState==PWM_LOW)
		{
			//0: OC1 active high.
			TIM2->CCER&=~(1<<(1+(ch_index*4)));
		}
		else
		{
			//Error
		}
	}
	//Defines the starting polarity of each PWM channel.
	for(int ch_index=0;ch_index<Max_Num_CH;ch_index++)
	{
		if(ConfigPtr->Config_Pwm.Channel_Config[ch_index].PwmPolarity==PWM_HIGH)
		{
			if(ConfigPtr->Config_Pwm.Channel_Config[ch_index].PwmIdleState==PWM_LOW)
			{
				//110: PWM mode_1 channel x is active as long as TIMx_CNT<TIMx_CCR1 else inactive
				switch(ConfigPtr->Config_Pwm.Channel_Config[ch_index].PwmChannelId)
				{
				case PwmChannelId_0:
					TIM2->CCMR1 |=13<<3;
					break;
				case PwmChannelId_1:
					TIM2->CCMR1 |=13<<11;
					break;
				case PwmChannelId_2:
					TIM2->CCMR2 |=13<<3;
					break;
				case PwmChannelId_3:
					TIM2->CCMR2 |=13<<11;
					break;
				default:
					//Error
					break;
				}
			}
			else if(ConfigPtr->Config_Pwm.Channel_Config[ch_index].PwmIdleState==PWM_HIGH)
			{
				//111: PWM mode_2 channel 1 is inactive as long as TIMx_CNT<TIMx_CCR1 else active
				switch(ConfigPtr->Config_Pwm.Channel_Config[ch_index].PwmChannelId)
				{
				case PwmChannelId_0:
					TIM2->CCMR1 |=15<<3;
					break;
				case PwmChannelId_1:
					TIM2->CCMR1 |=15<<11;
					break;
				case PwmChannelId_2:
					TIM2->CCMR2 |=15<<3;
					break;
				case PwmChannelId_3:
					TIM2->CCMR2 |=15<<11;
					break;
				default:
					//Error
					break;
				}
			}
			else
			{
				//Error
			}
		}
		else if(ConfigPtr->Config_Pwm.Channel_Config[ch_index].PwmPolarity==PWM_LOW)
		{
			//111: PWM mode_2 channel 1 is inactive as long as TIMx_CNT<TIMx_CCR1 else active
			if(ConfigPtr->Config_Pwm.Channel_Config[ch_index].PwmIdleState==PWM_HIGH)
			{
				//110: PWM mode_1 channel x is active as long as TIMx_CNT<TIMx_CCR1 else inactive
				switch(ConfigPtr->Config_Pwm.Channel_Config[ch_index].PwmChannelId)
				{
				case PwmChannelId_0:
					TIM2->CCMR1 |=13<<3;
					break;
				case PwmChannelId_1:
					TIM2->CCMR1 |=13<<11;
					break;
				case PwmChannelId_2:
					TIM2->CCMR2 |=13<<3;
					break;
				case PwmChannelId_3:
					TIM2->CCMR2 |=13<<11;
					break;
				default:
					//Error
					break;
				}
			}
			else if(ConfigPtr->Config_Pwm.Channel_Config[ch_index].PwmIdleState==PWM_LOW)
			{
				//111: PWM mode_2 channel 1 is inactive as long as TIMx_CNT<TIMx_CCR1 else active
				switch(ConfigPtr->Config_Pwm.Channel_Config[ch_index].PwmChannelId)
				{
				case PwmChannelId_0:
					TIM2->CCMR1 |=15<<3;
					break;
				case PwmChannelId_1:
					TIM2->CCMR1 |=15<<11;
					break;
				case PwmChannelId_2:
					TIM2->CCMR2 |=15<<3;
					break;
				case PwmChannelId_3:
					TIM2->CCMR2 |=15<<11;
					break;
				default:
					//Error
					break;
				}
			}
			else
			{
				//Error
			}
		}
		else
		{
			//Error
		}
	}
	// set Prescalers (frequency is 1MH)
	TIM2->PSC =7;
	//Value of period used for Initialization(in seconds)
	Max_Counter=1000000*ConfigPtr->Config_Pwm.Channel_Config[PwmChannelId_0].PwmPeriodDefault;
	TIM2->ARR=Max_Counter;
	//Value of duty cycle used for Initialization 0 represents 0% 0x8000 represents 100%
	for(int ch_index=0;ch_index<Max_Num_CH;ch_index++)
	{
		Duty_cycle=(ConfigPtr->Config_Pwm.Channel_Config[PwmChannelId_0].PwmDutycycleDefault/32768.0)*Max_Counter;
		switch(ConfigPtr->Config_Pwm.Channel_Config[ch_index].PwmChannelId)
		{
		case PwmChannelId_0:
			TIM2->CCR1=Duty_cycle;
			break;
		case PwmChannelId_1:
			TIM2->CCR2=Duty_cycle;
			break;
		case PwmChannelId_2:
			TIM2->CCR3=Duty_cycle;
			break;
		case PwmChannelId_3:
			TIM2->CCR4=Duty_cycle;
			break;
		default:
			//Error
			break;
		}
	}
	//Compare x output enable
	for(int ch_index=0;ch_index<Max_Num_CH;ch_index++)
	{
		TIM2->CCER|=1<<(ch_index*4);
	}
	// Counter enable
	TIM2->CR1|=1<<0;
	PWM_State=PWM_INITIALIZED;
}
/***********************************************************************************
 * Service name     	: Pwm_DeInit
 * Service ID[hex]   	: 0x01
 * Sync/Async        	: Synchronous
 * Reentrancy        	: Non Reentrant
 * Parameters (in)   	: None
 * Parameters (inout)	: None
 * Parameters (out)  	: None
 * Return value     	: None
 * Description       	: Service for PWM De-Initialization.
 ********************************************************************************/
void Pwm_DeInit (void)
{
	/*
	 [SWS_Pwm_00011] The function Pwm_DeInit shall set the state of the PWM output
	 signals to the idle state.
	*/
	//Compare x output disable
	for(int ch_index=0;ch_index<Max_Num_CH;ch_index++)
	{
		TIM2->CCER&=~(1<<(ch_index*4));
	}
	/*
	 [SWS_Pwm_00012] The function Pwm_DeInit shall disable PWM interrupts and
	 PWM signal edge notifications.
	 */
	NVIC_IRQ28_TIM2_Disable();
	for(int ch_index=0;ch_index<Max_Num_CH;ch_index++)
	{
		//disable PWM signal edge notifications.
		Flag_Notifications|=0b11<<ch_index;
		//disable PWM interrupts
		TIM2->DIER&=~(1<<(Pwm_Config.Config_Pwm.Channel_Config[ch_index].PwmChannelId+1));
	}

	// Counter disable
	TIM2->CR1&=~(1<<0);
	PWM_State=PWM_NOT_INITIALIZED;
}
/***********************************************************************************
 * Service name     	: Pwm_SetDutyCycle
 * Service ID[hex]   	: 0x02
 * Sync/Async        	: Asynchronous
 * Reentrancy        	: Reentrant for different channel numbers
 * Parameters (in)   	: ChannelNumber
 	 	 	 	 	 	  Numeric identifier of the PWM
 *Parameters (in)   	: DutyCycle
						  Min=0x0000 Max=0x8000
 *
 * Parameters (inout)	: None
 * Parameters (out)  	: None
 * Return value     	: None
 * Description       	: Service sets the duty cycle of the PWM channel.
 ********************************************************************************/
void Pwm_SetDutyCycle (Pwm_ChannelType ChannelNumber,uint16 DutyCycle)
{
	uint16 Duty_cycle=0;
#if(PwmDevErrorDetect==TRUE)
	if(ChannelNumber<PwmChannelId_0||ChannelNumber>PwmChannelId_3)
	{
		Det_ReportError(PWM_VERSION_ID,PwmIndex_Zero, PWM_SETDUTYCYCLE_ID, PWM_E_PARAM_CHANNEL);
	}
	else
	{
		//
	}
#endif
	/*
	 [SWS_Pwm_00014] ⌈When the requested duty cycle is either 0% or 100%, the
	 function
	 Pwm_SetDutyCycle shall set the PWM output state to either PWM_HIGH or
	 PWM_LOW, with regard to both the configured polarity parameter and the requested
	 duty cycle.
	 Thus for 0% requested Duty Cycle the output will be the inverse of the configured
	 polarity parameter, and for 100% Duty Cycle the output will be equal to the
	 configured polarity parameter.
	 */
	Duty_cycle=(DutyCycle/32768.0)*TIM2->ARR;
	//Value of duty cycle used for Initialization 0 represents 0% 0x8000 represents 100%
	switch(ChannelNumber)
	{
	case PwmChannelId_0:
		TIM2->CCR1=Duty_cycle;
		break;
	case PwmChannelId_1:
		TIM2->CCR2=Duty_cycle;
		break;
	case PwmChannelId_2:
		TIM2->CCR3=Duty_cycle;
		break;
	case PwmChannelId_3:
		TIM2->CCR4=Duty_cycle;
		break;
	default:
		//Error
		break;
	}
	/*
	 [SWS_Pwm_20086] After the call of the function Pwm_SetOutputToIdle, channels
	 shall be reactivated using the Api Pwm_SetDutyCycle( ) to activate the PWM channel
	 with the old period.
	 */
	if((TIM2->CCER&(1<<ChannelNumber*4))==0)
	{
		TIM2->CCER|=1<<(ChannelNumber*4);
	}
	else
	{
		//
	}
	//to update
	TIM2->EGR |=1<<0;
}
/***********************************************************************************
 * Service name     	: Pwm_DeInit
 * Service ID[hex]   	: 0x03
 * Sync/Async        	: Asynchronous
 * Reentrancy        	: Reentrant for different channel numbers
 * Parameters (in)   	: ChannelNumber
 	 	 	 	 	 	  Numeric identifier of the PWM
 * Parameters (in)   	: Period
 	 	 	 	 	 	  Period of the PWM signal
 * Parameters (in)   	: DutyCycle
 	 	 	 	 	 	  Min=0x0000 Max=0x8000
 * Parameters (inout)	: None
 * Parameters (out)  	: None
 * Return value     	: None
 * Description       	: Service sets the period and the duty cycle of a PWM channel
 ********************************************************************************/
void Pwm_SetPeriodAndDuty (Pwm_ChannelType ChannelNumber,Pwm_PeriodType Period,uint16 DutyCycle)
{

}
/***********************************************************************************
 * Service name     	: Pwm_SetOutputToIdle
 * Service ID[hex]   	: 0x04
 * Sync/Async        	: Asynchronous
 * Reentrancy        	: Reentrant for different channel numbers
 * Parameters (in)   	: ChannelNumber
                          Numeric identifier of the PWM
 * Parameters (inout)	: None
 * Parameters (out)  	: None
 * Return value     	: None
 * Description       	: Service sets the PWM output to the configured Idle state
 ********************************************************************************/
#if(PwmSetOutputToIdle==TRUE)
void Pwm_SetOutputToIdle (Pwm_ChannelType ChannelNumber)
{
	/*
	 [SWS_Pwm_20086] After the call of the function Pwm_SetOutputToIdle, channels
	 shall be reactivated using the Api Pwm_SetDutyCycle( ) to activate the PWM channel
	 with the old period.
	 */
	//Compare x output disable
	TIM2->CCER&=~(1<<(ChannelNumber*4));
}
#endif
/***********************************************************************************
 * Service name     	: Pwm_GetOutputState
 * Service ID[hex]   	: 0x05
 * Sync/Async        	: Synchronous
 * Reentrancy        	: Reentrant for different channel numbers
 * Parameters (in)   	: ChannelNumber
                          Numeric identifier of the PWM
 * Parameters (inout)	: None
 * Parameters (out)  	: None
 * Return value     	: Pwm_OutputStateType
 	 	 	 	 	 	  PWM_HIGH The PWM output state is high
						  PWM_LOW The PWM output state is low
 * Description       	: Service to read the internal state of the PWM output signal
 ********************************************************************************/
Pwm_OutputStateType Pwm_GetOutputState (Pwm_ChannelType ChannelNumber)
{

}
/***********************************************************************************
 * Service name     	: Pwm_DisableNotification
 * Service ID[hex]   	: 0x06
 * Sync/Async        	: Asynchronous
 * Reentrancy        	: Reentrant for different channel numbers
 * Parameters (in)   	: ChannelNumber
                          Numeric identifier of the PWM
 * Parameters (inout)	: None
 * Parameters (out)  	: None
 * Return value     	: None
 * Description       	: Service to disable the PWM signal edge notification
 ********************************************************************************/
void Pwm_DisableNotification (Pwm_ChannelType ChannelNumber)
{
	/*
	 [SWS_Pwm_00023] ⌈The function Pwm_DisableNotification shall disable the PWM
	 signal edge notification.
	 */
	Flag_Notifications|=(0b11<<(ChannelNumber*2));
}
/***********************************************************************************
 * Service name     	: Pwm_EnableNotification
 * Service ID[hex]   	: 0x07
 * Sync/Async        	: Asynchronous
 * Reentrancy        	: Reentrant for different channel numbers
 * Parameters (in)   	: ChannelNumber
                          Numeric identifier of the PWM
 * Parameters (in)   	: Notification
		  	  	  	  	  Type of notification PWM_RISING_EDGE or PWM_FALLING_EDGE or PWM_BOTH_EDGES
 * Parameters (inout)	: None
 * Parameters (out)  	: None
 * Return value     	: None
 * Description       	: Service to enable the PWM signal edge notification according to notification parameter.
 ********************************************************************************/
void Pwm_EnableNotification (Pwm_ChannelType ChannelNumber,Pwm_EdgeNotificationType Notification)
{
	/*
	 [SWS_Pwm_00024] The function Pwm_EnableNotification shall enable the PWM
	 signal edge notification according to notification parameter.
	 */
	Flag_Notifications&=~(0b11<<(ChannelNumber*2));
	Flag_Notifications|=Notification<<(ChannelNumber*2);
	/*
	 [SWS_Pwm_00081] The function Pwm_EnableNotification shall cancel pending
	 interrupts
	 */
	TIM2->SR|=1<<(ChannelNumber+1);
}

