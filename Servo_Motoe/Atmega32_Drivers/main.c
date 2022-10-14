/*
 * Atmega32_Drivers.c
 *
 * Created: 30/08/2022
 * Author : salama mohamed
 */ 
//  servo motor
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

int main(void)
{
	Servo_Init();
    while (1) 
    {
		My_Servo(0) ;
		_delay_ms(1500);
		My_Servo(90)  ;
		_delay_ms(1500);
		My_Servo(180)  ;
		_delay_ms(1500);
    }
}

