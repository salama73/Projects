/******************************************************************************
* @Module      :	Default Error Tracer 
* @File Name   :	Det.h
* @Description :	This specification describes the API of the Default Error Tracer. 
					All detected development and runtime errors in the Basic Software 
					are reported to this module.
* Author       :	Salama Mohamed
*******************************************************************************/
/******************************************************************************
* Project				: Can Stack
* Platform				: STM32F103C8
* Autosar Version		: 4.8.0
* SW Version		    : 1.0.0
******************************************************************************/
#ifndef DET_H_
#define DET_H_

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
// AUTOSAR checking Std_Version 
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != DET_AR_RELEASE_MAJOR_VERSION)\
||  (STD_TYPES_AR_RELEASE_MINOR_VERSION  != DET_AR_RELEASE_MINOR_VERSION)\
||  (STD_TYPES_AR_RELEASE_PATCH_VERSION  != DET_AR_RELEASE_PATCH_VERSION))
#error "The Autosar version of Std_Types.h does not match the DET version"
#endif
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
Std_ReturnType Det_ReportError ( uint16 ModuleId , uint8 InstanceId , uint8 ApiId , uint8 ErrorId ) ;

#endif /* DET_H_ */
