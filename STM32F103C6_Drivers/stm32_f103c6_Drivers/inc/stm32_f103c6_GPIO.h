/*
 * stm32_f103c6_GPIO.h
 *
 *  Created on: Aug 26, 2022
 *      Author: Salama Mohamed
 */

#ifndef INC_STM32_F103C6_GPIO_H_
#define INC_STM32_F103C6_GPIO_H_

//Include
#include "stm32f103x6.h"




//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
	uint16_t pinNumber 			 ; //specified the GPIO pin to be configured .
					     	 	  //this parameter must be set based on  @ ref  GPIO_PINS_Define

	uint8_t GPIO_MODE			;//specified the operating  for the select pin .
								//this parameter must be set based on  @ ref  GPIO_MODE_Define

	uint8_t GPIO_OUTPUT_Speed	;//specified the speed  for the select pin .
								//this parameter must be set based on  @ ref  GPIO_speed_Define

}GPIO_Pinconfig_t;


//=========================================================================
//-----------------------------
//Macros Configuration References
//-----------------------------

//@ ref  GPIO_PINS_Define

#define GPIO_PIN_0			((uint16_t)0X0001)
#define GPIO_PIN_1			((uint16_t)0X0002)
#define GPIO_PIN_2			((uint16_t)0X0004)
#define GPIO_PIN_3			((uint16_t)0X0008)
#define GPIO_PIN_4			((uint16_t)0X0010)
#define GPIO_PIN_5			((uint16_t)0X0020)
#define GPIO_PIN_6			((uint16_t)0X0040)
#define GPIO_PIN_7			((uint16_t)0X0080)
#define GPIO_PIN_8			((uint16_t)0X0100)
#define GPIO_PIN_9			((uint16_t)0X0200)
#define GPIO_PIN_10			((uint16_t)0X0400)
#define GPIO_PIN_11			((uint16_t)0X0800)
#define GPIO_PIN_12			((uint16_t)0X1000)
#define GPIO_PIN_13			((uint16_t)0X2000)
#define GPIO_PIN_14			((uint16_t)0X4000)
#define GPIO_PIN_15			((uint16_t)0X8000)
#define GPIO_PIN_ALL		((uint16_t)0XFFFF)
#define GPIO_PIN_MASK		0X0000FFFF


//@ ref  GPIO_MODE_Define

//0: Analog mode
//1: Floating input (reset state)
//2: Input with pull-up
//3: pull-down
//4: General purpose output push-pull
//5: General purpose output Open-drain
//6: Alternate function output Push-pull
//7: Alternate function output Open-drain
//8: Alternate function input

#define GPIO_MODE_Analog			0
#define GPIO_MODE_INPUT_FLO			1
#define GPIO_MODE_INPUT_PU			2
#define GPIO_MODE_INPUT_PD			3
#define GPIO_MODE_OUTPUT_PP			4
#define GPIO_MODE_OUTPUT_OD			5
#define GPIO_MODE_OUTPUT_AF_PP		6
#define GPIO_MODE_OUTPUT_AF_OD		7
#define GPIO_MODE_INPUT_AF			8

//@ ref  GPIO_speed_Define
//1: Output mode, max speed 10 MHz.
//2: Output mode, max speed 2 MHz.
//3: Output mode, max speed 50 MHz

#define GPIO_speed_10M				1
#define GPIO_speed_2M				2
#define GPIO_speed_50M				3


//@ ref  GPIO_PINS_state
#define GPIO_PIN_SET				1
#define GPIO_PIN_RESET				0

//@ref GPIO_Return_lock
#define GPIO_Return_lock_Enabled	1
#define GPIO_Return_lock_ERROR		0
//=============================================================================
/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/

void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx , GPIO_Pinconfig_t *pinconfig );
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx );
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx ,uint16_t pinNumber );
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx );
void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx ,uint16_t pinNumber ,uint8_t value);
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx ,uint16_t value);
void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx ,uint16_t pinNumber );
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef *GPIOx ,uint16_t pinNumber );
//===============================================================================

#endif /* INC_STM32_F103C6_GPIO_H_ */
