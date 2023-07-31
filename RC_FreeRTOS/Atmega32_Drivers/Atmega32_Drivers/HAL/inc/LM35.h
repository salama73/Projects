/*
 * ILM35.h
 *
 * Created: 12/6/2022 3:05:51 PM
 *  Author: Salama Mohammed
 */ 


#ifndef ILM35_H_
#define ILM35_H_


#include "ADC.h" 

void LM35_Init(enum NUM_CH CH);

uint16_t LM35_Get_Tem(enum NUM_CH CH);



#endif /* ILM35_H_ */