/*
 * RC_Car.h
 * Created: 25/07/2023
 * Author : Salama Mohamed
 */ 


#ifndef RC_CAR_H_
#define RC_CAR_H_

/*********************************************************************************
***********************************Include****************************************
*********************************************************************************/
#include "GPIO_Driver.h"
#include "LCD.h"
#include "HC_05_Bluetooth.h"
#include "TIMER0_Driver.h"
#include "DC_MOTOR.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "StackMacros.h"
/*********************************************************************************
***********************************APIS*******************************************
*********************************************************************************/
void GPIO_Init(void);
void Timer0_init(void);
/*********************************************************************************
***********************************Task Call Back*********************************
*********************************************************************************/
void Task_init(void);
void CMD_RX(void *pvparam);
void Moter_State(void *pvparam);
void Set_Speed(void *pvparam);
void Print_State(void *pvparam);
void Traffic_State(void *pvparam);
void Turn_Signal_State(void *pvparam);
/*********************************************************************************
***********************************End********************************************
*********************************************************************************/
#endif /* RC_CAR_H_ */