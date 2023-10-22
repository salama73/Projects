/******************************************************************************
* @Module		: Common
* @File Name	: StandardTypes.h
* @Description 	: This document specifies the AUTOSAR standard types header file. It contains all
				  types that are used across several modules of the basic software and that are
				  platform and compiler independent.
* Author		:Salama Mohamed
*******************************************************************************/

/******************************************************************************
* Project				: Door_Lock_Indication
* Platform				: STM32F103C8
* Autosar Version		: 4.8.0
* SW Version		    : 1.0.0
******************************************************************************/

#ifndef STD_TYPES_H
#define STD_TYPES_H

/*****************************************************************************
							Source File Version Informations
*****************************************************************************/
#define STD_VERSION_ID									49
#define STD_TYPES_AR_RELEASE_MAJOR_VERSION				4
#define STD_TYPES_AR_RELEASE_MINOR_VERSION				8
#define STD_TYPES_AR_RELEASE_PATCH_VERSION				0
#define STD_TYPES_SW_RELEASE_MAJOR_VERSION				1
#define STD_TYPES_SW_RELEASE_MINOR_VERSION				0
#define STD_TYPES_SW_RELEASE_PATCH_VERSION			    0
/*****************************************************************************
							Includes
*****************************************************************************/
#include "../Common_Module/Platform_Types.h"
/*****************************************************************************
							Symbol and Module Data Types
*****************************************************************************/
//This type can be used as standard API return type which is shared between the RTE and the BSW modules
typedef uint8 Std_ReturnType ;
//Because E_OK is already defined within OSEK, the symbol E_OK has to be shared. To avoid name clashes and redefinition problems,
#ifndef STATUSTYPEDEFINED
#define STATUSTYPEDEFINED
#define E_OK		((Std_ReturnType)0x00U)
#endif
#define E_NOT_OK	((Std_ReturnType)0x01U)
//This type shall be used to request the version of a BSW module using the <Module name>_Get VersionInfo() function.
typedef struct  
{
	uint16 vendorID ;
	uint16 moduleID ;
	uint8 sw_major_version ;
	uint8 sw_minor_version ;
	uint8 sw_patch_version ;
}Std_VersionInfoType;
//The type of the Std_TransformerError
typedef uint8 Std_TransformerErrorCode ;
//Std_TransformerClass is an enumeration where each element represents a transformer class
typedef uint8 Std_TransformerClass ;
//Std_TransformerError represents a transformer error in the context of a certain transformer chain
typedef struct
{
	Std_TransformerErrorCode errorCode ;
	Std_TransformerClass transformerClass ;
}Std_TransformerError;
// Physical state 5V or 3.3V 
#define STD_HIGH 0x01U
// Physical state 0V
#define STD_LOW 0x00U
// Logical state active 
#define STD_ACTIVE 0x01U
// Logical state idle
#define STD_IDLE 0x00U
#define STD_ON 0x01U
#define STD_OFF 0x00U//The implementation shall provide the NULL_PTR define with a void pointer to zero definition.#define NULL_PTR ((void *)0)
#endif /* STD_TYPES_H */