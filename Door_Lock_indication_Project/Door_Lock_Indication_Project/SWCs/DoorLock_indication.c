/*
 @File Name		: DoorLock_indication.c
 @Created on	: 22/10/2023
 @   Author		: Salama Mohamed
 */

#include "Rte_DoorLock_indication.h"
#define LED_OFF		(myuint8)0
#define LED_ON		(myuint8)1
#define Door_Close	(myuint8)0
#define Door_Open	(myuint8)1
/*****************************************************
 * Runnable: 	DoorLock_indication
 * Period:		0.015
 *****************************************************/
void IB_DoorLock_indication_Runnable(void)
{
	myuint8 Door_State=0;
	Door_State=Rte_IRead_DoorLock_indication_DoorLock_indication_RP_SR_DOOR_State_Door_State();
	if(Door_State==Door_Open)
	{
		Rte_IWrite_DoorLock_indication_DoorLock_indication_PP_SR_LED_State_LED_State(LED_ON);
	}
	else if(Door_State==Door_Close)
	{
		Rte_IWrite_DoorLock_indication_DoorLock_indication_PP_SR_LED_State_LED_State(LED_OFF);
	}
	else
	{
		//Error
	}
}
