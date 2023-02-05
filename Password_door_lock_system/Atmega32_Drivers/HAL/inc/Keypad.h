/*
 * Keypad.h
 *
 * Created: 11/8/2022 4:05:48 AM
 *  Author: vip
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "GPIO_Driver.h"


#define R0    GPIO_PIN_0
#define R1    GPIO_PIN_1
#define R2    GPIO_PIN_2
#define R3    GPIO_PIN_3
#define C0    GPIO_PIN_4
#define C1    GPIO_PIN_5
#define C2    GPIO_PIN_6
#define C3    GPIO_PIN_7

#define Keypad_port				GPIOD
#define Keypad_Col_port         GPIOC


void keypad_init(void);
char keypad_getkey(void);

#endif /* KEYPAD_H_ */