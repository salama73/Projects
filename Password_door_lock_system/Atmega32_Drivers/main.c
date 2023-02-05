/*
 * Atmega32_Drivers.c
 *
 * Created: 9/11/2022
 * Author : salama mohamed
 */ 

//Password door lock system

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
#include "Keypad.h"
#include "WDT.h"

uint8_t Data1[4] = {0};
uint8_t Data2[4]= {0x1,0x1,0x1,0x1};
uint8_t key_pressed;
uint8_t number_attempts=3 ,Select=1;

void GPIO_INIT(void)
{
	GPIO_Pinconfig_t keypad_Conf ;
	keypad_Conf.GPIO_MODE=GPIO_MODE_OUTPUT;
	keypad_Conf.pinNumber=GPIO_PIN_4;
	MCAL_GPIO_Init(GPIOB,&keypad_Conf);
		
	keypad_Conf.GPIO_MODE=GPIO_MODE_OUTPUT;
	keypad_Conf.pinNumber=GPIO_PIN_5;
	MCAL_GPIO_Init(GPIOB,&keypad_Conf);
}

//Receiving the password from the user using the keypad
void Get_pass(void)
{
	key_pressed=keypad_getkey();
	while(key_pressed=='n')
	{
		key_pressed=keypad_getkey();
	}
	Data1[0]=key_pressed;
	LCD_Character('*');
	key_pressed=keypad_getkey();
	while(key_pressed=='n')
	{
		key_pressed=keypad_getkey();
	}
	Data1[1]=key_pressed;
	LCD_Character('*');
	key_pressed=keypad_getkey();
	while(key_pressed=='n')
	{
		key_pressed=keypad_getkey();
	}
	Data1[2]=key_pressed;
	LCD_Character('*');
	key_pressed=keypad_getkey();
	while(key_pressed=='n')
	{
		key_pressed=keypad_getkey();
	}
	Data1[3]=key_pressed;
	LCD_Character('*');
	lcd_Clear();
}


int main(void)
{
	//initialization GPIO , WDT , EEPROM , I2C , LCD , KEYPAD , SERVO , 
	MCAL_WDT_OFF();
	MCAL_WDT_Init(WDT_Wait_Time_2200ms);
	EEPROM_Init();
	keypad_init();
	LCD_init();
	Servo_Init();
	GPIO_INIT();
	_delay_ms(500);
	//Read the saved password inside the EEPROM
	EEPROM_Read_Data(0x0000, Data2, 4);
	//The function is called when the system is running for the first time to set the password
	if (Data2[0]==0XFF && Data2[1]==0XFF)
	{
		LCD_String("Please enter a  new password");
		_delay_ms(1000);
		lcd_Clear();
		Get_pass();
		EEPROM_Write_Data(0x0000, Data1, 4);
		LCD_String("Welcome");
		_delay_ms(1000);
		lcd_Clear();
	}

    while (1) 
    {
		//Set the number of attempts allowed each time(3)
		number_attempts=3;
		//Read the saved password inside the EEPROM
		EEPROM_Read_Data(0x0000, Data2, 4);
		LCD_String("Please enter a  password");
		_delay_ms(1000);
		lcd_Clear();
		Get_pass();
		//Compare the user password with the one stored before 
		while(number_attempts)
		{
			//When a valid password is entered, the number_attempts is set to zero and the programs are completed
			if (Data2[0]==Data1[0] && Data2[1]==Data1[1] && Data2[2]==Data1[2] && Data2[3]==Data1[3])
			{
				LCD_String("correct");
				_delay_ms(1000);
				lcd_Clear();
				number_attempts=0;
			}
			//When an incorrect password is entered (3 times), the number_attempts is set to zero and WDT is activated to reboot the system after 2200 microseconds
			else
			{
				number_attempts--;
				LCD_String("incorrect");
				_delay_ms(1000);
				lcd_Clear();
				if (number_attempts==0)
				{
					MCAL_WDT_ON();
					MCAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
					LCD_String("please wait");
					_delay_ms(2100);
					lcd_Clear();
					_delay_ms(500);
				}
				LCD_String("Please enter a password");
				_delay_ms(1000);
				lcd_Clear();
				Get_pass();
			}
		}
		//This LOOP can only be accessed when a valid password is entered
		do
		{
			//You can continue inside the system or change the current password
			LCD_String("1:change the password");
			GOTO_XY(1,0);
			LCD_String("2:continue");
			Select=keypad_getkey();
			while(Select=='n')
			{
				Select=keypad_getkey();
			}
			lcd_Clear();
			if (Select==1)
			{
				lcd_Clear();
				_delay_ms(100);
				LCD_String("Please enter a  new password");
				_delay_ms(500);
				lcd_Clear();
				Get_pass();
				EEPROM_Write_Data(0x00, Data1, 4);
				Select=0;
			}
		} while (Select=='n');
		//When you enter the correct password, the SERVO will be moved at an angle of 90 degrees for 3 seconds
		My_Servo(90) ;
		MCAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET);
		_delay_ms(3000);
		MCAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET);
		My_Servo(0) ;
		
    }
}

