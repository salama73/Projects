/******************************************************************************
* @Module      :	 PWM
* @File Name   :	 Pwm_Cfg.h
* @Description :	 the Pre-compile configuration of the AUTOSAR Basic Software module PWM Driver.
* Author       :	 Salama Mohamed
*******************************************************************************/
/******************************************************************************
* Project				: *********
* Platform				: STM32F103C8
* Autosar Version		: 4.8.0
* SW Version		    : 1.0.0
******************************************************************************/
#ifndef PWM_CFG_H_
#define PWM_CFG_H_

/*****************************************************************************
							Source File Version Informations
*****************************************************************************/
#define PWM_VERSION_ID							    37
#define VENDOR_ID								    100
#define PWM_CFG_AR_RELEASE_MAJOR_VERSION			4
#define PWM_CFG_AR_RELEASE_MINOR_VERSION			8
#define PWM_CFG_AR_RELEASE_PATCH_VERSION		    0
#define PWM_CFG_SW_RELEASE_MAJOR_VERSION			1
#define PWM_CFG_SW_RELEASE_MINOR_VERSION			0
#define PWM_CFG_SW_RELEASE_PATCH_VERSION		    0
/*****************************************************************************
							Includes
*****************************************************************************/
#include "../Common_Module/Std_Types.h"
/******************************************************************************
			Pre-compile configuration parameters of the PWM driver.
*******************************************************************************/
//Switch for enabling the update of the duty cycle parameter at the end of the current period.
#define PwmDevErrorDetect				TRUE
//Switch for enabling the update of the duty cycle parameter at the end of the current period.
#define PwmDutycycleUpdatedEndperiod	TRUE
//Specifies the InstanceId of this module instance
#define PwmIndex_Zero					(uint8)0
//Switch to indicate that the notifications are supported
#define PwmNotificationSupported		TRUE
//Switch for enabling the update of the period parameter at the end of the current period.
#define PwmPeriodUpdatedEndperiod 		TRUE
//Channel Id of the PWM channel. This value will be assigned to the symbolic name derived of the PwmChannel container short name.
#define PwmChannelId_0					(uint8)0
#define PwmChannelId_1					(uint8)1
#define PwmChannelId_2					(uint8)2
#define PwmChannelId_3					(uint8)3
//PwmDutycycleDefault
#define Default_Dutycycle				(uint16)0X6000
//PwmPeriodDefault
#define Default_Period					(float32)0.02
//Adds / removes the service Pwm_DeInit() from the code.
#define PwmDeInitApi					TRUE
//Adds / removes the service Pwm_GetOutputState() from the code.
#define PwmGetOutputState				TRUE
//Adds / removes the service Pwm_SetDutyCycle() from the code.
#define PwmSetDutyCycle					TRUE
//Adds / removes the service Pwm_SetOutputToIdle() from the code.
#define PwmSetOutputToIdle				TRUE
//Adds / removes the service Pwm_SetPeriodAndDuty() from the code.
#define PwmSetPeriodAndDuty				TRUE
//Switch to indicate that the Pwm_ GetVersionInfo is supported
#define PwmVersionInfoApi				TRUE
#endif /* PWM_CFG_H_ */
