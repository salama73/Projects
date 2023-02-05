/*********************************************************************************
 * Control the car using Bluetooth.c
 * Created: 1/02/2023
 * Author : Salama Mohammed
 ********************************************************************************/

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

unsigned char Data;
unsigned char DATA;

void ISR_Bluetooth (void)
{
	Bluetooth_RX_Byte(&Data);
	if(Data =='B')
	{
		lcd_Clear();
		LCD_String("BACK");
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_4 , SET) ;
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_5 , RESET) ;
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_6 , SET) ;
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_7 , RESET) ;
	}
	else if(Data =='F')
	{
		lcd_Clear();
		LCD_String("FORWARD");
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_4 , RESET) ;
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_5 , SET) ;
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_6 , RESET) ;
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_7 , SET) ;
	}
	else if(Data =='R')
	{
		lcd_Clear();
		LCD_String("RIGHT");
		MOTOR_Speed(1);
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_4 , SET) ;
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_5 , RESET) ;
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_6 , RESET) ;
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_7 , SET) ;
	}
	else if(Data =='L')
	{
		lcd_Clear();
		LCD_String("LEFT");
		MOTOR_Speed(1);
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_4 , RESET) ;
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_5 , SET) ;
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_6 , SET) ;
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_7 , RESET) ;
	}
	else if(Data =='S')
	{
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_4 , RESET) ;
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_5 , RESET) ;
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_6 , RESET) ;
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_7 , RESET) ;
	}
	else if(Data =='X')
	{
		DATA=20;
		while(DATA)
		{
			MCAL_GPIO_TogglePin(GPIOB , GPIO_PIN_0 ) ;
			_delay_ms(100);
			DATA--;
		}
	}
	else if(Data =='V')
	{
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_3 , SET) ;
	}
	else if(Data =='v')
	{
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_3 , RESET) ;
	}
	else if(Data =='W')
	{
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_1 , SET) ;
	}
	else if(Data =='w')
	{
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_1 , RESET) ;
	}
	else if(Data =='U')
	{
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_2 , SET) ;
	}
	else if(Data =='u')
	{
		MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_2 , RESET) ;
	}
	else
	{
		if(Data=='0')
		{
			lcd_Clear();
			LCD_String("STOB");
			MOTOR_Speed(0);
			SEG_Display(0);
		}
		else if(Data=='1')
		{
			MOTOR_Speed(1);
			SEG_Display(1);
		}
		else if(Data=='2')
		{
			MOTOR_Speed(2);
			SEG_Display(2);
		}
		else if(Data=='3')
		{
			MOTOR_Speed(3);
			SEG_Display(3);
		}
		else if(Data=='4')
		{
			MOTOR_Speed(4);
			SEG_Display(4);
		}
		else if(Data=='5')
		{
			MOTOR_Speed(5);
			SEG_Display(5);
		}
	}
}



int main(void)
{
	GPIO_Pinconfig_t GPIO_Conf ;
	GPIO_Conf.pinNumber = GPIO_PIN_0 ;
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	MCAL_GPIO_Init(GPIOB , &GPIO_Conf ) ;
	
	GPIO_Conf.pinNumber = GPIO_PIN_1 ;
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	MCAL_GPIO_Init(GPIOC , &GPIO_Conf ) ;
	
	GPIO_Conf.pinNumber = GPIO_PIN_2 ;
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	MCAL_GPIO_Init(GPIOC , &GPIO_Conf ) ;		
	
	GPIO_Conf.pinNumber = GPIO_PIN_3 ;
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	MCAL_GPIO_Init(GPIOC , &GPIO_Conf ) ;	
	
	GPIO_Conf.pinNumber = GPIO_PIN_4 ;
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	MCAL_GPIO_Init(GPIOC , &GPIO_Conf ) ;
	
	GPIO_Conf.pinNumber = GPIO_PIN_5 ;
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	MCAL_GPIO_Init(GPIOC , &GPIO_Conf ) ;
	
	GPIO_Conf.pinNumber = GPIO_PIN_6 ;
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	MCAL_GPIO_Init(GPIOC , &GPIO_Conf ) ;
		
	GPIO_Conf.pinNumber = GPIO_PIN_7 ;
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	MCAL_GPIO_Init(GPIOC , &GPIO_Conf ) ;
	

	SEG_Init();
	MOTOR_Init();
	MOTOR_Speed(1);
	Bluetooth_Init( INT_Enable) ;
	LCD_init();
	
	while (1)
	{

	}
	return 0;
}
