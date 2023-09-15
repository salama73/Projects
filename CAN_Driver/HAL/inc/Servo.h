/*
 * Servo.h
 *
 *  Created on: 20/2/2023
 *  Author: Salama mohamed
 */


#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include <stm32_f103c6_TIM2_3.h>
#include "delay.h"
#include "stm32_f103c6_RCC.h"

void Servo_Init(void) ;

void My_Servo(uint8_t angle) ;

void Servo_DInit(void) ;

#endif /* INC_SERVO_H_ */
