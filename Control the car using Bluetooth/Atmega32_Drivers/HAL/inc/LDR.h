/*
 * LDR.h
 *
 * Created: 12/6/2022 2:59:37 PM
 *  Author: Salama Mohammed
 */ 


#ifndef LDR_H_
#define LDR_H_

#include "ADC.h" 

void LDR_Init(void);

uint16_t LDR_Get_Val(enum NUM_CH CH);


#endif /* LDR_H_ */