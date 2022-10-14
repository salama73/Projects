/*
 * Keypad.h
 *
 * Created: 25/08/2022 01:25:31 ص
 *  Author: elmnshawy
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "stm32_f103c6_GPIO.h"
#include "stm32f103x6.h"

#define R0    GPIO_PIN_0
#define R1    GPIO_PIN_1
#define R2    GPIO_PIN_3
#define R3    GPIO_PIN_4
#define C0    GPIO_PIN_5
#define C1    GPIO_PIN_6
#define C2    GPIO_PIN_7
#define C3    GPIO_PIN_8
 
#define Keypad_port         GPIOB

void keypad_init(void);
char keypad_getkey(void);

#endif /* KEYPAD_H_ */
