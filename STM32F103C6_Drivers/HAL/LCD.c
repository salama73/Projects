/*
 * LCD.c
 *
 * Created: 24/08/2022 07:58:21 م
 *  Author: elmnshawy
 */ 

#include "LCD.h"

//#define _4_bit_mode
#define _8_bit_mode


void _delay_ms(int x)
{
	uint32_t i,j;
	for(i=0;i<=x;i++)
		for(j=0;j<255;j++);
}

void LCD_init(void)
{
	GPIO_Pinconfig_t pincfg_LCD;
	// lcd_Data_Direction-->>Output
	pincfg_LCD.pinNumber=GPIO_PIN_0;
	//PORTA Pin0 as output_pull_push
	pincfg_LCD.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	//PORTA Pin0 at 10 MHZ
	pincfg_LCD.GPIO_OUTPUT_Speed=GPIO_speed_10M;
	//init pin
	MCAL_GPIO_Init(GPIOA,&pincfg_LCD);

	pincfg_LCD.pinNumber=GPIO_PIN_1;
	//PORTA Pin1 as output_pull_push
	pincfg_LCD.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	//PORTA Pin1 at 10 MHZ
	pincfg_LCD.GPIO_OUTPUT_Speed=GPIO_speed_10M;
	//init pin
	MCAL_GPIO_Init(GPIOA,&pincfg_LCD);

	pincfg_LCD.pinNumber=GPIO_PIN_2;
	//PORTA Pin2 as output_pull_push
	pincfg_LCD.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	//PORTA Pin2 at 10 MHZ
	pincfg_LCD.GPIO_OUTPUT_Speed=GPIO_speed_10M;
	//init pin
	MCAL_GPIO_Init(GPIOA,&pincfg_LCD);

	pincfg_LCD.pinNumber=GPIO_PIN_3;
	//PORTA Pin3 as output_pull_push
	pincfg_LCD.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	//PORTA Pin3 at 10 MHZ
	pincfg_LCD.GPIO_OUTPUT_Speed=GPIO_speed_10M;
	//init pin
	MCAL_GPIO_Init(GPIOA,&pincfg_LCD);

	pincfg_LCD.pinNumber=GPIO_PIN_4;
	//PORTA Pin4 as output_pull_push
	pincfg_LCD.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	//PORTA Pin4 at 10 MHZ
	pincfg_LCD.GPIO_OUTPUT_Speed=GPIO_speed_10M;
	//init pin
	MCAL_GPIO_Init(GPIOA,&pincfg_LCD);

	pincfg_LCD.pinNumber=GPIO_PIN_5;
	//PORTA Pin5 as output_pull_push
	pincfg_LCD.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	//PORTA Pin5 at 10 MHZ
	pincfg_LCD.GPIO_OUTPUT_Speed=GPIO_speed_10M;
	//init pin
	MCAL_GPIO_Init(GPIOA,&pincfg_LCD);

	pincfg_LCD.pinNumber=GPIO_PIN_6;
	//PORTA Pin6 as output_pull_push
	pincfg_LCD.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	//PORTA Pin6 at 10 MHZ
	pincfg_LCD.GPIO_OUTPUT_Speed=GPIO_speed_10M;
	//init pin
	MCAL_GPIO_Init(GPIOA,&pincfg_LCD);

	pincfg_LCD.pinNumber=GPIO_PIN_7;
	//PORTA Pin7 as output_pull_push
	pincfg_LCD.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	//PORTA Pin7 at 10 MHZ
	pincfg_LCD.GPIO_OUTPUT_Speed=GPIO_speed_10M;
	//init pin
	MCAL_GPIO_Init(GPIOA,&pincfg_LCD);

	pincfg_LCD.pinNumber=rs;
	//PORTB Pin1 as output_pull_push
	pincfg_LCD.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	//PORTB Pin1 at 10 MHZ
	pincfg_LCD.GPIO_OUTPUT_Speed=GPIO_speed_10M;
	//init pin
	MCAL_GPIO_Init(lcd_control_Direction,&pincfg_LCD);

	pincfg_LCD.pinNumber=RW;
	//PORTB Pin2 as output_pull_push
	pincfg_LCD.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	//PORTB Pin2 at 10 MHZ
	pincfg_LCD.GPIO_OUTPUT_Speed=GPIO_speed_10M;
	//init pin
	MCAL_GPIO_Init(lcd_control_Direction,&pincfg_LCD);

	pincfg_LCD.pinNumber=en;
	//PORTB Pin3 as output_pull_push
	pincfg_LCD.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	//PORTB Pin3 at 10 MHZ
	pincfg_LCD.GPIO_OUTPUT_Speed=GPIO_speed_10M;
	//init pin
	MCAL_GPIO_Init(lcd_control_Direction,&pincfg_LCD);
	_delay_ms(2);

#ifdef _8_bit_mode
	LCD_cmd(_2L_8b);                              // 2 line 5*7 matrix in 4-bit mode
	LCD_cmd(Display_on_Cursor_off);              // Display on cursor off
	LCD_cmd(Entry_Mode);                        // take cursor to next position "shift cursor to right"
	LCD_cmd(Clear_Display);                    // Clear display screen
	_delay_ms(2);
#endif
#ifdef _4_bit_mode
	LCD_cmd(0x02);                // send for 4 bit initialization of LCD "shift cursor to left"
	LCD_cmd(_2L_4b);                              // 2 line 5*7 matrix in 4-bit mode
	LCD_cmd(Entry_Mode);                        // take cursor to next position "shift cursor to right"
	LCD_cmd(beginning_of_the_first_line);
	LCD_cmd(Display_on_Cursor_blinking);              // Display on cursor off
	LCD_cmd(Clear_Display);                    // Clear display screen
	_delay_ms(2);
#endif
}

void LCD_cmd( unsigned char cmd )
{
#ifdef _8_bit_mode
	MCAL_GPIO_WritePort(lcd_Data_Port, cmd);                                 // send command
	MCAL_GPIO_WritePin(lcd_control_Port,rs,GPIO_PIN_RESET);					// rs=0 i.e select command reg
	MCAL_GPIO_WritePin(lcd_control_Port,RW,GPIO_PIN_RESET);				   // R/W=0 i.e MODE Write
	MCAL_GPIO_WritePin(lcd_control_Port,en,GPIO_PIN_SET);				  // give high pulse to enable pin
	_delay_ms(30);
	MCAL_GPIO_WritePin(lcd_control_Port,en,GPIO_PIN_RESET);				 // give low pulse to enable pin
	_delay_ms(2);
#endif
#ifdef _4_bit_mode
	MCAL_GPIO_WritePort(lcd_Data_Port, (cmd & 0XF0));
	MCAL_GPIO_WritePin(lcd_control_Port,rs,GPIO_PIN_RESET);            // rs=0 i.e select command reg
	MCAL_GPIO_WritePin(lcd_control_Port,RW,GPIO_PIN_RESET);					 // R/W=0 i.e MODE Write
	MCAL_GPIO_WritePin(lcd_control_Port,en,GPIO_PIN_SET);					// give high pulse to enable pin
	_delay_ms(10);
	MCAL_GPIO_WritePin(lcd_control_Port,en,GPIO_PIN_RESET);				 // give low pulse to enable pin
	_delay_ms(2);
	MCAL_GPIO_WritePort(lcd_Data_Port, ( cmd & 0X0F) << 4);               //sending lower nibble of 8 bit i.e 1byte
	MCAL_GPIO_WritePin(lcd_control_Port,rs,GPIO_PIN_RESET);            // rs=0 i.e select command reg
	MCAL_GPIO_WritePin(lcd_control_Port,RW,GPIO_PIN_RESET);					 // R/W=0 i.e MODE Write
	MCAL_GPIO_WritePin(lcd_control_Port,en,GPIO_PIN_SET);					// give high pulse to enable pin
	_delay_ms(10);
	MCAL_GPIO_WritePin(lcd_control_Port,en,GPIO_PIN_RESET);				 // give low pulse to enable pin
	_delay_ms(2);
#endif
}

void lcd_Clear()
{
	LCD_cmd (0x01);                   // send hex 01 to Clear display
	_delay_ms(2);
	LCD_cmd(0x80);                   // send hex 80 to Force Cursor to beginning of 1st line
}

void GOTO_XY(unsigned char line , unsigned char posision)
{
	if (line==0)
	{
		if(posision>=0 && posision<16)
			LCD_cmd(0X80+posision);
	}
	else if (line==1)
	{
		if(posision>=0 && posision<16)
			LCD_cmd(0XC0+posision);
	}
}

void LCD_Character( unsigned char character )
{
#ifdef _8_bit_mode
	MCAL_GPIO_WritePort(lcd_Data_Port, character);                           // send command
	MCAL_GPIO_WritePin(lcd_control_Port,rs,GPIO_PIN_SET);					//  set rs to select data register
	MCAL_GPIO_WritePin(lcd_control_Port,RW,GPIO_PIN_RESET);				   // R/W=0 i.e MODE Write
	MCAL_GPIO_WritePin(lcd_control_Port,en,GPIO_PIN_SET);				  // give high pulse to enable pin
	_delay_ms(30);
	MCAL_GPIO_WritePin(lcd_control_Port,en,GPIO_PIN_RESET);				 // give low pulse to enable pin
	_delay_ms(2);
#endif
#ifdef _4_bit_mode
	MCAL_GPIO_WritePort(lcd_Data_Port, (character & 0XF0));
	MCAL_GPIO_WritePin(lcd_control_Port,rs,GPIO_PIN_SET);           		  //  set rs to select data register
	MCAL_GPIO_WritePin(lcd_control_Port,RW,GPIO_PIN_RESET);			  	    // R/W=0 i.e MODE Write
	MCAL_GPIO_WritePin(lcd_control_Port,en,GPIO_PIN_SET);			       // give high pulse to enable pin
	_delay_ms(10);
	MCAL_GPIO_WritePin(lcd_control_Port,en,GPIO_PIN_RESET);				 // give low pulse to enable pin
	_delay_ms(2);

	MCAL_GPIO_WritePort(lcd_Data_Port, (character & 0X0F) << 4);             //sending lower nibble of 8 bit i.e 1byte
	MCAL_GPIO_WritePin(lcd_control_Port,rs,GPIO_PIN_SET);           		  //  set rs to select data register
	MCAL_GPIO_WritePin(lcd_control_Port,RW,GPIO_PIN_RESET);			  	    // R/W=0 i.e MODE Write
	MCAL_GPIO_WritePin(lcd_control_Port,en,GPIO_PIN_SET);			   // give high pulse to enable pin
	_delay_ms(10);
	MCAL_GPIO_WritePin(lcd_control_Port,en,GPIO_PIN_RESET);			 // give low pulse to enable pin
	_delay_ms(2);
#endif
}

void LCD_String (char *string)
{
	int count=0;
	while(*string)
	{
		count++;
		LCD_Character(*string++);
		if (count==16)
		{
			GOTO_XY(1,0);
		}
		else if(count==32)
		{
			_delay_ms(500);
			lcd_Clear();
			GOTO_XY(0,0);
			count=0;
		}
	}
}
