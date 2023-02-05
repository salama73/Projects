/*
 * EEPROM.h
 *
 * Created: 29/09/2022
 * Author : salama mohamed
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "I2C_Driver.h"

#define EEPROM_Slave_Address_Write	0xA6  // default Address
#define EEPROM_Slave_Address_Read	0xA7  // default Address

void EEPROM_Init(void);
void EEPROM_Write_Data(uint16_t EEPROM_Address , uint8_t* PTXBuffer , uint8_t Dataln);
void EEPROM_Read_Data( uint16_t EEPROM_Address , uint8_t* PRXBuffer , uint8_t Dataln );

#endif /* EEPROM_H_ */