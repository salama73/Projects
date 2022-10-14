/*
 * Atmega32_Drivers.c
 *
 * Created: 30/08/2022 08:00:04 م
 * Author : salama mohamed
 */ 


#include "GPIO_Driver.h"
#include "EXTI_Driver.h"
#include "LCD.h"
#include "USART_Driver.h"
#include "DHT11.h"

uint8_t int_RH,frac_RH,int_Temp,frac_Temp,Check_sum;
char data[10];
int main(void)
{
	LCD_init() ;
	_delay_us(50);
	lcd_Clear();
	LCD_String("Hum  =");
	GOTO_XY(1,0);
	LCD_String("Temp =");
    while (1) 
    {
		Request();					// send Request pulse 
		Response();					// receive response 
		int_RH=Receive_data();		// receive int part from RH 
		frac_RH=Receive_data();		// receive fraction part from RH 
		int_Temp=Receive_data();	// receive int part from RH 
		frac_Temp=Receive_data();	// receive fraction part from RH 
		Check_sum=Receive_data();   // receive  check_sum 
		if ((int_RH + frac_RH + int_Temp + frac_Temp) != Check_sum)
		{
			LCD_String("Error");
			_delay_ms(1000);
			lcd_Clear();
		}
		else
		{
			GOTO_XY(0,8);
			itoa(int_RH,data,10);
			LCD_String(data);
			LCD_String(".");
			itoa(frac_RH,data,11);
			LCD_String(data);
			LCD_String(" %");
			
			GOTO_XY(1,8);
			itoa(int_Temp,data,10);
			LCD_String(data);
			LCD_String(".");
			itoa(frac_Temp,data,10);
			LCD_String(data);
			LCD_String(" C");
		}
    }
}

