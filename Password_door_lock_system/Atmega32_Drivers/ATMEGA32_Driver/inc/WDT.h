/*
 * WDT.h
 *
 * Created: 11/8/2022 9:09:21 PM
 *  Author: vip
 */ 


#ifndef WDT_H_
#define WDT_H_

#include "Atmega32.h"

void MCAL_WDT_Init(uint8_t Wait_Time);//this parameter must be set based on  @ ref  WDT_Wait_Time_Define
void MCAL_WDT_ON(void);
void MCAL_WDT_OFF(void);


//@ ref  WDT_Wait_Time_Define
#define WDT_Wait_Time_17ms			(uint8_t)0
#define WDT_Wait_Time_34ms			(uint8_t)(1<<0)
#define WDT_Wait_Time_68ms			(uint8_t)(2<<0)
#define WDT_Wait_Time_140ms			(uint8_t)(3<<0)
#define WDT_Wait_Time_270ms			(uint8_t)(4<<0)
#define WDT_Wait_Time_550ms			(uint8_t)(5<<0)
#define WDT_Wait_Time_1100ms		(uint8_t)(6<<0)
#define WDT_Wait_Time_2200ms		(uint8_t)(7<<0)
#endif /* WDT_H_ */