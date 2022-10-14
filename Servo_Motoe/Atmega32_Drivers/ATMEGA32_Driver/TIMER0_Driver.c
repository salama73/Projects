/*
 * TIMER0_Driver.c
 *
 * Created: 10/11/2022 3:07:05 AM
 *  Author: Salama Mohamed
 */ 


#include "TIMER0_Driver.h"


/*
 * ===============================================================
 *
 *                      Generic Variable
 *
 * ===============================================================
 */

TIMER0_config_t* g_TIM0_Config = NULL ;

//===============================================================================

/*
 * ===============================================================
 *
 *                      API Function Definitions
 *
 * ===============================================================
 */

/**================================================================
* @Fn				-MCAL_TIMER0_Init
* @brief		  	-Initializes the TIMER0  according to the specified parameters in the TIMER0_Config
* 					 @ ref  TIMER0_OCIE0_ENABLE_Define  and  @ ref  TIMER0_Clock_Source_Define  and ....
* @param [in] 		-TIMER0_Config: configuration information for  TIMER0
* 					 take 2 pointers to function (this function calling at interrupt)
* @retval 			-none
* Note				-Support Normal mode and CTC
*/
void MCAL_TIMER0_Init(TIMER0_config_t* TIMER0_Config)
{
	g_TIM0_Config = TIMER0_Config;
	uint8_t Temp_TCCR0=0 , Temp_TIMSK=0;
	//Set timer0 mode
	Temp_TCCR0 =TIMER0_Config->Timer0_Mode ;
	//Set Clock Source
	Temp_TCCR0 |= TIMER0_Config->Clock_Source;
	//Set Output Compare pin 
	if ( TIMER0_Config->Output_Compare_pin != TIMER0_Output_Compare_pin_Disable)
	{
		Temp_TCCR0 |= TIMER0_Config->Output_Compare_pin;
		GPIO_Pinconfig_t pinconfig ;
		pinconfig.pinNumber = GPIO_PIN_3 ;
		pinconfig.GPIO_MODE = GPIO_MODE_OUTPUT ;
		MCAL_GPIO_Init(GPIOB , &pinconfig ) ;
	}
	//Set Output Compare pin TOIE0_EN
	Temp_TIMSK |=TIMER0_Config->TOIE0_EN ;
	//Set Output Compare pin OCIE0_EN
	Temp_TIMSK |=TIMER0_Config->OCIE0_EN ;
	//Set Compare Value
	OCR0 = TIMER0_Config->Compare_Value;
	//Set IRQ_EN
	if (TIMER0_Config->TOIE0_EN==TIMER0_TOIE0_ENABLE_Enable)
	{
		TIMR0_TOIE0_INT_Enable() ;
		EXTI_GLOBAL_Enable() ;
	}
	else
	{
		TIMR0_TOIE0_INT_Disable() ;
		EXTI_GLOBAL_Disable() ;
	}
	if (TIMER0_Config->OCIE0_EN==TIMER0_OCIE0_ENABLE_Enable)
	{
		TIMR0_OCIE0_INT_Enable() ;
		EXTI_GLOBAL_Enable() ;
	}
	else
	{
		TIMR0_OCIE0_INT_Disable();
		EXTI_GLOBAL_Disable() ;
	}
	TCCR0 = Temp_TCCR0 ;
	TIMSK = Temp_TIMSK ;
}

/**================================================================
* @Fn				-MCAL_TIMER0_Set_Compare_Value
* @brief		  	-set a compare value to compared with the counter value (TCNT0). used to generate waveform output on the OC0 pin
* @param [in] 		-Compare_Value: Compare_Value pass to OCR0
* @retval 			-none
* Note				-Support Normal mode and CTC
*/
void MCAL_TIMER0_Set_Compare_Value(uint8_t Compare_Value) 
{
	OCR0 = Compare_Value ;
}


/**================================================================
* @Fn				-MCAL_TIMER0_Read_Compare_Value
* @brief		  	-Read the compare value 
* @retval 			-compare value
* Note				-Support Normal mode and CTC
*/
uint8_t MCAL_TIMER0_Read_Compare_Value() 
{
	return OCR0 ;
}

/**================================================================
* @Fn				-MCAL_TIMER0_Read_Counter_Value
* @brief		  	-Read the Counter Value
* @retval 			-Counter value
* Note				-Support Normal mode and CTC
*/
uint8_t MCAL_TIMER0_Read_Counter_Value() 
{
	return TCNT0 ;
}


/*
 * ===============================================================
 *
 *                      ISR Function Definitions
 *
 * ===============================================================
 */

void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	g_TIM0_Config->P_OCIE0_CALL();
}

void __vector_11 (void) __attribute__((signal));
void __vector_11 (void)
{
	g_TIM0_Config->P_TOIE0_CALL();
}

//========================================================================================