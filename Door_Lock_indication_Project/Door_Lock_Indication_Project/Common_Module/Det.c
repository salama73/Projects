
/******************************************************************************
* @Module      :	Default Error Tracer
* @File Name   :	Det.c
* @Description :	This specification describes the API of the Default Error Tracer.
					All detected development and runtime errors in the Basic Software
					are reported to this module.
* Author       :	Salama Mohamed
*******************************************************************************/
/******************************************************************************
* Project				: Door_Lock_Indication
* Platform				: STM32F103C8
* Autosar Version		: 4.8.0
* SW Version		    : 1.0.0
******************************************************************************/
/*****************************************************************************
							Source File Version Informations
*****************************************************************************/
#define DET_VERSION_ID							17
#define DET_AR_RELEASE_MAJOR_VERSION			4
#define DET_AR_RELEASE_MINOR_VERSION			8
#define DET_AR_RELEASE_PATCH_VERSION		    0
#define DET_SW_RELEASE_MAJOR_VERSION			1
#define DET_SW_RELEASE_MINOR_VERSION			0
#define DET_SW_RELEASE_PATCH_VERSION		    0
/*****************************************************************************
							Includes
*****************************************************************************/
#include "../Common_Module/Std_Types.h"
 /*************************************************************************
                               APIS                                   
*************************************************************************/
/************************************************************************
* Service ID [hex]	:	0x01
* Service Name		:	Det_ReportError
* Sync/Async		:	Synchronous
* Reentrancy		:	reentrant
* Parameters (in)	:	ModuleId (Module ID of calling module)
						InstanceId (The identifier of the index based instance of a module)
						ApiId (ID of API service in which error is detected)
						ErrorId (ID of detected development error)
* Parameters (inout):	None
* Parameters (out)	:	None
* Return value		:	Std_ReturnType (never returns a value, but has a return type for compatibility with services and hooks)
* Description		:	Service to report development errors.
***********************************************************************/
Std_ReturnType Det_ReportError ( uint16 ModuleId , uint8 InstanceId , uint8 ApiId , uint8 ErrorId )
{
	while(1)
	{
		
	}
}
