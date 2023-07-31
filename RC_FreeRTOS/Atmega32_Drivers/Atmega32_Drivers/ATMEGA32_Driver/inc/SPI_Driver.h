﻿/*
 * SPI_Driver.h
 *
 * Created: 13/09/2022
 *  Author: Salama Mohamed
 */ 


#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

//Include
#include "Atmega32.h"
#include "GPIO_Driver.h"

//============================================================

//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
	uint8_t MODE 			 	; 			//specified the SPI (Master / slave) to be configured .
											//this parameter must be set based on  @ ref  SPI_MODE_Define

	uint8_t BaudRate_Prescalers;	 		//specified the baudrate prescalers .
											//this parameter must be set based on  @ ref  SPI_BaudRate_Prescalers_Define

	uint8_t Speed_Communication;			//specified the Speed_Communication	  .
											//this parameter must be set based on  @ ref  SPI_Speed_Communication_Define

	uint8_t Polarity			;			//specified the Polarity  .
											//this parameter must be set based on  @ ref  SPI_Polarity_Define

	uint8_t Phase	   			;			//specified the Phase.
											//this parameter must be set based on  @ ref  SPI_Phase_Define

	uint8_t Data_Order	   		;			//specified the Programmable data order with MSB-first or LSB-first shifting .
											//this parameter must be set based on  @ ref  SPI_Data_Order_Define

	uint8_t IRQ_EN				;			//specified the interrupt (disable or enable )  .
											//this parameter must be set based on  @ ref  SPI_IRQ_ENABLE_Define

	void (*P_IRQ_CALL)()		;     		// set the function which will be call at IRQ happen

}SPI_config_t;

enum SPI_polling_mechanism
{
	Enabled ,
	Disabled
};

//=========================================================================

//-----------------------------
//Macros Configuration References
//-----------------------------

/*
This bit selects Master SPI mode when written to one, and Slave SPI mode when written
logic zero. If SS is configured as an input and is driven low while MSTR is set, MSTR will
be cleared, and SPIF in SPSR will become set. The user will then have to set MSTR to
re-enable SPI Master mode.
*/
// @ ref  SPI_MODE_Define
#define SPI_MODE_Master										(1<<4)
#define SPI_MODE_Slave										~(1<<4)

//@ ref  SPI_BaudRate_Prescalers_Define
/*
Bits 5:3 BR[2:0]: Baud rate control
00: fPCLK/4
01: fPCLK/16
10: fPCLK/64
11: fPCLK/128
 */
#define SPI_BaudRate_Prescalers_4							(uint8_t)(~(3<<0))
#define SPI_BaudRate_Prescalers_16							(uint8_t)(1<<0)
#define SPI_BaudRate_Prescalers_64							(uint8_t)(2<<0)
#define SPI_BaudRate_Prescalers_128							(uint8_t)(3<<0)

//@ ref  SPI_Speed_Communication_Define
#define SPI_Speed_Communication_Normal						(uint8_t)(~(1<<0))
#define SPI_Speed_Communication_Double_Speed				(uint8_t)(1<<0)

// @ ref  SPI_Polarity_Define
#define SPI_Polarity_Low_level_idle_state					(uint8_t)(~(1<<3))
#define SPI_Polarity_High_level_idle_state					(uint8_t)(1<<3)

//@ ref  SPI_Phase_Define
#define SPI_Phase_Data_Latched_On_Second_Clock				(uint8_t)(1<<2)
#define SPI_Phase_Data_Latched_On_First_Clock				(uint8_t)(~(1<<2))

//@ ref  SPI_Data_Order_Define
#define SPI_Data_Order_MSB_Transmitted_First				(uint8_t)(~(1<<5))
#define SPI_Data_Order_LSB_Transmitted_First				(uint8_t)(1<<5)

//@ ref  SPI_IRQ_ENABLE_Define
#define SPI_IRQ_ENABLE_Enable								(uint8_t)(1<<7)
#define SPI_IRQ_ENABLE_Disable								(uint8_t)(~(1<<7))

#define SPI_Enable()										(uint8_t)(1<<6)
#define SPI_Disable()										(uint8_t)(~(1<<6))
//============================================================================

/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/
void MCAL_SPI_Init(  SPI_config_t* USART_Config );
void MCAL_SPI_DeInit( void );
void MCAL_SPI_Set_Master_Pin( void );
void MCAL_SPI_ReceiveData( uint8_t* PRXBuffer , enum SPI_polling_mechanism polling_EN);
void MCAL_SPI_SendData( uint8_t* PTXBuffer , enum SPI_polling_mechanism polling_EN);
void MCAL_SPI_Receive_Send_Data( uint8_t* PRXBuffer , enum SPI_polling_mechanism polling_EN);
void MCAL_SPI_Set_Slave_Pin( void );
//===============================================================================


#endif /* SPI_DRIVER_H_ */