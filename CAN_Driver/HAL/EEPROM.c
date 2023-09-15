/*
 * EEPROM.c
 *
 *  Created on: Sep 21, 2022
 *      Author: salama
 */

#include "EEPROM.h"

void EEPROM_Init(void)
{
	I2C_config_t I2C_Config;
	I2C_Config.ACK_Control=I2C_ACK_Control_Enable ;
	I2C_Config.IRQ_EN =I2C_IRQ_ENABLE_Disable ;
	I2C_Config.NUM_Address_BIT=I2C_NUM_Address_BIT_7 ;
	I2C_Config.MODE_Speed=I2C_Speed_MODE_SM_100;
	MCAL_I2C_GPIO_Set_Pins(I2C1);
	MCAL_I2C_Init(I2C1, &I2C_Config);
}


unsigned char EEPROM_Write_Data(uint32_t EEPROM_Address , uint8_t* PTXBuffer , uint8_t DataLen)
{
	uint8_t i=0;
	uint8_t buffer[256];
	buffer[0] = (uint8_t)(EEPROM_Address>>8);   // Send Upper Byte
	buffer[1] = (uint8_t)(EEPROM_Address);		// Send Lower Byte

	for( i =2 ; i<(DataLen+2) ; i++)
	{
		buffer[i]= PTXBuffer[i-2];
	}

	MCAL_I2C_Master_TX(I2C1, EEPROM_Slave_Address, buffer, (DataLen+2), WithStop, Start);

	return 0;
}

unsigned char EEPROM_Read_Data( uint32_t EEPROM_Address , uint8_t* PRXBuffer , uint8_t DataLen)
{
	uint8_t buffer[2];
	buffer[0] = (uint8_t)(EEPROM_Address>>8);   // Send Upper Byte
	buffer[1] = (uint8_t)(EEPROM_Address);		 // Send Lower Byte
	//send address
	MCAL_I2C_Master_TX(I2C1, EEPROM_Slave_Address, buffer, 2, WithoutStop, Start);
	// Read Data
	MCAL_I2C_Master_RX(I2C1, EEPROM_Slave_Address, PRXBuffer, DataLen, WithStop, RepeatedSart);

	return 0;
}
