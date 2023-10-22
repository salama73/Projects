/******************************************************************************
* @Module      :	 Port
* @File Name   :	 Port_Cfg.h
* @Description :	 the Pre-compile configuration of the AUTOSAR Basic Software module PORT Driver.
* Author       :	 Salama Mohamed
*******************************************************************************/
/******************************************************************************
* Project				: Door_Lock_Indication
* Platform				: STM32F103C8
* Autosar Version		: 4.8.0
* SW Version		    : 1.0.0
******************************************************************************/
#ifndef PORT_CFG_H_
#define PORT_CFG_H_
/*****************************************************************************
							Source File Version Informations
*****************************************************************************/
#define PORT_VERSION_ID							    40
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION			4
#define PORT_CFG_AR_RELEASE_MINOR_VERSION			8
#define PORT_CFG_AR_RELEASE_PATCH_VERSION		    0
#define PORT_CFG_SW_RELEASE_MAJOR_VERSION			1
#define PORT_CFG_SW_RELEASE_MINOR_VERSION			0
#define PORT_CFG_SW_RELEASE_PATCH_VERSION		    0
#define VENDOR_ID								    100
/******************************************************************************
			Module wide configuration parameters of the PORT driver.
*******************************************************************************/
//The number of specified PortPins in this PortContainer.
#define PortNumberOfPortPins	32
/*
 Switches the development error detection and notification on or off.
 true: detection and notification is enabled.
 false: detection and notification is disabled.
*/
#define PortDevErrorDetect			TRUE
/*
 Pre-processor switch to enable / disable the use of the function Port_SetPinDirection().
*/
#define PortSetPinDirectionApi		TRUE
/*
 Pre-processor switch to enable / disable the use of the function Port_SetPinMode().
*/
#define PortSetPinModeApi			TRUE
/*
 Pre-processor switch to enable / disable the API to read out the modules version information.
*/
#define PortVersionInfoApi			TRUE
#define GPIO_Pin_Driven_Mode_PP		0
#define GPIO_Pin_Driven_Mode_OD		1
#define GPIO_Slew_Rate_10M			1
#define GPIO_Slew_Rate_2M			2
#define GPIO_Slew_Rate_50M			3
#define PORT_INSTANCE_ZERO			0
/*
 [SWS_Port_00207] dThese symbolic names for the individual port pins (e.g. PORT_
 A_PIN_0) shall be defined in the configuration tool
 */
#define  PORT_A_PIN_0		((Port_PinType)1)
#define  PORT_A_PIN_1		((Port_PinType)2)
#define  PORT_A_PIN_2		((Port_PinType)3)
#define  PORT_A_PIN_3		((Port_PinType)4)
#define  PORT_A_PIN_4		((Port_PinType)5)
#define  PORT_A_PIN_5		((Port_PinType)6)
#define  PORT_A_PIN_6		((Port_PinType)7)
#define  PORT_A_PIN_7		((Port_PinType)8)
#define  PORT_A_PIN_8		((Port_PinType)9)
#define  PORT_A_PIN_9		((Port_PinType)10)
#define  PORT_A_PIN_10		((Port_PinType)11)
#define  PORT_A_PIN_11		((Port_PinType)12)
#define  PORT_A_PIN_12		((Port_PinType)13)
#define  PORT_A_PIN_13		((Port_PinType)14)
#define  PORT_A_PIN_14		((Port_PinType)15)
#define  PORT_A_PIN_15		((Port_PinType)16)
#define  PORT_B_PIN_0		((Port_PinType)17)
#define  PORT_B_PIN_1		((Port_PinType)18)
#define  PORT_B_PIN_2		((Port_PinType)19)
#define  PORT_B_PIN_3		((Port_PinType)20)
#define  PORT_B_PIN_4		((Port_PinType)21)
#define  PORT_B_PIN_5		((Port_PinType)22)
#define  PORT_B_PIN_6		((Port_PinType)23)
#define  PORT_B_PIN_7		((Port_PinType)24)
#define  PORT_B_PIN_8		((Port_PinType)25)
#define  PORT_B_PIN_9		((Port_PinType)26)
#define  PORT_B_PIN_10		((Port_PinType)27)
#define  PORT_B_PIN_11		((Port_PinType)28)
#define  PORT_B_PIN_12		((Port_PinType)29)
#define  PORT_B_PIN_13		((Port_PinType)30)
#define  PORT_B_PIN_14		((Port_PinType)31)
#define  PORT_B_PIN_15		((Port_PinType)32)
#define  PORT_C_PIN_13		((Port_PinType)46)
#define  PORT_C_PIN_14		((Port_PinType)47)
#define  PORT_C_PIN_15		((Port_PinType)48)
#endif /* PORT_CFG_H_ */
