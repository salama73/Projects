/*
 * LCD.h
 *
 * Created: 24/08/2022 07:58:37 م
*  Author: salama mohamed
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "GPIO_Driver.h"


#define lcd_Data_Direction                      GPIOA
#define lcd_control_Direction                   GPIOB
#define lcd_Data_Port                           GPIOA
#define lcd_control_Port                        GPIOB
#define en                                      GPIO_PIN_2
#define rs                                      GPIO_PIN_1
#define RW                                      GPIO_PIN_3
#define beginning_of_the_first_line             0X80                   
#define Activate_second_line                    0X3C                 
#define beginning_of_second_line                0XC0                     //Force cursor to beginning of second line
#define Jump_to_second_line                     0XC1                    //Jump to second line position1 
#define Clear_Display                           0X01                   //Clear Display (also clear DDRAM content)
#define _1L_8b                                  0X30                  //Function Set: 8-bit, 1 Line, 5x7 Dots 
#define _2L_8b                                  0X38                 //Function Set: 8-bit, 2 Line, 5x7 Dots 
#define _1L_4b                                  0X20                //Function Set: 4-bit, 1 Line, 5x7 Dots
#define _2L_4b                                  0X28               //Function Set: 4-bit, 2 Line, 5x7 Dots
#define Entry_Mode                              0X06              //take cursor to next position "shift cursor to right"
#define Display_off_Cursor_off                  0X08             //(clearing display without clearing DDRAM content)
#define Display_on_Cursor_on                    0x0E
#define Display_on_Cursor_off                   0x0C
#define Display_on_Cursor_blinking              0x0F
#define Shift_entire_display_left               0x18
#define Shift_entire_display_right              0x1C
#define Move_cursor_left_by_one_character       0x10
#define Move_cursor_right_by_one_character      0x14

//Configure The LCD to send Addresses
void LCD_cmd( unsigned char cmd );
//Used To Send a Single Character
void LCD_Character( unsigned char character );
//Used To Send a Single number
void LCD_Character( unsigned char character );
//Used To Send a Single Character
void LCD_String (char *string);
//clear LCD
void lcd_Clear(void);
//Initializing 16x2 LCD with 4 bit mode
void LCD_init(void);
//position of write
void GOTO_XY(unsigned char line , unsigned char posision);
//LCD_check_busy 
void LCD_check_busy (void);
#endif /* LCD_H_ */