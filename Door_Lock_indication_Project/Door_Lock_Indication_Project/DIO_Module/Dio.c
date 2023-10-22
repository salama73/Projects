/******************************************************************************
* @Module      :	 DIO
* @File Name   :	 DIO.c
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
/*****************************************************************************
							Includes
*****************************************************************************/
#include "Dio.h"

#include "../Common_Module/stm32f103x6.h"
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
* Description		:	None
***********************************************************************/
Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId)
{
	uint16 Channel_Pos=0;
	boolean Channel_state;
	/*
	 [SWS_Dio_00027] The Dio_ReadChannel function shall return the value of the
	 specified DIO channel.
	 */
#if (TRUE==DioDevErrorDetect)
	/*
	 [SWS_Dio_00074] If development error detection is enabled, the services
	 Dio_ReadChannel shall check the “ChannelId” parameter to be valid within the current
	 configuration. If the “ChannelId” parameter is invalid, the functions shall report
	 the error code DIO_E_PARAM_INVALID_CHANNEL_ID to the DET.
	 */
	if (ChannelId<channel_0||ChannelId>MAX_Number_Channel)
	{
		Det_ReportError(DIO_VERSION_ID,DIO_INSTANCE_ZERO,Dio_ReadChannel_ID,DIO_E_PARAM_INVALID_CHANNEL_ID);
	}
	else
	{
		//
	}
#endif
	if(ChannelId<channel_16)
	{
		Channel_Pos=ChannelId;
		if((GPIOA->IDR&(1<<Channel_Pos))!=STD_LOW)
		{
			Channel_state=STD_HIGH;
		}
		else
		{
			Channel_state=STD_LOW;
		}
	}
	else if(ChannelId<channel_32)
	{
		Channel_Pos=ChannelId-16;
		if((GPIOB->IDR&(1<<Channel_Pos))!=STD_LOW)
		{
			Channel_state=STD_HIGH;
		}
		else
		{
			Channel_state=STD_LOW;
		}
	}
	else if(ChannelId<=channel_47)
	{
		Channel_Pos=ChannelId-32;
		if((GPIOC->IDR&(1<<Channel_Pos))!=STD_LOW)
		{
			Channel_state=STD_HIGH;
		}
		else
		{
			Channel_state=STD_LOW;
		}
	}
	else
	{
		//Error
	}
	return Channel_state;
}
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
void Dio_WriteChannel (Dio_ChannelType ChannelId,Dio_LevelType Level)
{
	uint16 Channel_Pos=0;
	/*
	 [SWS_Dio_00028] If the specified channel is configured as an output channel, the
	 Dio_WriteChannel function shall set the specified Level for the specified channel.
	 */
	/*
	 [SWS_Dio_00029] If the specified channel is configured as an input channel, the
	 Dio_WriteChannel function shall have no influence on the physical output.
	 */
	if(ChannelId<channel_8)
	{
		Channel_Pos=ChannelId-0;
		//output
		if((GPIOA->CRL&(3<<Channel_Pos*4))!=0)
		{
			if(Level==STD_HIGH)
			{
				GPIOA->ODR|=(1<<(ChannelId-0));
			}
			else if(Level==STD_LOW)
			{
				GPIOA->ODR&=~(1<<(ChannelId-0));
			}
			else
			{
				//Error
			}
		}
		//input
		{
			//not effect
		}
	}
	else if(ChannelId<channel_16)
	{
		Channel_Pos=ChannelId-8;
		//output
		if((GPIOA->CRH&(3<<Channel_Pos*4))!=0)
		{
			if(Level==STD_HIGH)
			{
				GPIOA->ODR|=(1<<(ChannelId-0));
			}
			else if(Level==STD_LOW)
			{
				GPIOA->ODR&=~(1<<(ChannelId-0));
			}
			else
			{
				//Error
			}
		}
		//input
		{
			//not effect
		}
	}
	else if(ChannelId<channel_24)
	{
		Channel_Pos=ChannelId-16;
		//output
		if((GPIOB->CRL&(3<<Channel_Pos*4))!=0)
		{
			if(Level==STD_HIGH)
			{
				GPIOB->ODR|=(1<<(ChannelId-16));
			}
			else if(Level==STD_LOW)
			{
				GPIOB->ODR&=~(1<<(ChannelId-16));
			}
			else
			{
				//Error
			}
		}
		//input
		{
			//not effect
		}
	}
	else if(ChannelId<channel_32)
	{
		Channel_Pos=ChannelId-24;
		//output
		if((GPIOB->CRH&(3<<Channel_Pos*4))!=0)
		{
			if(Level==STD_HIGH)
			{
				GPIOB->ODR|=(1<<(ChannelId-16));
			}
			else if(Level==STD_LOW)
			{
				GPIOB->ODR&=~(1<<(ChannelId-16));
			}
			else
			{
				//Error
			}
		}
		//input
		{
			//not effect
		}
	}
	else if(ChannelId<=channel_47)
	{
		Channel_Pos=ChannelId-40;
		//output
		if((GPIOC->CRH&(3<<ChannelId*4))!=0)
		{
			if(Level==STD_HIGH)
			{
				GPIOC->ODR|=(1<<(ChannelId-32));
			}
			else if(Level==STD_LOW)
			{
				GPIOC->ODR&=~(1<<(ChannelId-32));
			}
			else
			{
				//Error
			}
		}
		//input
		{
			//not effect
		}
	}
	else
	{
		//Error
	}
}
/************************************************************************
* Service ID [hex]	:	0x02
* Service Name		:	Dio_ReadPort
* Sync/Async		:	Synchronous
* Reentrancy		:	Reentrant
* Parameters (in)	:	PortId (ID of DIO Port).
* Parameters (in)	:	Level (Value to be written).
* Parameters (inout):	None
* Parameters (out)	:	None
* Return value		:	Dio_PortLevelType (Level of all channels of that port)
* Description		:	Returns the level of all channels of that port.
***********************************************************************/
Dio_PortLevelType Dio_ReadPort (Dio_PortType PortId)
{
	Dio_PortLevelType Port_State=0;
	/*
	 [SWS_Dio_00031] The Dio_ReadPort function shall return the level of all
	 channels of that port.
	 */
#if (TRUE==DioDevErrorDetect)
	/*
	 [SWS_Dio_00074] If development error detection is enabled, the services
	 Dio_ReadPort shall check the “ChannelId” parameter to be valid within the current
	 configuration. If the “ChannelId” parameter is invalid, the functions shall report
	 the error code DIO_E_PARAM_INVALID_CHANNEL_ID to the DET.
	 */
	if (PortId<DioPort_A||PortId>DioPort_C)
	{
		Det_ReportError(DIO_VERSION_ID,DIO_INSTANCE_ZERO,Dio_ReadPort_ID,DIO_E_PARAM_INVALID_PORT_ID);
	}
	else
	{
		//
	}
#endif
	switch (PortId)
	{
		case DioPort_A:
			Port_State=(uint16)(GPIOA->IDR);
			break;
		case DioPort_B:
			Port_State=(uint16)(GPIOB->IDR);
			break;
		case DioPort_C:
			Port_State=(uint16)(GPIOC->IDR);
			break;
		default:
			//Error
			break;
	}
	return Port_State;
}
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
void Dio_WritePort (Dio_PortType PortId,Dio_PortLevelType Level)
{
	/*
	 [SWS_Dio_00034] The Dio_WritePort function shall set the specified value for
	 the specified port.
	 */
	/*
	 [SWS_Dio_00034] The Dio_WritePort function shall set the specified value for
	 the specified port.
	 */
	switch (PortId)
	{
		case DioPort_A:
			for(int index=0;index<16;index++)
			{
				if(index<8)
				{
					//output
					if((GPIOA->CRL&(3<<index*4))!=0)
					{
						if((Level&(1<<index))>>index)
						{
							GPIOA->ODR|=(1<<index);
						}
						else
						{
							GPIOA->ODR&=~(1<<index);
						}
					}
					//input
					else
					{
						//not effect
					}
				}
				else
				{
					//output
					if((GPIOA->CRH&(3<<(index-8)*4))!=0)
					{
						if((Level&(1<<index))>>index)
						{
							GPIOA->ODR|=(1<<index);
						}
						else
						{
							GPIOA->ODR&=~(1<<index);
						}
					}
					//input
					else
					{

					}
				}
			}
			break;
		case DioPort_B:
			for(int index=0;index<16;index++)
			{
				if(index<8)
				{
					//output
					if((GPIOB->CRL&(3<<index*4))!=0)
					{
						if((Level&(1<<index))>>index)
						{
							GPIOB->ODR|=(1<<index);
						}
						else
						{
							GPIOB->ODR&=~(1<<index);
						}
					}
					//input
					else
					{
						//not effect
					}
				}
				else
				{
					//output
					if((GPIOB->CRH&(3<<(index-8)*4))!=0)
					{
						if((Level&(1<<index))>>index)
						{
							GPIOB->ODR|=(1<<index);
						}
						else
						{
							GPIOB->ODR&=~(1<<index);
						}
					}
					//input
					else
					{

					}
				}
			}
			break;
		case DioPort_C:
			for(int index=0;index<16;index++)
			{
				if(index<8)
				{
					//output
					if((GPIOC->CRL&(3<<index*4))!=0)
					{
						if((Level&(1<<index))>>index)
						{
							GPIOC->ODR|=(1<<index);
						}
						else
						{
							GPIOC->ODR&=~(1<<index);
						}
					}
					//input
					else
					{
						//not effect
					}
				}
				else
				{
					//output
					if((GPIOC->CRH&(3<<(index-8)*4))!=0)
					{
						if((Level&(1<<index))>>index)
						{
							GPIOC->ODR|=(1<<index);
						}
						else
						{
							GPIOC->ODR&=~(1<<index);
						}
					}
					//input
					else
					{

					}
				}
			}
			break;
		default:
			//Error
			break;
	}
}
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
#if(DioVersionInfoApi==TRUE)
void Dio_GetVersionInfo (Std_VersionInfoType* VersionInfo)
{
#if (TRUE==DioDevErrorDetect)
	/*
	 [SWS_Port_00225] if Det is enabled, the parameter versioninfo shall be
	 checked for being NULL. The error DIO_E_PARAM_POINTER shall be reported in
	 case the value is a NULL pointer.
	 */
	if (NULL_PTR==VersionInfo)
	{
		Det_ReportError(DIO_VERSION_ID,DIO_INSTANCE_ZERO,Dio_GetVersionInfo_ID,DIO_E_PARAM_POINTER);
	}
	else
	{
		//
	}
#endif
	VersionInfo->moduleID = DIO_VERSION_ID ;
	VersionInfo->sw_major_version = DIO_SW_RELEASE_MAJOR_VERSION ;
	VersionInfo->sw_minor_version = DIO_SW_RELEASE_MINOR_VERSION ;
	VersionInfo->sw_patch_version = DIO_SW_RELEASE_PATCH_VERSION ;
	VersionInfo->vendorID = VENDOR_ID ;
}
#endif
