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


void TIMER0_CALL(void)
{
	MCAL_GPIO_TogglePin(GPIOA , GPIO_PIN_0 );
}
int main(void)
{	
	LCD_init();
	uint8_t Data1[] = {0x1,0x2,0x3,0x4};
	uint8_t Data2[4]= {0};

	EEPROM_Init();
	EEPROM_Write_Data(0xAF, Data1, 4);
	_delay_ms(100);
	EEPROM_Read_Data(0xAF, Data2, 4);

    while (1) 
    {
			
    }
}

