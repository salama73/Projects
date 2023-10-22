/*
 @File Name		: ECU_Abstraction_SWC.c
 @Created on	: 22/10/2023
 @   Author		: Salama Mohamed
*/
#include "Rte_ECU_Abstraction_SWC.h"
#include "Dio.h"

#define LED_OFF	(myuint8)0
#define LED_ON	(myuint8)1
/*****************************************************
 * Port: 		PP_CS_LED_Switch
 * Interface:	CS_Interface
 * Operation:	LED_Switch
 *****************************************************/
Std_ReturnType Switch_LED_State_Runnable(myuint8 LED_State)
{
	if(LED_State==LED_ON)
	{
		Dio_WriteChannel(channel_1,STD_HIGH);
		return E_OK;
	}
	else if(LED_State==LED_OFF)
	{
		Dio_WriteChannel(channel_1,STD_LOW);
		return E_OK;
	}
	else
	{
		return E_NOT_OK;
	}
}
/*****************************************************
 * Runnable: 	Read_Door_Sensor
 * Period:		0.01
 *****************************************************/
void Read_Door_Sensor_Runnable(void)
{
	myuint8 Sensor_State=0;
	Sensor_State=Dio_ReadChannel(channel_0);
	Rte_IWrite_ECU_Abstraction_SWC_Read_Door_Sensor_PP_SR_DOOR_State_Sensor_Reading(Sensor_State);
}
