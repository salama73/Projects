/*
 * stm32_f103c6_EXTI.h
 *
 *  Created on: Aug 29, 2022
 *      Author: Salama Mohamed
 */

#ifndef INC_STM32_F103C6_EXTI_H_
#define INC_STM32_F103C6_EXTI_H_

//Include
#include "stm32f103x6.h"




//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
	uint16_t 				ETI_LineNumber;
	GPIO_TypeDef* 			GPIO_PORT;
	uint16_t				GPIO_Pin;
	uint8_t					IVT_IRQ_Number;
}EXTI_GPIO_Maping_t;

typedef struct
{
	EXTI_GPIO_Maping_t		EXTI_Pin; 	   		     //specified the EXTI  pin to be configured .
												    //this parameter must be set based on  @ ref  EXTI_Define

	uint8_t					Trigger_case;  		   //specified Rising or Falling or Both Trigger  .
												  //this parameter must be set based on  @ ref  EXTI_Trigger_Define

	uint8_t					IRQ_EN;  		     //Enable or Disable EXTI_IRQ (EXTI MASK and NVIC Interrupt .
												//this parameter must be set based on  @ ref  EXTI_IRQ_Define
	void (*P_IRQ_CALL)(void);                   // set the function which will be call at IRQ happen

}EXTI_PinConfig_t;
//=========================================================================
//-----------------------------
//Macros Configuration EXTI

#define EXTI0				0
#define EXTI1				1
#define EXTI2				2
#define EXTI3				3
#define EXTI4				4
#define EXTI5				5
#define EXTI6				6
#define EXTI7				7
#define EXTI8				8
#define EXTI9				9
#define EXTI10				10
#define EXTI11				11
#define EXTI12				12
#define EXTI13				13
#define EXTI14				14
#define EXTI15				15

//-----------------------------

//==========================================================================
//-----------------------------
//Macros Configuration References
//-----------------------------

//@ ref  EXTI_Define
//EXTI0
#define EXTI0_PA0		(EXTI_GPIO_Maping_t){EXTI0 , GPIOA , GPIO_PIN_0 , EXTI0_IRQ}
#define EXTI0_PB0		(EXTI_GPIO_Maping_t){EXTI0 , GPIOB , GPIO_PIN_0 , EXTI0_IRQ}
#define EXTI0_PC0		(EXTI_GPIO_Maping_t){EXTI0 , GPIOC , GPIO_PIN_0 , EXTI0_IRQ}
#define EXTI0_PD0		(EXTI_GPIO_Maping_t){EXTI0 , GPIOD , GPIO_PIN_0 , EXTI0_IRQ}
//EXTI1
#define EXTI1_PA1		(EXTI_GPIO_Maping_t){EXTI1 , GPIOA , GPIO_PIN_1 , EXTI1_IRQ}
#define EXTI1_PB1		(EXTI_GPIO_Maping_t){EXTI1 , GPIOB , GPIO_PIN_1 , EXTI1_IRQ}
#define EXTI1_PC1		(EXTI_GPIO_Maping_t){EXTI1 , GPIOC , GPIO_PIN_1 , EXTI1_IRQ}
#define EXTI1_PD1		(EXTI_GPIO_Maping_t){EXTI1 , GPIOD , GPIO_PIN_1 , EXTI1_IRQ}
//EXTI2
#define EXTI2_PA2		(EXTI_GPIO_Maping_t){EXTI2 , GPIOA , GPIO_PIN_2 , EXTI2_IRQ}
#define EXTI2_PB2		(EXTI_GPIO_Maping_t){EXTI2 , GPIOB , GPIO_PIN_2 , EXTI2_IRQ}
#define EXTI2_PC2		(EXTI_GPIO_Maping_t){EXTI2 , GPIOC , GPIO_PIN_2 , EXTI2_IRQ}
#define EXTI2_PD2		(EXTI_GPIO_Maping_t){EXTI2 , GPIOD , GPIO_PIN_2 , EXTI2_IRQ}
//EXTI3
#define EXTI3_PA3		(EXTI_GPIO_Maping_t){EXTI3 , GPIOA , GPIO_PIN_3 , EXTI3_IRQ}
#define EXTI3_PB3		(EXTI_GPIO_Maping_t){EXTI3 , GPIOB , GPIO_PIN_3 , EXTI3_IRQ}
#define EXTI3_PC3		(EXTI_GPIO_Maping_t){EXTI3 , GPIOC , GPIO_PIN_3 , EXTI3_IRQ}
#define EXTI3_PD3		(EXTI_GPIO_Maping_t){EXTI3 , GPIOD , GPIO_PIN_3 , EXTI3_IRQ}
//EXTI4
#define EXTI4_PA4		(EXTI_GPIO_Maping_t){EXTI4 , GPIOA , GPIO_PIN_4 , EXTI4_IRQ}
#define EXTI4_PB4		(EXTI_GPIO_Maping_t){EXTI4 , GPIOB , GPIO_PIN_4 , EXTI4_IRQ}
#define EXTI4_PC4		(EXTI_GPIO_Maping_t){EXTI4 , GPIOC , GPIO_PIN_4 , EXTI4_IRQ}
#define EXTI4_PD4		(EXTI_GPIO_Maping_t){EXTI4 , GPIOD , GPIO_PIN_4 , EXTI4_IRQ}
//EXTI5
#define EXTI5_PA5		(EXTI_GPIO_Maping_t){EXTI5 , GPIOA , GPIO_PIN_5 , EXTI5_IRQ}
#define EXTI5_PB5		(EXTI_GPIO_Maping_t){EXTI5 , GPIOB , GPIO_PIN_5 , EXTI5_IRQ}
#define EXTI5_PC5		(EXTI_GPIO_Maping_t){EXTI5 , GPIOC , GPIO_PIN_5 , EXTI5_IRQ}
#define EXTI5_PD5		(EXTI_GPIO_Maping_t){EXTI5 , GPIOD , GPIO_PIN_5 , EXTI5_IRQ}
//EXTI6
#define EXTI6_PA6		(EXTI_GPIO_Maping_t){EXTI6 , GPIOA , GPIO_PIN_6 , EXTI6_IRQ}
#define EXTI6_PB6		(EXTI_GPIO_Maping_t){EXTI6 , GPIOB , GPIO_PIN_6 , EXTI6_IRQ}
#define EXTI6_PC6		(EXTI_GPIO_Maping_t){EXTI6 , GPIOC , GPIO_PIN_6 , EXTI6_IRQ}
#define EXTI6_PD6		(EXTI_GPIO_Maping_t){EXTI6 , GPIOD , GPIO_PIN_6 , EXTI6_IRQ}
//EXTI7
#define EXTI7_PA7		(EXTI_GPIO_Maping_t){EXTI7 , GPIOA , GPIO_PIN_7 , EXTI7_IRQ}
#define EXTI7_PB7		(EXTI_GPIO_Maping_t){EXTI7 , GPIOB , GPIO_PIN_7 , EXTI7_IRQ}
#define EXTI7_PC7		(EXTI_GPIO_Maping_t){EXTI7 , GPIOC , GPIO_PIN_7 , EXTI7_IRQ}
#define EXTI7_PD7		(EXTI_GPIO_Maping_t){EXTI7 , GPIOD , GPIO_PIN_7 , EXTI7_IRQ}
//EXTI8
#define EXTI8_PA8		(EXTI_GPIO_Maping_t){EXTI8 , GPIOA , GPIO_PIN_8 , EXTI8_IRQ}
#define EXTI8_PB8		(EXTI_GPIO_Maping_t){EXTI8 , GPIOB , GPIO_PIN_8 , EXTI8_IRQ}
#define EXTI8_PC8		(EXTI_GPIO_Maping_t){EXTI8 , GPIOC , GPIO_PIN_8 , EXTI8_IRQ}
#define EXTI8_PD8		(EXTI_GPIO_Maping_t){EXTI8 , GPIOD , GPIO_PIN_8 , EXTI8_IRQ}
//EXTI9
#define EXTI9_PA9		(EXTI_GPIO_Maping_t){EXTI9 , GPIOA , GPIO_PIN_9 , EXTI9_IRQ}
#define EXTI9_PB9		(EXTI_GPIO_Maping_t){EXTI9 , GPIOB , GPIO_PIN_9 , EXTI9_IRQ}
#define EXTI9_PC9		(EXTI_GPIO_Maping_t){EXTI9 , GPIOC , GPIO_PIN_9 , EXTI9_IRQ}
#define EXTI9_PD9		(EXTI_GPIO_Maping_t){EXTI9 , GPIOD , GPIO_PIN_9 , EXTI9_IRQ}
//EXTI10
#define EXTI0_PA10		(EXTI_GPIO_Maping_t){EXTI10 , GPIOA , GPIO_PIN_10 , EXTI10_IRQ}
#define EXTI0_PB10		(EXTI_GPIO_Maping_t){EXTI10 , GPIOB , GPIO_PIN_10 , EXTI10_IRQ}
#define EXTI0_PC10		(EXTI_GPIO_Maping_t){EXTI10 , GPIOC , GPIO_PIN_10 , EXTI10_IRQ}
#define EXTI0_PD10		(EXTI_GPIO_Maping_t){EXTI10 , GPIOD , GPIO_PIN_10 , EXTI10_IRQ}
//EXTI11
#define EXTI11_PA11		(EXTI_GPIO_Maping_t){EXTI11 , GPIOA , GPIO_PIN_11 , EXTI11_IRQ}
#define EXTI11_PB11		(EXTI_GPIO_Maping_t){EXTI11 , GPIOB , GPIO_PIN_11 , EXTI11_IRQ}
#define EXTI11_PC11		(EXTI_GPIO_Maping_t){EXTI11 , GPIOC , GPIO_PIN_11 , EXTI11_IRQ}
#define EXTI11_PD11		(EXTI_GPIO_Maping_t){EXTI11 , GPIOD , GPIO_PIN_11 , EXTI11_IRQ}
//EXTI12
#define EXTI12_PA12		(EXTI_GPIO_Maping_t){EXTI12 , GPIOA , GPIO_PIN_12 , EXTI12_IRQ}
#define EXTI12_PB12		(EXTI_GPIO_Maping_t){EXTI12 , GPIOB , GPIO_PIN_12 , EXTI12_IRQ}
#define EXTI12_PC12		(EXTI_GPIO_Maping_t){EXTI12 , GPIOC , GPIO_PIN_12 , EXTI12_IRQ}
#define EXTI12_PD12		(EXTI_GPIO_Maping_t){EXTI12 , GPIOD , GPIO_PIN_12 , EXTI12_IRQ}
//EXTI13
#define EXTI13_PA13		(EXTI_GPIO_Maping_t){EXTI13 , GPIOA , GPIO_PIN_13 , EXTI13_IRQ}
#define EXTI13_PB13		(EXTI_GPIO_Maping_t){EXTI13 , GPIOB , GPIO_PIN_13 , EXTI13_IRQ}
#define EXTI13_PC13		(EXTI_GPIO_Maping_t){EXTI13 , GPIOC , GPIO_PIN_13 , EXTI13_IRQ}
#define EXTI13_PD13		(EXTI_GPIO_Maping_t){EXTI13 , GPIOD , GPIO_PIN_13 , EXTI13_IRQ}
//EXTI14
#define EXTI14_PA14		(EXTI_GPIO_Maping_t){EXTI14 , GPIOA , GPIO_PIN_14 , EXTI14_IRQ}
#define EXTI14_PB14		(EXTI_GPIO_Maping_t){EXTI14 , GPIOB , GPIO_PIN_14 , EXTI14_IRQ}
#define EXTI14_PC14		(EXTI_GPIO_Maping_t){EXTI14 , GPIOC , GPIO_PIN_14 , EXTI14_IRQ}
#define EXTI14_PD14		(EXTI_GPIO_Maping_t){EXTI14 , GPIOD , GPIO_PIN_14 , EXTI14_IRQ}
//EXTI15
#define EXTI15_PA15		(EXTI_GPIO_Maping_t){EXTI15 , GPIOA , GPIO_PIN_15 , EXTI15_IRQ}
#define EXTI15_PB15		(EXTI_GPIO_Maping_t){EXTI15 , GPIOB , GPIO_PIN_15 , EXTI15_IRQ}
#define EXTI15_PC15		(EXTI_GPIO_Maping_t){EXTI15 , GPIOC , GPIO_PIN_15 , EXTI15_IRQ}
#define EXTI15_PD15		(EXTI_GPIO_Maping_t){EXTI15 , GPIOD , GPIO_PIN_15 , EXTI15_IRQ}

//=============================================================================
//@ ref  EXTI_Trigger_Define

#define EXTI_Trigger_Rising			  			0
#define EXTI_Trigger_Falling					1
#define EXTI_Trigger_Rising_and_Falling			2

//======================================================
//@ ref  EXTI_IRQ_Define

#define EXTI_IRQ_Disable			  			0
#define EXTI_IRQ_Enable					        1
//======================================================

/*
* ===============================================
* APIs Supported by "MCAL EXTI DRIVER"
* ===============================================
*/

void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t* EXTI_Config);
void MCAL_EXTI_GPIO_DeInit(void);
void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t* EXTI_Config);

//===============================================================================

#endif /* INC_STM32_F103C6_EXTI_H_ */
