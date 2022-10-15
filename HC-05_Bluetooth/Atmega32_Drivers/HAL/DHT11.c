/*
 * DHT11.c
 *
 * Created: 08/09/2022 02:13:54 ص
 *  Author: elmnshawy
 */ 

#include "DHT11.h"

uint8_t buffer=0;
GPIO_Pinconfig_t pinconfig ;

void Request()				//  send start pulse to request
{
	//Set pit output
	pinconfig.pinNumber = DHT11_Pin ;
	pinconfig.GPIO_MODE = GPIO_MODE_OUTPUT ;
	MCAL_GPIO_Init( GPIOD , &pinconfig ) ;
	// set pit how level
	MCAL_GPIO_WritePin(GPIOD,DHT11_Pin,GPIO_PIN_RESET);
	_delay_ms(20);
	// set pit high level 
	MCAL_GPIO_WritePin(GPIOD,DHT11_Pin,GPIO_PIN_SET);
}
void Response()				// receive response from DHT11 to MCU
{
	//Set pit input
	pinconfig.pinNumber = DHT11_Pin ;
	pinconfig.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
	MCAL_GPIO_Init( GPIOD , &pinconfig ) ;
	
	while( MCAL_GPIO_ReadPin(GPIOD,DHT11_Pin)); // wait to pin input zero ( this is start low level Response )
	while( MCAL_GPIO_ReadPin(GPIOD,DHT11_Pin)==GPIO_PIN_RESET); // wait to pin input One ( this is start high level Response )
	while( MCAL_GPIO_ReadPin(GPIOD,DHT11_Pin)); // wait to end response signal
}
uint8_t Receive_data() 	// receive data
{
	uint8_t i ;
	for ( i=0 ;i<8 ; i++)
	{
		// check bit 0 or 1 (if pulse is <30 us input is low (0) )
		while( MCAL_GPIO_ReadPin(GPIOD,DHT11_Pin)==GPIO_PIN_RESET); //wait to input is high 
		_delay_us(30);
		// read pi if high this input is 1 
		if( MCAL_GPIO_ReadPin(GPIOD,DHT11_Pin))
		{
			buffer = (buffer<<1)|(0x01) ; // 1
		}
		else
		{
			buffer = (buffer<<1) ;
		}
		while( MCAL_GPIO_ReadPin(GPIOD,DHT11_Pin));// wait until end signal
	}
	return buffer ;
}