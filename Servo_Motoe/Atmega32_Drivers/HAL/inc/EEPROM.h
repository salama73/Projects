/*
 * EEPROM.h
 *
 * Created: 9/29/2022 12:31:48 AM
 *  Author: salama
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "I2C_Driver.h"

#define EEPROM_Slave_Address_Write	0xA6  // default Address
#define EEPROM_Slave_Address_Read	0xA7  // default Address

void EEPROM_Init(void);
unsigned char EEPROM_Write_Data(uint16_t EEPROM_Address , uint8_t PTXBuffer );
unsigned char EEPROM_Read_Data( uint16_t EEPROM_Address );

#endif /* EEPROM_H_ */