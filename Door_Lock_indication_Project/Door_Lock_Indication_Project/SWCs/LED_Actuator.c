/*
 @File Name		: LED_Actuator.c
 @Created on	: 22/10/2023
 @   Author		: Salama Mohamed
*/
#include "Rte_LED_Actuator.h"

#define LED_OFF	(myuint8)0
#define LED_ON	(myuint8)1

/*****************************************************
 * Runnable: 	Read_LED_State
 * Period:		0.018
 *****************************************************/
void Read_LED_State_Runnable(void)
{
	myuint8 LED_State=0;
	LED_State=Rte_IRead_LED_Actuator_Read_LED_State_RP_SR_LED_State_LED_State();
	if(LED_State==LED_ON)
	{
		Rte_Call_LED_Actuator_RP_CS_LED_Switch_LED_Switch(LED_ON);
	}
	else if(LED_State==LED_OFF)
	{
		Rte_Call_LED_Actuator_RP_CS_LED_Switch_LED_Switch(LED_OFF);
	}
	else
	{
		//Error
	}
}
