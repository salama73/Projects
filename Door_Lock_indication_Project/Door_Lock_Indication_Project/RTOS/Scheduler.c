/*
 * Scheduler.c
 *  Created on: 27/4/2023
 *  Author: Salama mohamed
 */


#include "Scheduler.h"
#include"MY_RTOS_FIFO.h"

uint8_t IdleTaskLED;

/*
 * ===============================================================
 *
 *                      Generic Variable
 *
 * ===============================================================
 * */
struct {
	Task_Ref* OSTasks[100]			; //Scheduler Table
	unsigned int _S_MSP_Task 		;
	unsigned int _E_MSP_Task 		;
	unsigned int PSP_Task_Locator 	;
	unsigned int NoOfActiveTasks 	;
	Task_Ref* CurrentTask 			;
	Task_Ref* NextTask 				;
	enum{
		OSsuspend,
		OsRunning
	}OSmodeID;
}OS_Control;


typedef enum {
	SVC_Activatetask,
	SVC_terminateTask,
	SVC_TaskWaitingTime,
	SVC_AquireMutex,
	SVC_ReleaseMutex
}SVC_ID;


FIFO_Buf_t Ready_QUEUE ;

Task_Ref* Ready_QUEUE_FIFO[100] ;
Task_Ref MYRTOS_idleTask;

// idle task
void MYRTOS_IdleTask()
{
	while(1)
	{
		IdleTaskLED ^=1;
		__asm("WFE");
	}
}

/*
 * ===============================================================
 *
 *                      Function
 *
 * ===============================================================
 */

/**
* @Fn          - PendSV_Handler
* @brief       - Interrupt handler for PendSV to switch Context and restore to cpu register
* @retval      - None
* note         - Since the function is declared with the naked attribute, it is responsible
* 				for managing the necessary operations within the interrupt handler,
* 				such as saving and restoring task context, updating task states,
* 				or performing other operations related to task scheduling or context management.
*/
__attribute ((naked)) void PendSV_Handler()
{
	//====================================
	//Save the Context of the Current Task
	//====================================
	//Get the Current Task "Current PSP from CPU register" as CPU Push
	OS_GET_PSP(OS_Control.CurrentTask->Current_PSP);

	//using this Current_PSP store from R4 to R11
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("mov %0,r4 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("mov %0,r5 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("mov %0,r6 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("mov %0,r7 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("mov %0,r8 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("mov %0,r9 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("mov %0,r10 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("mov %0,r11 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	/*
	 * save the current Value of PSP
	 * already saved in Current_PSP
	 */
	//====================================
	//Restore the Context of the Next Task
	//====================================
	if (OS_Control.NextTask != NULL)
	{
	OS_Control.CurrentTask = OS_Control.NextTask ;
	OS_Control.NextTask = NULL ;
	}
	__asm volatile("mov r11,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("mov r10,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("mov r9,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("mov r8,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("mov r7,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("mov r6,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("mov r5,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("mov r4,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	//update PSP and exit
	OS_SET_PSP(OS_Control.CurrentTask->Current_PSP);
	// return to next task
	__asm volatile("BX LR");
}


/**
* @Fn          - MYRTOS_Create_MainStack
* @brief       - Creates the main stack for the MYRTOS (My Real-Time Operating System)
* @retval      - None
*/
void MYRTOS_Create_MainStack()
{
	OS_Control._S_MSP_Task = &_estack;
	OS_Control._E_MSP_Task = OS_Control._S_MSP_Task - MainStackSize;
	//Aligned 8 Bytes spaces between Main Task and PSP tasks
	OS_Control.PSP_Task_Locator = (OS_Control._E_MSP_Task - 8);
	//if (_E_MSP_Task <&_eheap) Error:excedded the available stack size
}

/**
* @Fn          - MYRTOS_Init
* @brief       - Initializes the MYRTOS (My Real-Time Operating System)
* @retval      - The error code indicating the success or failure of the initialization process
*/
MY_RTOS_ErrorID MYRTOS_Init()
{
	MY_RTOS_ErrorID error = NO_ERROR ;
	//Update OS Mode (OSsuspend)
	OS_Control.OSmodeID = OSsuspend ;
	//Create main Stack for OS
	MYRTOS_Create_MainStack();
	//Create OS Ready Queue
	if (FIFO_init(&Ready_QUEUE, Ready_QUEUE_FIFO, 100) !=FIFO_NO_ERROR)
	{
		error = Ready_Queue_Init_Error ;
	}
	//Configure IDLE TASK
	strcpy (MYRTOS_idleTask.TaskName, "idleTask");
	MYRTOS_idleTask.priority = 255 ;
	MYRTOS_idleTask.P_TaskEntry = MYRTOS_IdleTask ;
	MYRTOS_idleTask.Stack_Size = 300 ;
	error = MYRTOS_CreateTask(&MYRTOS_idleTask);
	return error ;
}

/**
* @Fn          - MyRTOS_Create_TaskStack
* @brief       - Creates the stack for a specific task in MyRTOS
* @param [in]  - Tref: Pointer to the Task_Ref structure representing the task
* @retval      - None
*/
void MyRTOS_Create_TaskStack(Task_Ref* Tref)
{
	/*Task Frame
	 * ======
	 * XPSR
	 * PC (Next Task Instruction which should be Run)
	 * LR (return register which is saved in CPU while TASk1 running before TaskSwitching)
	 * r12
	 * r4
	 * r3
	 * r2
	 * r1
	 * r0
	 *====
	 *R5-R6-R7-R8-R9-R10-R11 Saved and Restore Manual
	 * DUMMY Value
	 * XPSR should T =1 to thumb mode
	 * LR = 0xFFFFFFFD (EXC_RETURN)Return to thread with PSP
	 */
	//set current PSP
	Tref->Current_PSP = Tref->_S_PSP_Task ;
	Tref->Current_PSP-- ;
	*(Tref->Current_PSP) = 0x01000000;
	Tref->Current_PSP-- ;
	*(Tref->Current_PSP) = (uint32_t)Tref->P_TaskEntry ;
	Tref->Current_PSP-- ;
	*(Tref->Current_PSP)  = 0xFFFFFFFD ;
	//set R0 to R12 by value 0
	for (int  i=0 ; i< 13 ; i++ )
	{
		Tref->Current_PSP-- ;
		*(Tref->Current_PSP)  = 0 ;
	}
}


/**
* @Fn          - MYRTOS_CreateTask
* @brief       - Creates a new task in MyRTOS
* @param [in]  - Tref: Pointer to the Task_Ref structure representing the task
* @retval      - The error code indicating the success or failure of the task creation
*/
MY_RTOS_ErrorID MYRTOS_CreateTask(Task_Ref* Tref)
{
	MY_RTOS_ErrorID error = NO_ERROR ;
	//Create Its OWN PSP Stack
	// Start PSP Stack for Tref
	Tref->_S_PSP_Task = OS_Control.PSP_Task_Locator;
	// End PSP Stack for Tref
	Tref->_E_PSP_Task = Tref->_S_PSP_Task - Tref->Stack_Size ;
	//check that the stack task  does not exceed the stack size
	if(Tref->_E_PSP_Task < (uint32_t)(&(_eheap)))
	{
		return Task_exceeded_StackSize ;
	}
	//Aligned 8 Bytes spaces between Current Task PSP and next
	OS_Control.PSP_Task_Locator=(Tref->_E_PSP_Task-8);
	//Initialize PSP Task Stack
	MyRTOS_Create_TaskStack(Tref);
	//update Scheduler Table
	OS_Control.OSTasks[OS_Control.NoOfActiveTasks]= Tref ;
	OS_Control.NoOfActiveTasks++ ;
	//Task by default State is Suspend
	if(Tref->Auto_Start)
	{
		MYRTOS_ActivateTask(Tref);
	}
	else
		Tref->TaskState = Suspend ;
	return error ;
}


void bubbleSort()
{
	unsigned int i, j , n;
	Task_Ref* temp ;
	n=OS_Control.NoOfActiveTasks ;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (OS_Control.OSTasks[j]->priority > OS_Control.OSTasks[j + 1]->priority)
			{
				temp = OS_Control.OSTasks[j] ;
				OS_Control.OSTasks[j] = OS_Control.OSTasks[j + 1 ] ;
				OS_Control.OSTasks[j + 1] = temp ;
			}
}

/**
* @Fn          - MyRTOS_Update_Schedule_tables
* @brief       - Updates the schedule tables in MyRTOS
* @retval      - The error code indicating the success or failure of the update process
*/
MY_RTOS_ErrorID MyRTOS_Update_Schadule_tables()
{
	MY_RTOS_ErrorID error=NO_ERROR;
	Task_Ref* temp =NULL ;
	Task_Ref* Ptask ;
	Task_Ref* PnextTask ;
	int i = 0 ;
	//1- bubble sort SchTable OS_Control priority high then low
	bubbleSort();
	//2-free Ready Queue
	while(FIFO_dequeue(&Ready_QUEUE,&temp )!=FIFO_EMPTY);
	//3- update ready queue
	while(i< OS_Control.NoOfActiveTasks)
	{
		Ptask = OS_Control.OSTasks[i] ;
		PnextTask = OS_Control.OSTasks[i+1] ;
		if (Ptask->TaskState != Suspend)
		{
			//	if the Ptask priority > next task then hear 15<14
			if (Ptask->priority < PnextTask->priority )
			{
				FIFO_enqueue(&Ready_QUEUE, Ptask);
				Ptask->TaskState = Ready ;
				break ;
			}
			else if (Ptask->priority == PnextTask->priority)
			{
				/*
				 * push Ptask to ready state
				 * again process
				 */
				FIFO_enqueue(&Ready_QUEUE, Ptask);
				Ptask->TaskState = Ready ;
			}
			else if (Ptask->priority > PnextTask->priority)
			{
				if((i+1)<OS_Control.NoOfActiveTasks)
				{
					//Return error
					error=SO_Table_Sort_Error;
					return error;
				}
				//MYRTOS_IdleTask
				FIFO_enqueue(&Ready_QUEUE, Ptask);
				Ptask->TaskState = Ready ;
				break ;
			}
		}
		i++ ;
	}
}


/**
* @Fn          - Decide_whatNext
* @brief       - Makes decisions on the next task to execute based on the current state and priority in an RTOS
* @retval      - None
*/
void Decide_whatNext()
{
	//if Ready Queue is empty && OS_Control->currentTask != suspend
	if (Ready_QUEUE.counter == 0 && OS_Control.CurrentTask->TaskState != Suspend)
	{
		OS_Control.CurrentTask->TaskState = Running ;
		//add the current task again(round robin)
		FIFO_enqueue(&Ready_QUEUE, OS_Control.CurrentTask);
		OS_Control.NextTask = OS_Control.CurrentTask ;
	}
	else
	{
		FIFO_dequeue(&Ready_QUEUE, &OS_Control.NextTask);
		OS_Control.NextTask->TaskState = Running ;
		//update Ready queue (to keep round round robin Algorithm happen)
		if ((OS_Control.CurrentTask->priority == OS_Control.NextTask->priority )&&(OS_Control.CurrentTask->TaskState != Suspend))
		{
			FIFO_enqueue(&Ready_QUEUE, OS_Control.CurrentTask);
			OS_Control.CurrentTask->TaskState = Ready ;
		}
	}
}

/**
* @Fn          - OS_SV
* @brief       - Handles the Supervisor Call (SV) interrupt in the OS context
* @param [in]  - Stack_Frame: Pointer to the stack frame containing the saved registers
* @retval      - None
*/
void OS_SV(int* Stack_Frame)
{
	uint8_t SVC_Number;
	SVC_Number=*((uint8_t*)(((uint8_t*)Stack_Frame[6])-2));
	switch(SVC_Number)
	{
	case SVC_Activatetask:
	case SVC_terminateTask:
		//Update Scheduler table and ready queue
		MyRTOS_Update_Schadule_tables();
		//OS is in Running State
		if (OS_Control.OSmodeID == OsRunning)
		{
			if (strcmp(OS_Control.CurrentTask->TaskName,"idleTask") != 0)
			{
				//Decide what Next
				Decide_whatNext();
				//trigger OS_pendSV (Switch Context/Restore)
				trigger_OS_PendSV();
			}
		}
		break;
	case SVC_TaskWaitingTime:
		//Update Scheduler table and ready queue
		MyRTOS_Update_Schadule_tables();
		break;
	case 3:

		break;
	}
}

/**
* @Fn          - MYRTOS_OS_SVC_Set
* @brief       - Sets the appropriate Supervisor Call (SVC) instruction based on the given SVC ID
* @param [in]  - ID: The SVC ID representing the desired SVC operation
* @retval      - None
*/
void MYRTOS_OS_SVC_Set(SVC_ID ID)
{
	switch (ID)
	{
	case SVC_Activatetask:
		__asm("svc #0x00");
		break;
	case SVC_terminateTask:
		__asm("svc #0x01");
		break;
	case SVC_TaskWaitingTime:
		__asm("svc #0x02");
		break;
	}
}

/**
* @Fn          - MYRTOS_ActivateTask
* @brief       - Activates a task in MyRTOS
* @param [in]  - Tref: Pointer to the Task_Ref structure representing the task to activate
* @retval      - None
*/
void MYRTOS_ActivateTask (Task_Ref* Tref)
{
	Tref->TaskState=Waiting;
	MYRTOS_OS_SVC_Set(SVC_Activatetask);
}

/**
* @Fn          - MYRTOS_TerminateTask
* @brief       - Terminates a task in MyRTOS
* @param [in]  - Tref: Pointer to the Task_Ref structure representing the task to terminate
* @retval      - None
*/
void MYRTOS_TerminateTask (Task_Ref* Tref)
{
	Tref->TaskState = Suspend ;
	MYRTOS_OS_SVC_Set(SVC_terminateTask);
}

/**
* @Fn          - MYRTOS_TaskWait
* @brief       - Puts a task in a waiting state for a specified number of ticks
* @param [in]  - Num_Tick: Number of ticks to wait
* @param [in]  - Tref: Pointer to the Task_Ref structure representing the task
* @retval      - None
*/
void MYRTOS_TaskWait(unsigned int Num_Tick,Task_Ref* Tref)
{
	Tref->Timing_Waiting.Blocking = enable ;
	Tref->Timing_Waiting.Ticks_Count = Num_Tick ;
	// Task Should be blocked Until reached Number of Ticks
	Tref->TaskState = Suspend ;
	//terminate task
	MYRTOS_OS_SVC_Set(SVC_terminateTask);
}


/**
* @Fn          - MYRTOS_Update_TasksWaitingTime
* @brief       - Updates the waiting time of tasks in MyRTOS
* @retval      - None
*/
void MYRTOS_Update_TasksWaitingTime()
{
	for (int i =0; i < OS_Control.NoOfActiveTasks ; i++)
	{
		if (Suspend==OS_Control.OSTasks[i]->TaskState)
		{
			if (enable==OS_Control.OSTasks[i]->Timing_Waiting.Blocking)
			{
				OS_Control.OSTasks[i]->Timing_Waiting.Ticks_Count-- ;
				if (OS_Control.OSTasks[i]->Timing_Waiting.Ticks_Count == 1)
				{
					OS_Control.OSTasks[i]->Timing_Waiting.Blocking = disable ;
					OS_Control.OSTasks[i]->TaskState = Waiting ;
					MYRTOS_OS_SVC_Set(SVC_TaskWaitingTime);
				}
			}
		}
	}
}

/**
* @Fn          - MYRTOS_STARTOS
* @brief       - Starts the MyRTOS scheduler
* @retval      - None
*/
void MYRTOS_STARTOS()
{
	OS_Control.OSmodeID = OsRunning ;
	//Set Default "Current Task =Idle Task"
	OS_Control.CurrentTask = &MYRTOS_idleTask ;
	//Activate IDLE Task
	MYRTOS_ActivateTask(&MYRTOS_idleTask);
	//Start Ticker
	Start_Ticker(); // 1ms

	OS_SET_PSP(OS_Control.CurrentTask->Current_PSP);
	//Switch Thread Mode SP from MSP to PSP
	OS_Switch_SP_PSP;
	CPU_Access_Level_Unprivileged();
	MYRTOS_idleTask.P_TaskEntry();
}


/**
* @Fn          - MYRTOS_AcquireMutex
* @brief       - Acquires a mutex in MyRTOS
* @param [in]  - Mref: Pointer to the Mutex_Ref structure representing the mutex
* @param [in]  - Tref: Pointer to the Task_Ref structure representing the task
* @retval      - The error code indicating the success or failure of acquiring the mutex
*/
MY_RTOS_ErrorID MYRTOS_AcquireMutex(Mutex_Ref* Mref , Task_Ref* Tref)
{
	// Mutex not used or AcquireMutex by same task
	if(Mref->CurrentTUser == NULL || Mref->CurrentTUser==Tref )
	{
		Mref->CurrentTUser = Tref ;
	}
	else
	{
		if(Mref->NextTUser == NULL)
		{
			Mref->NextTUser = Tref ;
			/*
			 * Solution priority inversion used ceiling protocol
			 * save priority for current task
			 * Give the highest priority to the current task(0) " current task---> Acquire Mutex "
			 */
			Mref->priority_Inversion=Mref->CurrentTUser->priority;
			Mref->CurrentTUser->priority=0;

			//move to Suspend state until be released Mutex
			Tref->TaskState = Suspend ;
			MYRTOS_OS_SVC_Set(SVC_terminateTask);

		}
		else
		{
			return MutexisReacedToMaxNumberOfUsers ;
		}
	}
	return NO_ERROR;
}


/**
* @Fn          - MYRTOS_ReleaseMutex
* @brief       - Releases a mutex in MyRTOS
* @param [in]  - Mref: Pointer to the Mutex_Ref structure representing the mutex
* @param [in]  - Tref: Pointer to the Task_Ref structure representing the task
* @retval      - The error code indicating the success or failure of releasing the mutex
*/
void MYRTOS_ReleaseMutex(Mutex_Ref* Mref , Task_Ref* Tref)
{
	if(Mref->CurrentTUser != NULL && Mref->CurrentTUser==Tref)
	{
		/*
		 * Solution priority inversion used ceiling protocol
		 * set old priority for current task
		 */

		if(Mref->NextTUser != NULL)
		{
			Mref->CurrentTUser->priority=Mref->priority_Inversion;
			Mref->CurrentTUser = Mref->NextTUser 		;
			Mref->NextTUser  = NULL 					;
			Mref->CurrentTUser->TaskState = Waiting 	;
			MYRTOS_OS_SVC_Set(SVC_Activatetask)			;
		}
	}
}


/**
* @Fn          - MYRTOS_AcquireSemaphore
* @brief       - Acquires a semaphore in MyRTOS
* @param [in]  - Sref: Pointer to the Semaphore_Ref structure representing the semaphore
* @param [in]  - Tref: Pointer to the Task_Ref structure representing the task
* @retval      - The error code indicating the success or failure of acquiring the semaphore
*/
MY_RTOS_ErrorID MYRTOS_AcquireSemaphore(Semaphore_Ref* Sref ,Task_Ref* Tref)
{
	// Semaphore not used
	if(Sref->state != 1)
	{
		Sref->state=1;
		Sref->CurrentTUser=Tref;
	}
	else if(Sref->CurrentTUser !=Tref)
	{
		//move to Suspend state until be released Semaphore
		Tref->TaskState = Suspend ;
		Sref->NextTUser=Tref;
		MYRTOS_OS_SVC_Set(SVC_terminateTask);
	}
	return NO_ERROR;
}

/**
* @Fn          - MYRTOS_ReleaseSemaphore
* @brief       - Releases a semaphore in MyRTOS
* @param [in]  - Sref: Pointer to the Semaphore_Ref structure representing the semaphore
* @retval      - The error code indicating the success or failure of releasing the semaphore
*/
void MYRTOS_ReleaseSemaphore(Semaphore_Ref* Sref)
{
	if(Sref->state != 0)
	{
		Sref->state=0;
		if(Sref->NextTUser != NULL)
		{
			Sref->NextTUser->TaskState = Waiting 	    ;
			Sref->CurrentTUser = Sref->NextTUser		;
			Sref->NextTUser = NULL 						;
			MYRTOS_OS_SVC_Set(SVC_Activatetask)			;
		}
	}
}

