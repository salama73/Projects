/*
 * WDT.c
 *
 * Created: 11/8/2022 9:09:37 PM
 *  Author: vip
 */ 

#include "WDT.h"

void MCAL_WDT_Init(uint8_t Wait_Time)
{
	WDTCR = Wait_Time ;
}


void MCAL_WDT_ON(void)
{
	WDTCR |= (1 << 3);
}

void MCAL_WDT_OFF(void)
{
	WDTCR = (1<<4)|(1<<3);
	WDTCR = 0x00;
}