/*
 * Atmega32_Drivers.c
 *
 * Created: 30/08/2022
 * Author : salama mohamed
 */ 

#include "GPIO_Driver.h"
#include "EXTI_Driver.h"
#include "LCD.h"
#include "USART_Driver.h"
#include "SPI_Driver.h"
#include "I2C_Driver.h"
#include "EEPROM.h"
#include "TIMER0_Driver.h"
#include "PWM_Driver.h"
#include "Servo_Motor.h"
#include "HC_05_Bluetooth.h"

uint8_t Data;

void ISR_Bluetooth (void)
{
	Bluetooth_RX_Byte(&Data);	
			if(Data =='1')
			{
				MCAL_GPIO_WritePin(GPIOB , GPIO_PIN_0 , SET) ;			
				Bluetooth_TX_Str("LED_ON#");					
			}
			else if(Data =='2')
			{
				MCAL_GPIO_WritePin(GPIOB , GPIO_PIN_0 , RESET) ;							
				Bluetooth_TX_Str("LED_OFF#"); 				
			}
}

int main(void)
{	
	GPIO_Pinconfig_t GPIO_Conf ;
	GPIO_Conf.pinNumber = GPIO_PIN_0 ;
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	MCAL_GPIO_Init(GPIOB , &GPIO_Conf ) ;
	
	Bluetooth_Init( INT_Enable) ;
	
    while (1) 
    {
		
	}
	return 0;
}

