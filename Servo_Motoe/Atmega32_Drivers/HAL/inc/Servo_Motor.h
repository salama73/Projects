/*
 * Servo_Motor.h
 *
 * Created: 10/13/2022 11:07:55 PM
 *  Author: Salama Mohamed
 */ 


#ifndef SERVO_MOTOR_H_
#define SERVO_MOTOR_H_

#include "PWM_Driver.h"

void Servo_Init(void) ;

void My_Servo(uint8_t angle) ;

void Servo_DInit(void) ;

#endif /* SERVO_MOTOR_H_ */