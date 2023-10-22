/******************************************************************************
* @Module      :	 DIO
* @File Name   :	 DIO.h
* @Description :	 This specification specifies the functionality, API and the configuration of the AUTOSAR
					 Basic Software module DIO Driver.
* Author       :	 Salama Mohamed
*******************************************************************************/
/******************************************************************************
* Project				: Door_Lock_Indication
* Platform				: STM32F103C8
* Autosar Version		: 4.8.0
* SW Version		    : 1.0.0
******************************************************************************/
#ifndef DIO_H_
#define DIO_H_

/*****************************************************************************
							Source File Version Informations
*****************************************************************************/
#define DIO_VERSION_ID							20
#define DIO_AR_RELEASE_MAJOR_VERSION			4
#define DIO_AR_RELEASE_MINOR_VERSION			8
#define DIO_AR_RELEASE_PATCH_VERSION		    0
#define DIO_SW_RELEASE_MAJOR_VERSION			1
#define DIO_SW_RELEASE_MINOR_VERSION			0
#define DIO_SW_RELEASE_PATCH_VERSION		    0
#define VENDOR_ID								100
/*****************************************************************************
							Includes
*****************************************************************************/
#include "Dio_Cfg.h"
#include "../Common_Module/Det.h"
#include "../Common_Module/Std_Types.h"
// AUTOSAR checking Std_Version
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
||  (STD_TYPES_AR_RELEASE_MINOR_VERSION  != DIO_AR_RELEASE_MINOR_VERSION)\
||  (STD_TYPES_AR_RELEASE_PATCH_VERSION  != DIO_AR_RELEASE_PATCH_VERSION))
#error "The Autosar version of Std_Types.h does not match the DIO version"
#endif
/******************************************************************************
                      API Service Id Macros
******************************************************************************/
//Service ID for Dio_ReadChannel
#define Dio_ReadChannel_ID						(uint8)0x00
//Service ID for Dio_WriteChannel
#define Dio_WriteChannel_ID						(uint8)0x01
//Service ID for Dio_ReadPort
#define Dio_ReadPort_ID							(uint8)0x02
//Service ID for Dio_WritePort
#define Dio_WritePort_ID						(uint8)0x03
//Service ID for Dio_ReadChannelGroup
#define Dio_ReadChannelGroup_ID					(uint8)0x04
//Service ID for Dio_WriteChannelGroup
#define Dio_WriteChannelGroup_ID				(uint8)0x05
//Service ID for Dio_FlipChannel
#define Dio_FlipChannel_ID						(uint8)0x11
//Service ID for Dio_GetVersionInfo
#define Dio_GetVersionInfo_ID					(uint8)0x12
//Service ID for Dio_MaskedWritePort
#define Dio_MaskedWritePort_ID					(uint8)0x13
/*******************************************************************************
                      DET Error Codes
*******************************************************************************/
//Invalid channel requested
#define DIO_E_PARAM_INVALID_CHANNEL_ID 					(uint8)0x0A
//Invalid port requested
#define DIO_E_PARAM_INVALID_PORT_ID 					(uint8)0x14
//Invalid channel group requested
#define DIO_E_PARAM_INVALID_GROUP 						(uint8)0x1F
//API service called with a NULL pointer
#define DIO_E_PARAM_POINTER 							(uint8)0x20
/*****************************************************************************
							 Type definitions
*****************************************************************************/
// Numeric ID of a DIO channel.
typedef uint16 Dio_ChannelType;
//Numeric ID of a DIO port.
typedef uint8 Dio_PortType;
/*
 Type for the definition of a channel group, which consists of several adjoining
 channels within a port.
 */
typedef struct
{
	// This element mask which defines the positions of the channel group.
	uint8 mask;
	// This element shall be the position of the Channel Group on the port, counted from the LSB.
	uint8 offset;
	// This shall be the port on which the Channel group is defined.
	Dio_PortType port;
}Dio_ChannelGroupType;
//These are the possible levels a DIO channel can have (input or output).Range(STD_LOW or STD_HIGH)
typedef uint8 Dio_LevelType;
/*
 If the µC owns ports of different port widths (e.g. 4, 8,16...Bit) Dio_Port
 LevelType inherits the size of the largest port
 */
typedef uint16 Dio_PortLevelType;
/*************************************************************************
                               APIS
*************************************************************************/
/************************************************************************
* Service ID [hex]	:	0x00
* Service Name		:	Dio_ReadChannel
* Sync/Async		:	Synchronous
* Reentrancy		:	Reentrant
* Parameters (in)	:	ChannelId (ID of DIO channel).
* Parameters (inout):	None
* Parameters (out)	:	None
* Return value		:	Dio_LevelType
 						STD_HIGH ( The physical level of the corresponding Pin is STD_HIGH)
 						STD_LOW (The physical level of the corresponding Pin is STD_LOW)
* Description		:	Returns the value of the specified DIO channel.
***********************************************************************/
Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId);
/************************************************************************
* Service ID [hex]	:	0x01
* Service Name		:	Dio_WriteChannel
* Sync/Async		:	Synchronous
* Reentrancy		:	Reentrant
* Parameters (in)	:	ChannelId (ID of DIO channel).
* Parameters (in)	:	Level (Value to be written).
* Parameters (inout):	None
* Parameters (out)	:	None
* Return value		:	None
* Description		:	Service to set a level of a channel.
***********************************************************************/
void Dio_WriteChannel (Dio_ChannelType ChannelId,Dio_LevelType Level);
/************************************************************************
* Service ID [hex]	:	0x02
* Service Name		:	Dio_ReadPort
* Sync/Async		:	Synchronous
* Reentrancy		:	Reentrant
* Parameters (in)	:	PortId (ID of DIO Port).
* Parameters (inout):	None
* Parameters (out)	:	None
* Return value		:	Dio_PortLevelType (Level of all channels of that port)
* Description		:	Returns the level of all channels of that port.
***********************************************************************/
Dio_PortLevelType Dio_ReadPort (Dio_PortType PortId);
/************************************************************************
* Service ID [hex]	:	0x03
* Service Name		:	Dio_WritePort
* Sync/Async		:	Synchronous
* Reentrancy		:	Reentrant
* Parameters (in)	:	PortId (ID of DIO Port).
* Parameters (in)	:	Level (Value to be written).
* Parameters (inout):	None
* Parameters (out)	:	None
* Return value		:	None
* Description		:	Service to set a value of the port.
***********************************************************************/
void Dio_WritePort (Dio_PortType PortId,Dio_PortLevelType Level);
/************************************************************************
* Service ID [hex]	:	0x12
* Service Name		:	Dio_GetVersionInfo
* Sync/Async		:	Synchronous
* Reentrancy		:	Reentrant
* Parameters (in)	:	None
* Parameters (inout):	None
* Parameters (out)	:	VersionInfo
						 Pointer to where to store the version information of this module.
* Return value		:	None
* Description		:	Service to get the version information of this module.
***********************************************************************/
void Dio_GetVersionInfo (Std_VersionInfoType* VersionInfo);
#endif /* DIO_H_ */
