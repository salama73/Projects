/******************************************************************************
* @Module      :	 PWM
* @File Name   :	 Pwm.h
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
#ifndef PWM_H_
#define PWM_H_

/*****************************************************************************
							Source File Version Informations
*****************************************************************************/
#define PWM_VERSION_ID							37
#define VENDOR_ID								100
#define PWM_AR_RELEASE_MAJOR_VERSION			4
#define PWM_AR_RELEASE_MINOR_VERSION			8
#define PWM_AR_RELEASE_PATCH_VERSION		    0
#define PWM_SW_RELEASE_MAJOR_VERSION			1
#define PWM_SW_RELEASE_MINOR_VERSION			0
#define PWM_SW_RELEASE_PATCH_VERSION		    0
/*****************************************************************************
							Includes
*****************************************************************************/
#include "../Common_Module/Det.h"
#include "Pwm_Cfg.h"
#include "../Common_Module/Std_Types.h"
// AUTOSAR checking Std_Version
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PWM_AR_RELEASE_MAJOR_VERSION)\
||  (STD_TYPES_AR_RELEASE_MINOR_VERSION  != PWM_AR_RELEASE_MINOR_VERSION)\
||  (STD_TYPES_AR_RELEASE_PATCH_VERSION  != PWM_AR_RELEASE_PATCH_VERSION))
#error "The Autosar version of Std_Types.h does not match the Port version"
#endif
/******************************************************************************
                      API Service Id Macros
******************************************************************************/
#define PWM_INIT_ID									(uint8)0x00
#define PWM_DEINIT_ID								(uint8)0x01
#define PWM_SETDUTYCYCLE_ID							(uint8)0x02
#define PWM_SETPERIODANDDUTY_ID						(uint8)0x03
#define PWM_SETOUTPUTTOIDLE_ID						(uint8)0x04
#define PWM_GETOUTPUTSTATE_ID						(uint8)0x05
#define PWM_DISABLENOTIFICATION_ID					(uint8)0x06
#define PWM_ENABLENOTIFICATION_ID					(uint8)0x07
#define PWM_GETVERSIONINFO_ID						(uint8)0x08
#define PWM_SETPOWERSTATE_ID						(uint8)0x09
#define PWM_GETCURRENTPOWERSTATE_ID					(uint8)0x0A
/*******************************************************************************
                      DET Error Codes
*******************************************************************************/
//API Pwm_Init service called with wrong parameter
#define PWM_E_INIT_FAILED							(uint8)0x10
//API service used without module initialization
#define PWM_E_UNINIT								(uint8)0x11
//API service used with an invalid channel Identifier
#define PWM_E_PARAM_CHANNEL							(uint8)0x12
//Usage of unauthorized PWM service on PWM channel configured a fixed period
#define PWM_E_PERIOD_UNCHANGEABLE					(uint8)0x13
//API Pwm_Init service called while the PWM driver has already been initialised
#define PWM_E_ALREADY_INITIALIZED					(uint8)0x14
//API Pwm_GetVersionInfo is called with a NULL parameter.
#define PWM_E_PARAM_POINTER							(uint8)0x15
//API Pwm_SetPowerState is called while the PWM module is still in use.
#define PWM_E_NOT_DISENGAGED 						(uint8)0x16
//The requested power state is not supported by the PWM module.
#define PWM_E_POWER_STATE_NOT_SUPPORTED				(uint8)0x17
//The requested power state is not reachable from the current one
#define PWM_E_TRANSITION_NOT_POSSIBLE				(uint8)0x18
//API Pwm_SetPowerState has been called without having called the API Pwm_PreparePowerState before
#define PWM_E_PERIPHERAL_NOT_PREPARED				(uint8)0x19
/*****************************************************************************
							 Type definitions
*****************************************************************************/
#define PWM_NOT_INITIALIZED	0U
#define PWM_INITIALIZED		1U
#define Max_Num_CH	4
//Numeric identifier of a PWM channel.
typedef uint8 Pwm_ChannelType;
// Definition of the period of a PWM channel.
typedef float32 Pwm_PeriodType;
//Output state of a PWM channel.
typedef enum
{
	//The PWM channel is in high state
	PWM_HIGH,
	//The PWM channel is in low state
	PWM_LOW
}Pwm_OutputStateType;
//Definition of the type of edge notification of a PWM channel.
typedef enum
{
	// Notification will be called when a rising edge occurs on the PWM output signal.
	PWM_RISING_EDGE,
	// Notification will be called when a falling edge occurs on the PWM output signal.
	PWM_FALLING_EDGE,
	//Notification will be called when either a rising edge or falling edge occur on the PWM output signal.
	PWM_BOTH_EDGES
}Pwm_EdgeNotificationType;
// Defines the class of a PWM channel
typedef enum
{
	// The PWM channel has a variable period. The duty cycle and the period can be changed.
	PWM_VARIABLE_PERIOD,
	// The PWM channel has a fixed period. Only the duty cycle can be changed.
	PWM_FIXED_PERIOD,
}Pwm_ChannelClassType;
//Result of the requests related to power state transitions.
typedef enum
{
	// Power state change executed.
	PWM_SERVICE_ACCEPTED,
	//PWM Module not initialized
	PWM_NOT_INIT,
	//Wrong API call sequence
	PWM_SEQUENCE_ERROR,
	// The HW module has a failure which prevents it to enter the required power state.
	PWM_HW_FAILURE,
	// PWM Module does not support the requested power state.
	PWM_POWER_STATE_NOT_SUPP,
	//PWM Module cannot transition directly from the current power state to the requested power state or the HW peripheral is still busy.
	PWM_TRANS_NOT_POSSIBLE
}Pwm_PowerStateRequestResultType;
// Power state currently active or set as target power state.
typedef enum
{
	// Full Power
	PWM_FULL_POWER,
	// Half Power
	PWM_HALF_POWER
}Pwm_PowerStateType;
/************************************************************************************
Name			:           	PwmChannel
Parent Container: 				PwmChannelConfigSet
Description		:				Configuration of an individual PWM channel.
Type			:               Container
*************************************************************************************/
typedef struct
{
	//Only the duty cycle can be changed or Duty Cycle and period can be changed.
	Pwm_ChannelClassType PwmChannelClass;
	//Channel Id of the PWM channel. This value will be assigned to the symbolic name derived of the PwmChannel container short name
	Pwm_ChannelType PwmChannelId;
	//Value of duty cycle used for Initialization 0 represents 0% 0x8000 represents 100%
	uint16 PwmDutycycleDefault;
	//The parameter PWM_IDLE_STATE represents the output state of the PWM after the signal is stopped
	Pwm_OutputStateType PwmIdleState;
	//Definition of the Callback function.Default value "NULL"
	void(*PwmNotification)(void);
	//Value of period used for Initialization(in seconds).
	Pwm_PeriodType PwmPeriodDefault;
	//Defines the starting polarity of each PWM channel.
	Pwm_OutputStateType PwmPolarity;

}PwmChannel;
/************************************************************************************
Name			:           	PwmChannelConfigSet
Parent Container: 				PWM
Description		:				This container contains the configuration parameters and
								sub containers of the AUTOSAR Pwm module.
Type			:               Container
*************************************************************************************/
typedef struct
{
	PwmChannel Channel_Config[Max_Num_CH];
}PwmChannelConfigSet;
/************************************************************************************
Name			:           	Port
Parent Container: 				None
Description		:				This is the type of data structure containing the initialization data for the PWM driver.
Type			:               Structure
*************************************************************************************/
typedef struct
{
	PwmChannelConfigSet Config_Pwm;
}Pwm_ConfigType;
extern Pwm_ConfigType PWM_Config;
/*************************************************************************
                               APIS
*************************************************************************/
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
void Pwm_Init (const Pwm_ConfigType* ConfigPtr);
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
void Pwm_DeInit (void);
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
void Pwm_SetDutyCycle (Pwm_ChannelType ChannelNumber,uint16 DutyCycle);
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
void Pwm_SetPeriodAndDuty (Pwm_ChannelType ChannelNumber,Pwm_PeriodType Period,uint16 DutyCycle);
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
void Pwm_SetOutputToIdle (Pwm_ChannelType ChannelNumber);
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
Pwm_OutputStateType Pwm_GetOutputState (Pwm_ChannelType ChannelNumber);
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
void Pwm_DisableNotification (Pwm_ChannelType ChannelNumber);
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
void Pwm_EnableNotification (Pwm_ChannelType ChannelNumber,Pwm_EdgeNotificationType Notification);
#endif /* PWM_H_ */
