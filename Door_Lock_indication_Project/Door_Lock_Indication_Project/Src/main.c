/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Salama Mohamed
 * @brief          : Main program body
 ******************************************************************************
*/

/**************************************************************
 *************************Include File ************************
 *************************************************************/
#include "Scheduler.h"
#include "Port.h"
#include "Pwm.h"
#include "Dio.h"
#include "stm32f103x6.h"
/**************************************************************
 *************************Global Variable *********************
 **************************************************************/
extern const Port_ConfigType Port;
MY_RTOS_ErrorID Error;
Task_Ref _10ms_Task;
Task_Ref _12ms_Task;
Task_Ref _15ms_Task;
Task_Ref _18ms_Task;
/**************************************************************
 *************************Task*********************************
 **************************************************************/
void _10ms_task(void)
{
	while(1)
	{
		Read_Door_Sensor_Runnable();
		MYRTOS_TaskWait(10,&_10ms_Task);
	}
}
void _12ms_task(void)
{
	while(1)
	{
		Read_Door_State_Runnable();
		MYRTOS_TaskWait(12,&_12ms_Task);
	}
}
void _15ms_task(void)
{
	while(1)
	{
		IB_DoorLock_indication_Runnable();
		MYRTOS_TaskWait(15,&_15ms_Task);
	}
}
void _18ms_task(void)
{
	while(1)
	{
		Read_LED_State_Runnable();
		MYRTOS_TaskWait(18,&_18ms_Task);
	}
}
/**************************************************************
 *************************Init Functions **********************
 **************************************************************/
void OS(void)
{
	_10ms_Task.P_TaskEntry=_10ms_task;
	_10ms_Task.Stack_Size=512;
	_10ms_Task.Auto_Start=Task_Start;
	strcpy(_10ms_Task.TaskName,"10ms_Task");
	_10ms_Task.priority=1;

	_12ms_Task.P_TaskEntry=_12ms_task;
	_12ms_Task.Stack_Size=512;
	_12ms_Task.Auto_Start=Task_Start;
	strcpy(_12ms_Task.TaskName,"12ms_Task");
	_12ms_Task.priority=1;

	_15ms_Task.P_TaskEntry=_15ms_task;
	_15ms_Task.Stack_Size=512;
	_15ms_Task.Auto_Start=Task_Start;
	strcpy(_15ms_Task.TaskName,"15ms_Task");
	_15ms_Task.priority=1;

	_18ms_Task.P_TaskEntry=_18ms_task;
	_18ms_Task.Stack_Size=512;
	_18ms_Task.Auto_Start=Task_Start;
	strcpy(_18ms_Task.TaskName,"18ms_Task");
	_18ms_Task.priority=1;

	Error=MYRTOS_CreateTask(&_10ms_Task);
	Error=MYRTOS_CreateTask(&_12ms_Task);
	Error=MYRTOS_CreateTask(&_15ms_Task);
	Error=MYRTOS_CreateTask(&_18ms_Task);
	MYRTOS_STARTOS();

}
void MCU_init ()
{
	HW_init();
	RCC_GPIOA_CLK_Enable();
	RCC_TIM2_CLK_Enable();
	RCC_GPIOB_CLK_Enable();
	RCC_GPIOC_CLK_Enable();
	Port_Init(&Port);
	if (MYRTOS_Init() != NO_ERROR)
		while (1);
}
/**************************************************************
 *************************Main ********************************
 **************************************************************/
int main(void)
{
	MCU_init();
	OS();
	while(1)
	{

	}
}
/**************************************************************
 *************************End *********************************
 **************************************************************/
