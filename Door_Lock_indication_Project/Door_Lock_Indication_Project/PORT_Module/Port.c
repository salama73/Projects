
/******************************************************************************
* @Module      :	 Port
* @File Name   :	 Port.c
* @Description :	This specification specifies the functionality, API and the configuration of the AUTOSAR
					Basic Software module PORT Driver.
* Author       :	Salama Mohamed
*******************************************************************************/
/******************************************************************************
* Project				: Door_Lock_Indication
* Platform				: Atmega32
* Autosar Version		: 4.8.0
* SW Version		    : 1.0.0
******************************************************************************/
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
#include "Port.h"
#include "../Common_Module/stm32f103x6.h"
/*************************************************************************
                               Global Variables
*************************************************************************/
 uint8 Port_Status = PORT_NOT_INITIALIZED;
 const Port_ConfigType* Port_Config = NULL_PTR;
 uint8 Flag_Mode_Change[PortNumberOfPortPins]={0};
 uint8 Flag_DIR_Change[PortNumberOfPortPins]={0};
/*************************************************************************
                               Local Functions
*************************************************************************/
 uint8 get_position(uint8 pinNumber)
 {
	 uint8 Pos=0;
	 if(pinNumber<PORT_B_PIN_0)
	 {
		 if(pinNumber<PORT_A_PIN_8)
			 Pos=((pinNumber-1)*4);
		 else
			 Pos=((pinNumber-1)*4)-32;
	 }
	 else if(pinNumber<PORT_C_PIN_13)
	 {
		 if(pinNumber<PORT_B_PIN_8)
			 Pos=((pinNumber-17)*4);
		 else
			 Pos=((pinNumber-17)*4)-32;
	 }
	 else
	 {
		 Pos=((pinNumber-33)*4)-32;
	 }
	 return Pos;
 }
 uint8 get_Index(uint8 pinNumber)
 {
	 for(int index=0;index<PortNumberOfPortPins;index++)
	 {
		 if(Port_Config->PortPin[index].PortPinId==pinNumber)
			 return index;
	 }
	 //error
	 return PortNumberOfPortPins;
 }
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
void Port_Init( const Port_ConfigType* ConfigPtr )
{
	GPIO_TypeDef* GPIO_Current=NULL_PTR;
	 uint8 pos=0;
	uint32 pin_config=0;
	volatile uint32 *configregister =NULL_PTR;
	//uint32 pin_config=0;
	Port_Config = ConfigPtr ;
	#if (TRUE==PortDevErrorDetect)
		// Check APIs called with a Null Pointer
		if (NULL_PTR==ConfigPtr)
		{
			Det_ReportError(PORT_VERSION_ID,PORT_INSTANCE_ZERO,PORT_INIT_ID,PORT_E_PARAM_POINTER);
		}
		else
		{
			//
		}
	#endif
	for(int Pin_Index=0;Pin_Index<PortNumberOfPortPins;Pin_Index++)
	{
		pin_config=0;
		//determine GPIO current port
		if(ConfigPtr->PortPin[Pin_Index].PortPinId<PORT_B_PIN_0)
		{
			GPIO_Current=GPIOA;
			// GPIO->CRL configure pins 0-->>7
			// GPIO->CRH configure pins 8-->>15
			if(ConfigPtr->PortPin[Pin_Index].PortPinId<PORT_A_PIN_8)
			{
				configregister=&GPIO_Current->CRL;
				pos=get_position(ConfigPtr->PortPin[Pin_Index].PortPinId)/4;
			}
			else
			{
				configregister=&GPIO_Current->CRH;
				pos=(get_position(ConfigPtr->PortPin[Pin_Index].PortPinId)/4)+8;
			}
		}
		else if(ConfigPtr->PortPin[Pin_Index].PortPinId<PORT_C_PIN_13)
		{
			GPIO_Current=GPIOB;
			// GPIO->CRL configure pins 0-->>7
			// GPIO->CRH configure pins 8-->>15
			if(ConfigPtr->PortPin[Pin_Index].PortPinId<PORT_B_PIN_8)
			{
				configregister=&GPIO_Current->CRL;
				pos=get_position(ConfigPtr->PortPin[Pin_Index].PortPinId)/4;
			}
			else
			{
				configregister=&GPIO_Current->CRH;
				pos=(get_position(ConfigPtr->PortPin[Pin_Index].PortPinId)/4)+8;
			}
		}
		else
		{
			GPIO_Current=GPIOC;
			// GPIO->CRL configure pins 0-->>7
			// GPIO->CRH configure pins 8-->>15
			configregister =&GPIO_Current->CRH;
			pos=(get_position(ConfigPtr->PortPin[Pin_Index].PortPinId)/4)+8;
		}
		//clear MODEy[1:0] and CNFy[1:0]
		(*configregister) &=~(0XF<<get_position(ConfigPtr->PortPin[Pin_Index].PortPinId));
		//pin mode
		if(ConfigPtr->PortPin[Pin_Index].PortPinDirection==PORT_PIN_OUT)
		{
			//Slew_Rate
			if(ConfigPtr->PortPin[Pin_Index].Slew_Rate==GPIO_Slew_Rate_10M)
			{
				//01: Output mode, max speed 10 MHz
				pin_config|=(0b01<<get_position(ConfigPtr->PortPin[Pin_Index].PortPinId));

			}
			else if(ConfigPtr->PortPin[Pin_Index].Slew_Rate==GPIO_Slew_Rate_50M)
			{
				//11: Output mode, max speed 50 MHz
				pin_config|=(0b11<<get_position(ConfigPtr->PortPin[Pin_Index].PortPinId));
			}
			else
			{
				//10: Output mode, max speed 2 MHz
				pin_config|=(0b10<<get_position(ConfigPtr->PortPin[Pin_Index].PortPinId));
			}
			//Pin driven mode
			if(ConfigPtr->PortPin[Pin_Index].PortPinMode==PORT_PIN_MODE_CAN)
			{
				//10: Alternate function output Push-pull
				pin_config|=(0b10<<(get_position(ConfigPtr->PortPin[Pin_Index].PortPinId)+2));
			}
			else if(ConfigPtr->PortPin[Pin_Index].PortPinMode==PORT_PIN_MODE_ADC)
			{
				//
			}
			else
			{
				if(ConfigPtr->PortPin[Pin_Index].Pin_Driven_Mode==GPIO_Pin_Driven_Mode_PP)
				{
					//00: General purpose output push-pull
					pin_config&=~(0b11<<(get_position(ConfigPtr->PortPin[Pin_Index].PortPinId)+2));
				}
				else
				{
					//01: General purpose output Open-drain
					pin_config|=(0b01<<(get_position(ConfigPtr->PortPin[Pin_Index].PortPinId)+2));
				}
			}
			// Port Pin Level value from Port pin list.
			if(ConfigPtr->PortPin[Pin_Index].PortPinLevelValue==STD_HIGH)
			{
				GPIO_Current->ODR|=1<<pos;
			}
			else
			{
				//
			}
		}
		else if(ConfigPtr->PortPin[Pin_Index].PortPinDirection==PORT_PIN_IN)
		{
			//Pin driven mode
			if(ConfigPtr->PortPin[Pin_Index].PortPinMode==PORT_PIN_MODE_CAN)
			{
				//10: Input with pull-up / pull-down
				pin_config|=(0b10<<(get_position(ConfigPtr->PortPin[Pin_Index].PortPinId)+2));
				//  port bit configuration table px_ODR =1
				GPIO_Current->ODR|=1<<pos;
			}
			else if(ConfigPtr->PortPin[Pin_Index].PortPinMode==PORT_PIN_MODE_ADC)
			{
				//00: Analog mode
				pin_config&=~(0b11<<(get_position(ConfigPtr->PortPin[Pin_Index].PortPinId)+2));
			}
			else
			{
				if(ConfigPtr->PortPin[Pin_Index].Pull_UP==TRUE)
				{
					//10: Input with pull-up / pull-down
					pin_config|=(0b10<<(get_position(ConfigPtr->PortPin[Pin_Index].PortPinId)+2));
					//  port bit configuration table px_ODR =1
					if(ConfigPtr->PortPin[Pin_Index].PortPinLevelValue==STD_HIGH)
					{
						GPIO_Current->ODR|=1<<pos;
					}
					else
					{
						//
					}
				}
				else
				{
					//01: Floating input (reset state)
				}
			}
		}
		else
		{
			//
		}
		*configregister|=pin_config;
	}
	/*
	 [SWS_Port_00002] The function Port_Init shall initialize all variables used by the
	 PORT driver module to an initial state.
	 */
	Port_Status=PORT_INITIALIZED;
}
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
/*
 [SWS_Port_00086] The function Port_SetPinDirection shall only be available
 to the user if the pre-compile parameter PortSetPinDirectionApi is set to TRUE.
 If set to FALSE, the function Port_SetPinDirection is not available.
 */
#if (TRUE==PortSetPinDirectionApi)
void Port_SetPinDirection ( Port_PinType Pin , Port_PinDirectionType Direction )
{
	GPIO_TypeDef* GPIO_Current=NULL_PTR;
	 uint8 Index=0;
	 Index=get_Index(Pin);
	volatile uint32 *configregister =NULL_PTR;
#if (TRUE==PortDevErrorDetect)
	// API Port_SetPinMode service called when modeis unchangeable
	if (Port_Status == PORT_NOT_INITIALIZED)
	{
		Det_ReportError(PORT_VERSION_ID,PORT_INSTANCE_ZERO,PORT_SET_PIN_DIR_ID,PORT_E_UNINIT);
	}
	else
	{
		//
	}
	// Check Invalid Port Pin ID requested
	if (Pin < PORT_A_PIN_0 || Pin > PORT_C_PIN_15 )
	{
		Det_ReportError(PORT_VERSION_ID,PORT_INSTANCE_ZERO,PORT_SET_PIN_DIR_ID,PORT_E_PARAM_PIN);
	}
	else
	{
		//
	}
	// check if Port Pin not configured as changeable
	if (FALSE == Port_Config->PortPin[Index].PortPinDirectionChangeable)
	{
		Det_ReportError(PORT_VERSION_ID , PORT_INSTANCE_ZERO , PORT_SET_PIN_DIR_ID , PORT_E_DIRECTION_UNCHANGEABLE );
	}
#endif
	//determine GPIO current port
	if(Port_Config->PortPin[Index].PortPinId<PORT_B_PIN_0)
	{
		GPIO_Current=GPIOA;
		// GPIO->CRL configure pins 0-->>7
		// GPIO->CRH configure pins 8-->>15
		if(Port_Config->PortPin[Index].PortPinId<PORT_A_PIN_8)
		{
			configregister=&GPIO_Current->CRL;
		}
		else
		{
			configregister=&GPIO_Current->CRH;
		}
	}
	else if(Port_Config->PortPin[Index].PortPinId<PORT_C_PIN_13)
	{
		GPIO_Current=GPIOB;
		// GPIO->CRL configure pins 0-->>7
		// GPIO->CRH configure pins 8-->>15
		if(Port_Config->PortPin[Index].PortPinId<PORT_B_PIN_8)
		{
			configregister=&GPIO_Current->CRL;
		}
		else
		{
			configregister=&GPIO_Current->CRH;
		}
	}
	else
	{
		GPIO_Current=GPIOC;
		// GPIO->CRL configure pins 0-->>7
		// GPIO->CRH configure pins 8-->>15
		configregister =&GPIO_Current->CRH;
	}
	//clear MODEy[1:0] and CNFy[1:0]
	(*configregister) &=~(0XF<<get_position(Port_Config->PortPin[Index].PortPinId));
	if(Direction==PORT_PIN_OUT)
	{
		//01: Output mode, max speed 10 MHz.
		*configregister|=(0b01<<get_position(Port_Config->PortPin[Index].PortPinId));
		//Indication to Direction Pin Change
		Flag_DIR_Change[Index]=1;
	}
	else if(Direction==PORT_PIN_IN)
	{
		//01: Floating input (reset state)
		*configregister|=(0b01<<(get_position(Port_Config->PortPin[Index].PortPinId)+2));
		//Indication to Direction Pin Change
		Flag_DIR_Change[Index]=1;
	}
	else
	{
		//
	}
	/*
	 [SWS_Port_00063] dThe function Port_SetPinDirection shall set the port pin direction during runtime.
	 */
}
#endif
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
void Port_RefreshPortDirection (void)
{

}
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
#if (TRUE==PortVersionInfoApi)
void Port_GetVersionInfo ( Std_VersionInfoType* versioninfo )
{
#if (TRUE==PortDevErrorDetect)
	/*
	 [SWS_Port_00225] if Det is enabled, the parameter versioninfo shall be
	 checked for being NULL. The error PORT_E_PARAM_POINTER shall be reported in
	 case the value is a NULL pointer.
	 */
	if (NULL_PTR==versioninfo)
	{
		Det_ReportError(PORT_VERSION_ID,PORT_INSTANCE_ZERO,PORT_GET_VERSION_INFO_ID,PORT_E_PARAM_POINTER);
	}
	else
	{
		//
	}
#endif
	versioninfo->moduleID = PORT_VERSION_ID ;
	versioninfo->sw_major_version = PORT_SW_RELEASE_MAJOR_VERSION ;
	versioninfo->sw_minor_version = PORT_SW_RELEASE_MINOR_VERSION ;
	versioninfo->sw_patch_version = PORT_SW_RELEASE_PATCH_VERSION ;
	versioninfo->vendorID = VENDOR_ID ;
}
#endif
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
#if (TRUE==PortSetPinModeApi)
void Port_SetPinMode ( Port_PinType Pin , Port_PinModeType Mode )
{
	GPIO_TypeDef* GPIO_Current=NULL_PTR;
	uint8 Index=0;
	uint8 pos=0;
	Index=get_Index(Pin);
	volatile uint32 *configregister =NULL_PTR;
#if (TRUE==PortDevErrorDetect)
	// Check API service called without module initialization
	if (Port_Status == PORT_NOT_INITIALIZED)
	{
		Det_ReportError(PORT_VERSION_ID,PORT_INSTANCE_ZERO,PORT_SET_PIN_MODE_ID,PORT_E_UNINIT);
	}
	else
	{
		//
	}
	// Check Invalid Port Pin ID requested
	if (Pin < PORT_A_PIN_0 || Pin > PORT_C_PIN_15)
	{
		Det_ReportError(PORT_VERSION_ID,PORT_INSTANCE_ZERO,PORT_SET_PIN_MODE_ID,PORT_E_PARAM_PIN);
	}
	else
	{
		//
	}
	// check if Port Pin not configured as changeable
	if (FALSE == Port_Config->PortPin[Index].PortPinModeChangeable)
	{
		Det_ReportError(PORT_VERSION_ID , PORT_INSTANCE_ZERO , PORT_SET_PIN_MODE_ID , PORT_E_MODE_UNCHANGEABLE );
	}
	else
	{
		//
	}
	// check if Incorrect Port Pin Mode passed
	if (Mode > PORT_PIN_MODE_PWM || Mode < PORT_PIN_MODE_ADC )
	{
		Det_ReportError(PORT_VERSION_ID , PORT_INSTANCE_ZERO , PORT_SET_PIN_MODE_ID , PORT_E_PARAM_INVALID_MODE );
	}
	else
	{
		//
	}
#endif
	//determine GPIO current port
	if(Port_Config->PortPin[Index].PortPinId<PORT_B_PIN_0)
	{
		GPIO_Current=GPIOA;
		// GPIO->CRL configure pins 0-->>7
		// GPIO->CRH configure pins 8-->>15
		if(Port_Config->PortPin[Index].PortPinId<PORT_A_PIN_8)
		{
			configregister=&GPIO_Current->CRL;
			pos=get_position(Port_Config->PortPin[Index].PortPinId)/4;
		}
		else
		{
			configregister=&GPIO_Current->CRH;
			pos=(get_position(Port_Config->PortPin[Index].PortPinId)/4)+8;
		}
	}
	else if(Port_Config->PortPin[Index].PortPinId<PORT_C_PIN_13)
	{
		GPIO_Current=GPIOB;
		// GPIO->CRL configure pins 0-->>7
		// GPIO->CRH configure pins 8-->>15
		if(Port_Config->PortPin[Index].PortPinId<PORT_B_PIN_8)
		{
			configregister=&GPIO_Current->CRL;
			pos=get_position(Port_Config->PortPin[Index].PortPinId)/4;
		}
		else
		{
			configregister=&GPIO_Current->CRH;
			pos=(get_position(Port_Config->PortPin[Index].PortPinId)/4)+8;
		}
	}
	else
	{
		GPIO_Current=GPIOC;
		// GPIO->CRL configure pins 0-->>7
		// GPIO->CRH configure pins 8-->>15
		configregister =&GPIO_Current->CRH;
		pos=(get_position(Port_Config->PortPin[Index].PortPinId)/4)+8;
	}
	if(Port_Config->PortPin[Index].PortPinModeChangeable==TRUE)
	{
		//clear CNFy[1:0]
		(*configregister) &=~(0XC<<get_position(Port_Config->PortPin[Index].PortPinId));
		if(Mode==PORT_PIN_MODE_CAN)
		{
			//Init dir change
			if(Flag_DIR_Change[Index]==1)
			{
				if(Port_Config->PortPin[Index].PortPinDirection==PORT_PIN_OUT)
				{
					//10: Input with pull-up / pull-down
					*configregister|=(0b10<<(get_position(Port_Config->PortPin[Index].PortPinId)+2));
					//  port bit configuration table px_ODR =1
					GPIO_Current->ODR|=1<<pos;
					Flag_Mode_Change[Index]=1;
				}
				else if(Port_Config->PortPin[Index].PortPinDirection==PORT_PIN_IN)
				{
					//10: Alternate function output Push-pull
					*configregister|=(0b10<<(get_position(Port_Config->PortPin[Index].PortPinId)+2));
					//Indication to Direction Pin Change
					Flag_Mode_Change[Index]=1;
				}
				else
				{
					//
				}
			}
			//Init dir not change
			else
			{
				if(Port_Config->PortPin[Index].PortPinDirection==PORT_PIN_OUT)
				{
					//10: Alternate function output Push-pull
					*configregister|=(0b10<<(get_position(Port_Config->PortPin[Index].PortPinId)+2));
					//Indication to Direction Pin Change
					Flag_Mode_Change[Index]=1;
				}
				else if(Port_Config->PortPin[Index].PortPinDirection==PORT_PIN_IN)
				{
					//10: Input with pull-up / pull-down
					*configregister|=(0b10<<(get_position(Port_Config->PortPin[Index].PortPinId)+2));
					//  port bit configuration table px_ODR =1
					GPIO_Current->ODR|=1<<pos;
					Flag_Mode_Change[Index]=1;
				}
				else
				{
					//
				}
			}
		}
	}
	else
	{
		//
	}
}
#endif
