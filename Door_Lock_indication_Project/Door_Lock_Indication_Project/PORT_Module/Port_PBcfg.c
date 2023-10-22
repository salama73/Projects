/******************************************************************************
* @Module      :	 Port
* @File Name   :	 Port.c
* @Description :	the Post-build configuration of the AUTOSAR Basic Software module PORT Driver.
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
#define PORT_VERSION_ID							    40
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION			4
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION			8
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION		    0
#define PORT_PBCFG_SW_RELEASE_MAJOR_VERSION			1
#define PORT_PBCFG_SW_RELEASE_MINOR_VERSION			0
#define PORT_PBCFG_SW_RELEASE_PATCH_VERSION		    0
#define VENDOR_ID								    100
/*****************************************************************************
							Includes
*****************************************************************************/
 #include "Port.h"
/***************************************************************************/
const Port_ConfigType Port =
{
	{
		{PORT_PIN_IN,TRUE,PORT_A_PIN_0,PORT_PIN_MODE_DIO,STD_LOW,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_A_PIN_1,PORT_PIN_MODE_DIO,STD_LOW,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_A_PIN_2,PORT_PIN_MODE_DIO,STD_LOW,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_A_PIN_3,PORT_PIN_MODE_DIO,STD_HIGH,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_A_PIN_4,PORT_PIN_MODE_DIO,STD_LOW,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_A_PIN_5,PORT_PIN_MODE_DIO,STD_HIGH,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_A_PIN_6,PORT_PIN_MODE_DIO,STD_LOW,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_A_PIN_7,PORT_PIN_MODE_DIO,STD_HIGH,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_A_PIN_8,PORT_PIN_MODE_DIO,STD_LOW,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_A_PIN_9,PORT_PIN_MODE_DIO,STD_HIGH,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_A_PIN_10,PORT_PIN_MODE_DIO,STD_LOW,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_A_PIN_11,PORT_PIN_MODE_DIO,STD_LOW,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_A_PIN_12,PORT_PIN_MODE_DIO,STD_LOW,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_A_PIN_15,PORT_PIN_MODE_DIO,STD_HIGH,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_B_PIN_0,PORT_PIN_MODE_DIO,STD_LOW,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_B_PIN_1,PORT_PIN_MODE_DIO,STD_HIGH,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_B_PIN_3,PORT_PIN_MODE_DIO,STD_LOW,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_B_PIN_4,PORT_PIN_MODE_DIO,STD_HIGH,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_B_PIN_5,PORT_PIN_MODE_DIO,STD_LOW,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_B_PIN_6,PORT_PIN_MODE_DIO,STD_HIGH,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_B_PIN_7,PORT_PIN_MODE_DIO,STD_LOW,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_B_PIN_8,PORT_PIN_MODE_DIO,STD_HIGH,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_B_PIN_9,PORT_PIN_MODE_DIO,STD_LOW,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_B_PIN_10,PORT_PIN_MODE_DIO,STD_HIGH,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_B_PIN_11,PORT_PIN_MODE_DIO,STD_LOW,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_B_PIN_12,PORT_PIN_MODE_DIO,STD_HIGH,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_B_PIN_13,PORT_PIN_MODE_DIO,STD_LOW,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_B_PIN_14,PORT_PIN_MODE_DIO,STD_HIGH,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_B_PIN_15,PORT_PIN_MODE_DIO,STD_LOW,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_C_PIN_13,PORT_PIN_MODE_DIO,STD_LOW,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_C_PIN_14,PORT_PIN_MODE_DIO,STD_HIGH,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP},
		{PORT_PIN_OUT,TRUE,PORT_C_PIN_15,PORT_PIN_MODE_DIO,STD_LOW,PORT_PIN_MODE_DIO,TRUE,TRUE,GPIO_Slew_Rate_10M,GPIO_Pin_Driven_Mode_PP}
	}
};
