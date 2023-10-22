/******************************************************************************
* @Module      :	 Port
* @File Name   :	 Port.h
* @Description :	This specification specifies the functionality, API and the configuration of the AUTOSAR
					Basic Software module PORT Driver.
* Author       :	Salama Mohamed
*******************************************************************************/
/******************************************************************************
* Project				: Door_Lock_Indication
* Platform				: STM32F103C8
* Autosar Version		: 4.8.0
* SW Version		    : 1.0.0
******************************************************************************/
#ifndef PORT_H_
#define PORT_H_

/*****************************************************************************
							Source File Version Informations
*****************************************************************************/
#define PORT_VERSION_ID							40
#define PORT_AR_RELEASE_MAJOR_VERSION			4
#define PORT_AR_RELEASE_MINOR_VERSION			8
#define PORT_AR_RELEASE_PATCH_VERSION		    0
#define PORT_SW_RELEASE_MAJOR_VERSION			1
#define PORT_SW_RELEASE_MINOR_VERSION			0
#define PORT_SW_RELEASE_PATCH_VERSION		    0
#define VENDOR_ID								100
/*****************************************************************************
							Includes
*****************************************************************************/
#include "Port_Cfg.h"
#include "../Common_Module/Det.h"
#include "../Common_Module/Std_Types.h"
// AUTOSAR checking Std_Version
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
||  (STD_TYPES_AR_RELEASE_MINOR_VERSION  != PORT_AR_RELEASE_MINOR_VERSION)\
||  (STD_TYPES_AR_RELEASE_PATCH_VERSION  != PORT_AR_RELEASE_PATCH_VERSION))
#error "The Autosar version of Std_Types.h does not match the Port version"
#endif
/******************************************************************************
                      API Service Id Macros
 ******************************************************************************/
// Service ID for Port_Init
#define PORT_INIT_ID						(uint8)0x00
// Service ID for Port_SetPinDirection
#define PORT_SET_PIN_DIR_ID					(uint8)0x01
// Service ID for Port_RefreshPortDirection
#define PORT_REFRESH_PORT_DIR_ID			(uint8)0x02
// Service ID for Port_GetVersionInfo
#define PORT_GET_VERSION_INFO_ID			(uint8)0x03
// Service ID for Port_SetPinMode
#define PORT_SET_PIN_MODE_ID				(uint8)0x04
/*******************************************************************************
                      DET Error Codes
 *******************************************************************************/
// Invalid Port Pin ID requested
#define PORT_E_PARAM_PIN 					(uint8)0x0A
// Port Pin not configured as changeable
#define PORT_E_DIRECTION_UNCHANGEABLE 		(uint8)0x0B
// API Port_Init service called with wrong parameter
#define PORT_E_PARAM_CONFIG				 	(uint8)0x0C
// API Port_SetPinMode service called when Port Pin Mode passed not valid
#define PORT_E_PARAM_INVALID_MODE 			(uint8)0x0D
// API Port_SetPinMode service called when mode is unchangeable
#define PORT_E_MODE_UNCHANGEABLE 			(uint8)0x0E
// API service called without module initialization
#define PORT_E_UNINIT 						(uint8)0x0F
// APIs called with a Null Pointer
#define PORT_E_PARAM_POINTER 				(uint8)0x10
/*****************************************************************************
							 Type definitions
*****************************************************************************/
#define PORT_NOT_INITIALIZED	0U
#define PORT_INITIALIZED		1U
/*
 Shall cover all available port pins.
 The type should be chosen for the
 specific MCU platform (best performance).
*/
typedef  uint8	Port_PinType   ;
//Possible directions of a port pin.
typedef enum
{
	//Sets port pin as input.
	PORT_PIN_IN,
	//Sets port pin as output.
	PORT_PIN_OUT
} Port_PinDirectionType ;
/*
 As several port pin modes shall
 be configurable on one pin, the
 range shall be determined by the
 implementation.
 */
typedef enum
{
	PORT_PIN_MODE_ADC,
	PORT_PIN_MODE_CAN,
	PORT_PIN_MODE_DIO,
	PORT_PIN_MODE_PWM
}Port_PinModeType;
/************************************************************************************
Name			:           	PortPin
Parent Container: 				PortContainer
Description		:				Configuration of the individual port pins.
Type			:               Container
*************************************************************************************/
typedef struct
{
	/*The initial direction of the pin (IN or OUT). If the direction is not changeable,
	 the value configured here is fixed.
	 The direction must match the pin mode. E.g. a pin used for an ADC must be configured
	 to be an in port.
	*/
	Port_PinDirectionType PortPinDirection ;
	/*
	 Parameter to indicate if the direction is changeable on a port pin during runtime. true:
	 Port Pin direction changeable enabled. false: Port Pin direction changeable disabled.
	*/
	boolean PortPinDirectionChangeable;
	/*
	 Pin Id of the port pin. This value will be assigned to the symbolic name
	 derived from the port pin container short name.
	*/
	Port_PinType PortPinId;
	// Port pin mode from mode list for use with Port_Init() function
	Port_PinModeType PortPinInitialMode;
	// Port Pin Level value from Port pin list.
	uint8 PortPinLevelValue;
	// Port pin mode from mode list. Note that more than one mode is allowed by default.
	Port_PinModeType PortPinMode ;
	/*
	 Parameter to indicate if the mode is changeable on a port pin during runtime. True:
	 Port Pin mode changeable allowed. False: Port Pin mode changeable not permitted.
	*/
	boolean PortPinModeChangeable;
	// Activation of internal pull-ups
	boolean Pull_UP;
	// Slew rate contro
	uint8 Slew_Rate;
	// Pin driven mode (push-pull / open drain).
	uint8 Pin_Driven_Mode;
} PortPin;
/************************************************************************************
Name			:           	PortContainer
Parent Container: 				PortConfigSet
Description		:				Container collecting the PortPins.
Type			:               Container
*************************************************************************************/
typedef struct
{
	PortPin PortPin[PortNumberOfPortPins];
} PortContainer;
/************************************************************************************
Name			:           	PortConfigSet
Parent Container: 				Port
Description		:				This container contains the configuration parameters and sub
								containers of the AUTOSAR Port module
Type			:               Container
*************************************************************************************/
typedef struct
{
	PortContainer PortContainer;
}PortConfigSet;
/************************************************************************************
Name			:           	Port
Parent Container: 				PORT
Description		:				Configuration of the Port module.
Type			:               Structure
*************************************************************************************/
typedef struct
{
	PortPin PortPin[PortNumberOfPortPins];
}Port_ConfigType;
extern const Port_ConfigType Port;
/*************************************************************************
                               APIS
*************************************************************************/
/************************************************************************
* Service ID [hex]	:	0x00
* Service Name		:	Port_Init
* Sync/Async		:	Synchronous
* Reentrancy		:	Non reentrant
* Parameters (in)	:	ConfigPtr (Pointer to configuration set).
* Parameters (inout):	None
* Parameters (out)	:	None
* Return value		:	None
* Description		:	Initializes the Port Driver module.
***********************************************************************/
void Port_Init( const Port_ConfigType* ConfigPtr ) ;
/************************************************************************
* Service ID [hex]	:	0x01
* Service Name		:	Port_SetPinDirection
* Sync/Async		:	Synchronous
* Reentrancy		:	Reentrant
* Parameters (in)	:	Pin (Port Pin ID number)
						Direction (Port Pin Direction)
* Parameters (inout):	None
* Parameters (out)	:	None
* Return value		:	None
* Description		:	Sets the port pin direction
***********************************************************************/
void Port_SetPinDirection ( Port_PinType Pin , Port_PinDirectionType Direction ) ;
/************************************************************************
* Service ID [hex]	:	0x02
* Service Name		:	Port_RefreshPortDirection
* Sync/Async		:	Synchronous
* Reentrancy		:	Non Reentrant
* Parameters (in)	:	None
* Parameters (inout):	None
* Parameters (out)	:	None
* Return value		:	None
* Description		:	Refreshes port direction
***********************************************************************/
void Port_RefreshPortDirection (void);
/************************************************************************
* Service ID [hex]	:	0x03
* Service Name		:	Port_GetVersionInfo
* Sync/Async		:	Synchronous
* Reentrancy		:	Reentrant
* Parameters (in)	:	None
* Parameters (inout):	None
* Parameters (out)	:	versioninfo (Pointer to where to store the version information of this module).
* Return value		:	None
* Description		:	Returns the version information of this module.
***********************************************************************/
void Port_GetVersionInfo ( Std_VersionInfoType* versioninfo ) ;
/************************************************************************
* Service ID [hex]	:	0x04
* Service Name		:	Port_SetPinMode
* Sync/Async		:	Synchronous
* Reentrancy		:	Reentrant
* Parameters (in)	:	Pin (Port Pin ID number)
						Mode (New Port Pin mode to be set on port pin).
* Parameters (inout):	None
* Parameters (out)	:	None
* Return value		:	None
* Description		:	Mode New Port Pin mode to be set on port pin.
***********************************************************************/
void Port_SetPinMode ( Port_PinType Pin , Port_PinModeType Mode ) ;
#endif /* PORT_H_ */
