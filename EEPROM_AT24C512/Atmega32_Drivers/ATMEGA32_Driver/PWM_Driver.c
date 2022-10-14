/*
 * PWM_Driver.c
 *
 * Created: 10/13/2022 8:16:25 PM
 *  Author: Salama Mohamed
 */ 

#include "PWM_Driver.h"


/*
 * ===============================================================
 *
 *                      Generic Variable
 *
 * ===============================================================
 */

PWM_config_t* g_PWM_Config = NULL ;

//===============================================================================

/*
 * ===============================================================
 *
 *                      API Function Definitions
 *
 * ===============================================================
 */

/**================================================================
* @Fn				-MCAL_PWM_Init
* @brief		  	-Initializes the TIMER1  according to the specified parameters in the TIMER_Config
* 					 @ ref  PWM_Output_Compare_pin_A_Define  and  @ ref  PEM_Clock_Source_Define  and ....
* @param [in] 		-PWM_Config: configuration information for  TIMER1
* 					 take 3 pointers to function (this function calling at interrupt)
* @retval 			-none
* Note				-Support Fast PWM Only
*/
void MCAL_PWM_Init(PWM_config_t* PWM_Config)
{
	g_PWM_Config = PWM_Config ;
	uint8_t Temp_TCCR1B=0 , Temp_TCCR1A=0 ;
	//Set Fast PWM and TOP at ICR1
	Temp_TCCR1B |=(3<<3) ;
	Temp_TCCR1A |=(2<<0) ;
	//Set Output_Compare_pin_A
	Temp_TCCR1A |=PWM_Config->Output_Compare_pin_A ;
	if ( PWM_Config->Output_Compare_pin_A != PWM_Output_Compare_pin_A_Disable)
	{
		GPIO_Pinconfig_t pinconfig ;
		pinconfig.pinNumber = GPIO_PIN_5 ;
		pinconfig.GPIO_MODE = GPIO_MODE_OUTPUT ;
		MCAL_GPIO_Init(GPIOD , &pinconfig ) ;
	}
	//Set Output_Compare_pin_B
	Temp_TCCR1B |=PWM_Config->Output_Compare_pin_B ;
	if ( PWM_Config->Output_Compare_pin_B != PWM_Output_Compare_pin_B_Disable)
	{
		GPIO_Pinconfig_t pinconfig ;
		pinconfig.pinNumber = GPIO_PIN_4 ;
		pinconfig.GPIO_MODE = GPIO_MODE_OUTPUT ;
		MCAL_GPIO_Init(GPIOD , &pinconfig ) ;
	}
	//Set Clock Source
	Temp_TCCR1B |= PWM_Config->Clock_Source;
	//Set IRQ_EN
	if (PWM_Config->TOIE1_EN==PWM_TOIE1_ENABLE_Enable)
	{
		TIMR1_TOIE1_INT_Enable() ;
		EXTI_GLOBAL_Enable() ;
	}
	else
	{
		TIMR1_TOIE1_INT_Disable() ;
		EXTI_GLOBAL_Disable() ;
	}
	if (PWM_Config->OCIE1A_EN==PWM_OCIE1A_ENABLE_Enable)
	{
		TIMR1_OCIE1A_INT_Enable() ;
		EXTI_GLOBAL_Enable() ;
	}
	else
	{
		TIMR1_OCIE1A_INT_Disable();
		EXTI_GLOBAL_Disable() ;
	}
	if (PWM_Config->OCIE1A_EN==PWM_OCIE1A_ENABLE_Enable)
	{
		TIMR1_OCIE1A_INT_Enable() ;
		EXTI_GLOBAL_Enable() ;
	}
	else
	{
		TIMR1_OCIE1B_INT_Disable();
		EXTI_GLOBAL_Disable() ;
	}
	//Set TOP Value
	TIMER1->ICR1H = (uint8_t)(PWM_Config->TOP_Value>>8);
	TIMER1->ICR1L = (uint8_t)(PWM_Config->TOP_Value);
	//Set Compare_Value_CH_A
	TIMER1->OCR1AH = (uint8_t)(PWM_Config->Compare_Value_CH_A>>8);
	TIMER1->OCR1AL = (uint8_t)(PWM_Config->Compare_Value_CH_A);
	//Set Compare_Value_CH_B
	TIMER1->OCR1BH = (uint8_t)(PWM_Config->Compare_Value_CH_B>>8);
	TIMER1->OCR1BL = (uint8_t)(PWM_Config->Compare_Value_CH_B);
	
	TIMER1->TCCR1A = Temp_TCCR1A ;
	TIMER1->TCCR1B = Temp_TCCR1B ;
}


/**================================================================
* @Fn				-MCAL_PWM_DInit
* @brief		  	-Disable  TIMER1 and Disable global interrupt and clear register For TIMER1
* @retval 			-none
* Note				-none
*/
void MCAL_PWM_DInit(void)
{
	TIMER1->TCCR1A = 0 ;
	TIMER1->TCCR1B = 0 ;
	TIMSK = 0 ;
	TIMER1->OCR1AH = 0 ;
	TIMER1->OCR1AL = 0 ;
	TIMER1->OCR1BH = 0 ;
	TIMER1->OCR1BL = 0 ;
	TIMER1->ICR1H = 0 ;
	TIMER1->ICR1L =0 ;
}


/**================================================================
* @Fn				-MCAL_PWM_Set_Compare_Value
* @brief		  	-set a compare value to compared with the counter value (TCNT1). used to generate waveform output on the OC1A OR OC1B pin
* @param [in] 		-Compare_Value: Compare_Value pass to OCR1A/OCR1B
* @param [in] 		-Chan: Chose channel A or B (timer1 contains 2 channel A and B )
* @retval 			-none
* Note				-Support Fast PWM Only 
*/
void MCAL_PWM_Set_Compare_Value(uint16_t Compare_Value , channel Chan ) 
{
	if( Chan == A)
	{
		//Set Compare_Value_CH_A
		TIMER1->OCR1AH = (uint8_t)(Compare_Value>>8);
		TIMER1->OCR1AL = (uint8_t)(Compare_Value);
	}
	else
	{
		//Set Compare_Value_CH_B
		TIMER1->OCR1BH = (uint8_t)(Compare_Value>>8);
		TIMER1->OCR1BL = (uint8_t)(Compare_Value);
	}
}


/**================================================================
* @Fn				-MCAL_PWM_Set_TOP_Value
* @brief		  	-set a TOP value , it is maximum value the timer can reach (to control the output frequency) 
* @param [in] 		-TOP_Value: TOP_Value pass to ICR1
* @retval 			-none
* Note				-Support Fast PWM Only
*/
void MCAL_PWM_Set_TOP_Value(uint16_t TOP_Value ) 
{
	//Set TOP Value
	TIMER1->ICR1H = (uint8_t)(TOP_Value>>8);
	TIMER1->ICR1L = (uint8_t)(TOP_Value);
}

//==================================================================================

/*
 * ===============================================================
 *
 *                      ISR Function Definitions
 *
 * ===============================================================
 */

void __vector_9 (void) __attribute__((signal));
void __vector_9 (void)
{
	g_PWM_Config->P_TOIE1_CALL();
}

void __vector_7 (void) __attribute__((signal));
void __vector_7 (void)
{
	g_PWM_Config->P_OCIE1A_CALL();
}

void __vector_8 (void) __attribute__((signal));
void __vector_8 (void)
{
	g_PWM_Config->P_OCIE1B_CALL();
}
//========================================================================================