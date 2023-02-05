/*
 * DHT11.h
 *
 * Created: 08/09/2022 02:14:12 ص
 *  Author: Salama Mohammed
 */ 


#ifndef DHT11_H_
#define DHT11_H_

#include "Atmega32.h"
#include "GPIO_Driver.h"

#define DHT11_Pin	GPIO_PIN_6

void Request()	;			//  send start pulse to request 
void Response()	;			// receive response from DHT11 to MCU
uint8_t Receive_data() ;	// receive data 



#endif /* DHT11_H_ */