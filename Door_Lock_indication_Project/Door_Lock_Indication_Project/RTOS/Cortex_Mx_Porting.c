/*
 * Cortex_Mx_Porting.c
 *  Created on: 27/4/2023
 *  Author: Salama mohamed
 */

#include "Cortex_Mx_Porting.h"

uint8_t SysTickLED;

void HardFault_Handler(void)
{
	while(1);
}

void MemManage_Handler(void)
{
	while(1);
}

void vBusFault_Handler(void)
{
	while(1);
}

void UsageFault_Handler(void)
{
	while(1);
}

__attribute((naked)) void SVC_Handler (void)
{
    __asm(  "TST LR,#4\n\t"
    		"ITE EQ \n\t"
    		"MRSEQ R0,MSP\n\t"
    		"MRSNE R0,PSP\n\t"
    		"B OS_SV");
}

void HW_init()
{
	/*
	 * Initialize Clock Tree (RCC -> SysTick Timer & CPU) 8MHZ
	 * Clock tree
	 * RCC Default Values makes CPU Clock & SySTick Timer clock=8MHZ
	 * 8 MHZ
	 * 1 count -> 0.125 us
	 * X count -> 1 ms
	 * X = 8000 Count
	 */
	__NVIC_SetPriority(PendSV_IRQn, 15) ;

}
void trigger_OS_PendSV()
{
	SCB->ICSR|=SCB_ICSR_PENDSVSET_Msk;
}

void Start_Ticker()
{
	/*
	 * This clock tree should be defined in HW_init()
	 * 8 MHZ
	 * 1 count -> 0.125 us
	 * X count -> 1 ms
	 * X = 8000 Count
	 */
	 SysTick_Config(8000);
}

void SysTick_Handler(void)
{
	SysTickLED ^= 1 ;
	//MYRTOS_Update_TasksWaitingTime();
	MYRTOS_Update_TasksWaitingTime();
	//Determine Pcurrent & Pnext
	Decide_whatNext();
	//Switch Context & restore
	trigger_OS_PendSV();
}
