/*
 * LCD.c
 *
 * Created: 24/08/2022 07:58:21 م
*  Author: salama mohamed
 */ 

#include "LCD.h"

#define _4_bit_mode

void LCD_init(void)
{
	GPIO_Pinconfig_t config ;
		
	// set port lcd_data as output
	config.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	config.pinNumber = GPIO_PIN_0 ;
	MCAL_GPIO_Init( lcd_Data_Direction , & config ) ;
		
	config.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	config.pinNumber = GPIO_PIN_1 ;
	MCAL_GPIO_Init( lcd_Data_Direction , & config ) ;
				
	config.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	config.pinNumber = GPIO_PIN_2 ;
	MCAL_GPIO_Init( lcd_Data_Direction , & config ) ;
						
	config.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	config.pinNumber = GPIO_PIN_3 ;
	MCAL_GPIO_Init( lcd_Data_Direction , & config ) ;
								
	config.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	config.pinNumber = GPIO_PIN_4 ;
	MCAL_GPIO_Init( lcd_Data_Direction , & config ) ;
										
	config.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	config.pinNumber = GPIO_PIN_5 ;
	MCAL_GPIO_Init( lcd_Data_Direction , & config ) ;
												
	config.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	config.pinNumber = GPIO_PIN_6 ;
	MCAL_GPIO_Init( lcd_Data_Direction , & config ) ;
														
	config.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	config.pinNumber = GPIO_PIN_7 ;
	MCAL_GPIO_Init( lcd_Data_Direction , & config ) ;
	
	// set en rs rw as outpit
	config.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	config.pinNumber = en ;
	MCAL_GPIO_Init( lcd_control_Direction , & config ) ;
	
	config.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	config.pinNumber = rs ;
	MCAL_GPIO_Init( lcd_control_Direction , & config ) ;
	
	config.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	config.pinNumber = RW ;
	MCAL_GPIO_Init( lcd_control_Direction , & config ) ;
		
	_delay_ms(20);
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
	LCD_cmd(Display_on_Cursor_off);              // Display on cursor off
	LCD_cmd(Clear_Display);                    // Clear display screen
	_delay_ms(2);
#endif
}

void LCD_cmd( unsigned char cmd )
{
#ifdef _8_bit_mode
	MCAL_GPIO_WritePort( lcd_Data_Port , cmd ) ;			           // send command       
	MCAL_GPIO_WritePin( lcd_control_Port , rs , GPIO_PIN_RESET ) ;    // RS =0 Select commend register  
	MCAL_GPIO_WritePin( lcd_control_Port , RW , GPIO_PIN_RESET ) ;   // R/W=0 i.e MODE Write  
	MCAL_GPIO_WritePin( lcd_control_Port , en , GPIO_PIN_SET )   ;    
	_delay_us(1);       
	MCAL_GPIO_WritePin( lcd_control_Port , en , GPIO_PIN_RESET ) ;               
	_delay_us(200);
#endif
#ifdef _4_bit_mode
	MCAL_GPIO_WritePort(lcd_Data_Port, (cmd & 0XF0));
	MCAL_GPIO_WritePin(lcd_control_Port,rs,GPIO_PIN_RESET);            // rs=0 i.e select command reg
	MCAL_GPIO_WritePin(lcd_control_Port,RW,GPIO_PIN_RESET);					 // R/W=0 i.e MODE Write
	MCAL_GPIO_WritePin(lcd_control_Port,en,GPIO_PIN_SET);					// give high pulse to enable pin
	_delay_us(1);
	MCAL_GPIO_WritePin(lcd_control_Port,en,GPIO_PIN_RESET);				 // give low pulse to enable pin
	_delay_us(200);
	MCAL_GPIO_WritePort(lcd_Data_Port, ( cmd & 0X0F) << 4);               //sending lower nibble of 8 bit 
	MCAL_GPIO_WritePin(lcd_control_Port,rs,GPIO_PIN_RESET);            // rs=0 i.e select command reg
	MCAL_GPIO_WritePin(lcd_control_Port,RW,GPIO_PIN_RESET);					 // R/W=0 i.e MODE Write
	MCAL_GPIO_WritePin(lcd_control_Port,en,GPIO_PIN_SET);					// give high pulse to enable pin
	_delay_us(1);
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
	MCAL_GPIO_WritePort( lcd_Data_Port , character ) ;			           // send character
	MCAL_GPIO_WritePin( lcd_control_Port , rs , GPIO_PIN_SET ) ;    // RS =0 Select DATA register
	MCAL_GPIO_WritePin( lcd_control_Port , RW , GPIO_PIN_RESET ) ;   // R/W=0 i.e MODE Write
	MCAL_GPIO_WritePin( lcd_control_Port , en , GPIO_PIN_SET )   ;
	_delay_us(1);
	MCAL_GPIO_WritePin( lcd_control_Port , en , GPIO_PIN_RESET ) ;
	_delay_ms(2);
#endif
#ifdef _4_bit_mode
	MCAL_GPIO_WritePort(lcd_Data_Port, (character & 0XF0));
	MCAL_GPIO_WritePin(lcd_control_Port,rs,GPIO_PIN_SET);            // rs=0 i.e select DATA reg
	MCAL_GPIO_WritePin(lcd_control_Port,RW,GPIO_PIN_RESET);					 // R/W=0 i.e MODE Write
	MCAL_GPIO_WritePin(lcd_control_Port,en,GPIO_PIN_SET);					// give high pulse to enable pin
	_delay_us(1);
	MCAL_GPIO_WritePin(lcd_control_Port,en,GPIO_PIN_RESET);				 // give low pulse to enable pin
	_delay_us(200);
	MCAL_GPIO_WritePort(lcd_Data_Port, ( character & 0X0F) << 4);               //sending lower nibble of 8 bit i.e 1byte
	MCAL_GPIO_WritePin(lcd_control_Port,rs,GPIO_PIN_SET);            // rs=0 i.e select DATA reg
	MCAL_GPIO_WritePin(lcd_control_Port,RW,GPIO_PIN_RESET);					 // R/W=0 i.e MODE Write
	MCAL_GPIO_WritePin(lcd_control_Port,en,GPIO_PIN_SET);					// give high pulse to enable pin
	_delay_us(1);
	MCAL_GPIO_WritePin(lcd_control_Port,en,GPIO_PIN_RESET);				 // give low pulse to enable pin
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