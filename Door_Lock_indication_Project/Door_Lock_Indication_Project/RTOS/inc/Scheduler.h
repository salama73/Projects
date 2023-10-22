/*
 * Scheduler.h
 *  Created on: 27/4/2023
 *  Author: Salama mohamed
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_


#include "Cortex_Mx_Porting.h"

typedef enum
{
	NO_ERROR,
	Ready_Queue_Init_Error,
	Task_exceeded_StackSize,
	SO_Table_Sort_Error,
	MutexisReacedToMaxNumberOfUsers
}MY_RTOS_ErrorID;


typedef struct
{
	uint32_t Stack_Size			;
	uint8_t priority			;
	void (*P_TaskEntry)(void)	; //pointer to Tack C Function
	uint32_t _S_PSP_Task 		;//Not Entered by the user
	uint32_t _E_PSP_Task 		;//Not Entered by the user
	uint32_t* Current_PSP 		;//Not Entered by the user
	int8_t TaskName[30] 		;
	enum
	{
		Suspend,
		Running,
		Waiting,
		Ready
	}TaskState					;//Not Entered by the user
	enum
	{
		Task_Suspend,
		Task_Start
	}Auto_Start					;
	struct
	{
		enum
		{
			disable,
			enable
		}Blocking;
		uint32_t Ticks_Count ;
	}Timing_Waiting;
}Task_Ref;


typedef struct
{
	unsigned char* Ppayload					;
	unsigned int   PayloadSize 				;
	Task_Ref* 	   CurrentTUser 			;//Not Entered by the user
	Task_Ref* 	   NextTUser 				;//Not Entered by the user
	char 		   MutexName[30]  			;
	uint8_t 		priority_Inversion		;//Not Entered by the user
} Mutex_Ref;


typedef struct
{
	unsigned char* Ppayload					;
	Task_Ref* 	   CurrentTUser 			;//Not Entered by the user
	Task_Ref* 	   NextTUser 				;//Not Entered by the user
	char 		   SemaphoreName[30]  		;
	uint8_t 		state					;//Not Entered by the user
} Semaphore_Ref;



/*
 * *************************************************************
 * 						APIS
 ***************************************************************
 */

MY_RTOS_ErrorID MYRTOS_Init();
MY_RTOS_ErrorID MYRTOS_CreateTask(Task_Ref* Tref);
void MYRTOS_ActivateTask (Task_Ref* Tref);
void MYRTOS_TerminateTask (Task_Ref* Tref);
void MYRTOS_STARTOS();
void MYRTOS_TaskWait(unsigned int Num_Tick,Task_Ref* Tref);
MY_RTOS_ErrorID MYRTOS_AcquireMutex(Mutex_Ref* Mref , Task_Ref* Tref);
void MYRTOS_ReleaseMutex(Mutex_Ref* Mref , Task_Ref* Tref);
MY_RTOS_ErrorID MYRTOS_AcquireSemaphore(Semaphore_Ref* Sref ,Task_Ref* Tref);
void MYRTOS_ReleaseSemaphore(Semaphore_Ref* Sref);

#endif /* INC_SCHEDULER_H_ */
