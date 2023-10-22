/*
 * Cortex_Mx_Porting.h
 *  Created on: 27/4/2023
 *  Author: Salama mohamed
 */

#ifndef INC_CORTEX_MX_PORTING_H_
#define INC_CORTEX_MX_PORTING_H_

#include "core_cm3.h"

extern int _estack ;
extern int _eheap  ;
#define MainStackSize 	3072

#define OS_SET_PSP(TOP_Add)     __asm("MOV R0,%[in] \t\n MSR PSP,R0"  : :[in] "r" (TOP_Add))

#define OS_GET_PSP(TOP_Add)     __asm("MRS R0,PSP \t\n MOV %[OUT],R0" :[OUT] "=r" (TOP_Add))

#define OS_Switch_SP_PSP        __asm("MRS R0,CONTROL \t\n ORR R0,R0,#0x2 \t\n MSR CONTROL,R0")

#define OS_Switch_SP_MSP        __asm("MRS R0,CONTROL \t\n AND R0,R0,#0x5 \t\n MSR CONTROL,R0")

#define CPU_Access_Level_Unprivileged()     { __asm("MRS R3,CONTROL"); \
                                              __asm("ORR R3,R3,#0x01"); \
                                              __asm("MSR CONTROL,R3"); \
                                             }

#define CPU_Access_Level_Privileged()        {__asm("MRS R3,CONTROL"); \
                                              __asm("LSR R3,R3,#0x01"); \
                                              __asm("LSL R3,R3,#0x01"); \
                                              __asm("MSR CONTROL,R3"); \
                                             }

void HW_init();
void trigger_OS_PendSV();
void Start_Ticker();

#endif /* INC_CORTEX_MX_PORTING_H_ */
