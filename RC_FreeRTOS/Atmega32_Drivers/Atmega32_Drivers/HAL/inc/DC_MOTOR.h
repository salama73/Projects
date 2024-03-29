/*
 * DC_MOTOR.h
 *
 * Created: 12/4/2022 11:31:03 PM
 *  Author: Salama Mohammed
 */ 


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "PWM_Driver.h"

void MOTOR_Init(void) ;

void MOTOR_Speed(uint8_t speed) ;

void MOTOR_Right(void);

void MOTOR_Left(void);

void MOTOR_Stop(void);

void MOTOR_Forward(void);

void MOTOR_Back(void);



#endif /* DC_MOTOR_H_ */