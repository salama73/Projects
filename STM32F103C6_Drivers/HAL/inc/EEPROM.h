/*
 * EEPROM.h
 *
 *  Created on: Sep 21, 2022
 *      Author: salama
 */

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

#include "stm32_f103c6_I2C.h"

#define EEPROM_Slave_Address	0x2A  // default Address

void EEPROM_Init(void);
unsigned char EEPROM_Write_Data(uint32_t EEPROM_Address , uint8_t* PTXBuffer , uint8_t DataLen);
unsigned char EEPROM_Read_Data( uint32_t EEPROM_Address , uint8_t* PRXBuffer , uint8_t DataLen);

#endif /* INC_EEPROM_H_ */
