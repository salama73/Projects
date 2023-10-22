/*
 @File Name		: Read_Door_State.c
 @Created on	: 22/10/2023
 @   Author		: Salama Mohamed
*/
#include "Rte_Read_Door_State.h"

/*****************************************************
 * Runnable: 	Read_Door_State
 * Period:		0.012
 *****************************************************/
void Read_Door_State_Runnable(void)
{
	myuint8 Door_State=0;
	Door_State=Rte_IRead_Read_Door_State_Read_Door_State_RP_DOOR_State_Sensor_Reading();
	Rte_IWrite_Read_Door_State_Read_Door_State_PP_DOOR_State_Door_State(Door_State);
}

