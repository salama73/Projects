﻿/*
 * EXTI_Driver.c
 *
 * Created: 31/08/2022 11:54:55 م
 *  Author: salama mohamed
 */ 

#include "EXTI_Driver.h"
/*
 * ===============================================================
 *
 *                      Generic Variable
 *
 * ===============================================================
 */

void (*GP_IRQ_CALL[3])(void);

//=========================================================================================



/*
 * ===============================================================
 *
 *                      Generic Macro
 *
 * ===============================================================
 */


//==========================================================================================



/*
 * ===============================================================
 *
 *                      Generic Function
 *
 * ===============================================================
 */


//====================================================================================================



/*
 * ===============================================================
 *
 *                      API Function Definitions
 *
 * ===============================================================
 */





/**================================================================
* @Fn				-MCAL_EXTI_GPIO_Init
* @brief		  	-Initializes the EXTI [0-3] according to the specified parameters in the EXTI_Config
* 					 @ ref  EXTI_Define And @ ref  EXTI_Trigger_Define Trigger and @ ref  EXTI_IRQ_Define to enable and disable
* @param [in] 		-EXTI_Config: configuration information for the specified EXTI from 0 to 2
* 					 take a pointer to function (this function calling at interrupt)
* @retval 			-none
* Note				-none
*/

void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t* EXTI_Config)
{
	GPIO_Pinconfig_t pin ;// used to set GPIO
	
	if ( EXTI_Config->EXTI_Number == EXTI_INT0 )
	{
		//1 GPIO INPUT PORTD PIN 2
		pin.pinNumber = GPIO_PIN_2 ;
		pin.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
		MCAL_GPIO_Init(GPIOD , &pin ) ;
		
		// 2 Set Rising and Falling
		// Clear
		EXTI->MCUCR &=~(0X3) ;
		// set
		if( EXTI_Config->Trigger_case == EXTI_Trigger_Falling )
		{
			EXTI->MCUCR |= 0X3 ;
		}
		else if ( EXTI_Config->Trigger_case == EXTI_Trigger_Rising )
		{
			EXTI->MCUCR |= 0X2 ;
		}
		else
		{
			EXTI->MCUCR |= 0X1 ;
		}
		
		//3 IRQ Function Call
		GP_IRQ_CALL[EXTI_Config->EXTI_Number] = EXTI_Config->P_IRQ_CALL ;
		
		//4 Enable EXTI
		if( EXTI_Config->EXTI_EN == EXTI_IRQ_Enable)
		{
			EXTI_GLOBAL_Enable()	;
			EXTI_INT0_Enable()		;
		}
		else
		{
			EXTI_GLOBAL_Disable()	;
			EXTI_INT0_Disable()		;
		}
		
	}
	else if ( EXTI_Config->EXTI_Number == EXTI_INT1 )
	{
		//1 GPIO INPUT PORTD PIN 3
		pin.pinNumber = GPIO_PIN_3 ;
		pin.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
		MCAL_GPIO_Init(GPIOD , &pin ) ;
		
		// 2 Set Rising and Falling
		// Clear
		EXTI->MCUCR &=~(0X3 << 2 ) ;
		// set
		if( EXTI_Config->Trigger_case == EXTI_Trigger_Falling )
		{
			EXTI->MCUCR |= ( 0X3 <<2 ) ;
		}
		else if ( EXTI_Config->Trigger_case == EXTI_Trigger_Rising )
		{
			EXTI->MCUCR |= ( 0X2 << 2 ) ;
		}
		else
		{
			EXTI->MCUCR |= ( 0X1 << 2 ) ;
		}
		
		//3 IRQ Function Call
		GP_IRQ_CALL[EXTI_Config->EXTI_Number] = EXTI_Config->P_IRQ_CALL ;
		
		//4 Enable EXTI
		if( EXTI_Config->EXTI_EN == EXTI_IRQ_Enable)
		{
			EXTI_GLOBAL_Enable()	;
			EXTI_INT1_Enable()		;
		}
		else
		{
			EXTI_GLOBAL_Disable()	;
			EXTI_INT1_Disable()		;
		}
	}
	else
	{
		//1 GPIO INPUT PORTB PIN 2
		pin.pinNumber = GPIO_PIN_2 ;
		pin.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
		MCAL_GPIO_Init(GPIOB , &pin ) ;
		
		// 2 Set Rising and Falling
		// Clear
		EXTI->MCUCSR &=~( 1 << 6 ) ;
		// set
		if( EXTI_Config->Trigger_case == EXTI_Trigger_Falling )
		{
			EXTI->MCUCSR &=~( 1 << 6 ) ;
		}
		else if ( EXTI_Config->Trigger_case == EXTI_Trigger_Rising )
		{
			EXTI->MCUCSR |=( 1 << 6 ) ;
		}
		
		//3 IRQ Function Call
		GP_IRQ_CALL[EXTI_Config->EXTI_Number] = EXTI_Config->P_IRQ_CALL ;
		
		//4 Enable EXTI
		if( EXTI_Config->EXTI_EN == EXTI_IRQ_Enable)
		{
			EXTI_GLOBAL_Enable()	;
			EXTI_INT2_Enable()		;
		}
		else
		{
			EXTI_GLOBAL_Disable()	;
			EXTI_INT2_Disable()		;
		}
		
	}
}






/**================================================================
* @Fn				-MCAL_EXTI_GPIO_DeInit
* @brief		  	-Reset all the EXTI Register
* @retval 			-none
* Note				-none
*/

void MCAL_EXTI_GPIO_DeInit(void)
{
	EXTI_GLOBAL_Disable()		;
	EXTI->MCUCSR &=~( 1 << 6 )	;
	EXTI->MCUCR &=~( 0XF )		;
	EXTI_INT0_Disable()			;
	EXTI_INT1_Disable()			;
	EXTI_INT2_Disable()			;
}

//=========================================================================================================

/*
 * ===============================================================
 *
 *                      ISR Function Definitions
 *
 * ===============================================================
 */


void __vector_1 (void) __attribute__((signal));
void __vector_1 (void)
{
	//Call function
	GP_IRQ_CALL[0]();
}


void __vector_2 (void) __attribute__((signal));
void __vector_2 (void)
{
	//Call function
	GP_IRQ_CALL[1]();
}


void __vector_3 (void) __attribute__((signal));
void __vector_3 (void)
{
	//Call function
	GP_IRQ_CALL[2]();
}
