/*
 * UltraSonic.h
 *
 * Created: 12/5/2022 12:55:08 AM
 *  Author: Salama Mohammed
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_


#include "GPIO_Driver.h"

void UltraSonic_Init(void);
double UltraSonic_Get_Distance(void);



#endif /* ULTRASONIC_H_ */