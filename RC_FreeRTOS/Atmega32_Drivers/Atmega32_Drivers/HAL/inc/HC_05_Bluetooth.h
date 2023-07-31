/*
 * HC_05_Bluetooth.h
 *
 * Created: 15/10/2022
 * Author : Salama Mohamed
 */ 


#ifndef HC_05_BLUETOOTH_H_
#define HC_05_BLUETOOTH_H_

#include "USART_Driver.h"

enum interrupt
{
	INT_Enable ,
	INT_Disable
};



void Bluetooth_Init( enum interrupt State ) ;

void Bluetooth_TX_Byte(uint8_t* PTXBuffer) ;

void Bluetooth_TX_Str(uint8_t* PTXBuffer) ;

void Bluetooth_RX_Byte(uint8_t* PRXBuffer) ;

void Bluetooth_RX_Str(uint8_t* PRXBuffer) ;

void ISR_Bluetooth (void) ;

#endif /* HC_05_BLUETOOTH_H_ */