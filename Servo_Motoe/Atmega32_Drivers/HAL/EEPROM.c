/*
 * EEPROM.c
 *
 * Created: 9/29/2022 12:31:34 AM
 *  Author: salama
 */ 

#include "EEPROM.h"


void EEPROM_Init(void)
{
	I2C_config_t I2C_Config ;
	I2C_Config.IRQ_EN =I2C_IRQ_ENABLE_Disable ;
	I2C_Config.P_IRQ_CALL = NULL ;
	I2C_Config.Speed_MODE = I2C_Speed_MODE_100 ;
	I2C_Config.Prescaler = I2C_Prescaler_1     ;
	MCAL_I2C_Init(&I2C_Config) ;
}


unsigned char EEPROM_Write_Data(uint16_t EEPROM_Address , uint8_t PTXBuffer )
{
	uint8_t i=0;
	uint8_t buffer[3];
	buffer[0] = (uint8_t)(EEPROM_Address>>8);   // Send Upper Byte
	buffer[1] = (uint8_t)(EEPROM_Address);		// Send Lower Byte
	buffer[2]= PTXBuffer;
	MCAL_I2C_Master_TX(EEPROM_Slave_Address_Write, buffer, 3 ,With_Stop);
	return 0;
}


unsigned char EEPROM_Read_Data( uint16_t EEPROM_Address )
{
	uint8_t i=0 , data ;

	uint8_t buffer[2];
	buffer[0] = (uint8_t)(EEPROM_Address>>8);   // Send Upper Byte
	buffer[1] = (uint8_t)(EEPROM_Address);		 // Send Lower Byte
	//send address
	MCAL_I2C_Master_TX(EEPROM_Slave_Address_Write, buffer, 2 , Without_Stop);
	// Read Data
	data=MCAL_I2C_Master_RX( EEPROM_Slave_Address_Read);
	return data;
}