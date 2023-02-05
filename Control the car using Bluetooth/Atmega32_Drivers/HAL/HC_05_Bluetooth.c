/*
 * HC_05_Bluetooth.c
 *
 * Created: 15/10/2022
 * Author : Salama Mohammed
 */ 

#include "HC_05_Bluetooth.h"

// Init the usart to act (UART , 9600 BAUDRATE , FULL Duplex , 8 bit data , 1 stop bit , not parity ) to used interrupt set state (INT_Enable) and use function  { void ISR_Bluetooth (void) }
void Bluetooth_Init( enum interrupt State)
{
	static USART_config_t USART_Config ;
	USART_Config.BAUDRATE = USART_BAUDRATE_9600 ;
	USART_Config.Clock_Polarity = USART_Clock_Polarity_Trans_Rising ;
	USART_Config.Communication_MODE =  USART_Communication_MODE_Asynchronous_Normal ;
	if (State==INT_Enable)
	{
		USART_Config.IRQ_EN = USART_IRQ_ENABLE_RX ;
		USART_Config.P_IRQ_CALL = ISR_Bluetooth ;
	}
	else
	{
		USART_Config.IRQ_EN = USART_IRQ_ENABLE_Disable ;
		USART_Config.P_IRQ_CALL = NULL ;
	}
	USART_Config.MODE = USART_MODE_TX_RX ;
	USART_Config.NUM_DATA_BIT = USART_NUM_DATA_BIT_8 ;
	USART_Config.NUM_STOP_BIT = USART_NUM_STOP_BIT_1 ;
	USART_Config.PARITY = USART_PARITY_Disable ;
	MCAL_USART_Init(&USART_Config) ;
}


void Bluetooth_TX_Byte(uint8_t* PTXBuffer) 
{
	MCAL_USART_SendData(PTXBuffer, Enable) ;
}


//to finish the sending process you must send #
void Bluetooth_TX_Str(uint8_t* PTXBuffer) 
{
	MCAL_USART_Send_String(PTXBuffer , Enable);
}


void Bluetooth_RX_Byte(uint8_t* PRXBuffer) 
{
	MCAL_USART_ReceiveData(PRXBuffer,Enable);
}


void Bluetooth_RX_Str(uint8_t* PRXBuffer) 
{
	MCAL_USART_Receive_String(PRXBuffer , Enable) ;
}

