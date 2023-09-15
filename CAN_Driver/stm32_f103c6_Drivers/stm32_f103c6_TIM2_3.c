/*
 * stm32_f103c6_TIM2_3.c
 *
 *  Created on: 13/2/2023
 *  Author: Salama mohamed
 */

#include <stm32_f103c6_TIM2_3.h>

/*
 * ===============================================================
 *
 *                      Generic Variable
 *
 * ===============================================================
 */


//===============================================================================



/*
 * ===============================================================
 *
 *                      Generic Macro
 *
 * ===============================================================
 */


//=======================================================================================



/*
 * ===============================================================
 *
 *                      Generic Function
 *
 * ===============================================================
 */

//==========================================================================================



/*
 * ===============================================================
 *
 *                      API Function Definitions
 *
 * ===============================================================
 */

/**================================================================
* @Fn				-MCAL_TIMx_Init
* @brief		  	-Initializes the Timer [2-3] according to the specified parameters in the TIMx_Config
* 					 @ ref  TIM2_MODE_Define  and @ ref  TIM2_COUNT_MODE_Define and @ ref  TIM2_Prescalers_Defin
* @param [in] 		-TIMx_Config: configuration information for the specified timer 2 or 3
* @param [in] 		-TIMx:  specified TIMx x=[ 2 : 3 ]
* @param [in] 		-Chan:  specified channel from 1 to 4
* @retval 			-none
* Note				-Support Fast PWM and Normal ( delay mode )
*/
void MCAL_TIMx_Init( TIMx_TypeDef* TIMx , TIMx_config_t* TIMx_Config , channel Chan )
{
	GPIO_Pinconfig_t pinconfig ;
	// Enable counter and Disable update event
	TIMx->CR1=0b10000001;
	//set delay mode or PWM mode
	if(TIMx_Config->MODE != TIMx_MODE_Delay)
	{
		// set pin
		if(TIMx==TIM2)
		{
			RCC_TIM2_CLK_Enable();//clock enable
			pinconfig.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP  ;
			pinconfig.GPIO_OUTPUT_Speed = GPIO_speed_10M ;
			switch(Chan)
			{
			case CH1 :
				{
					//set pin outpt
					pinconfig.pinNumber = GPIO_PIN_0 ;
					break;
				}
			case CH2 :
				{
					//set pin output
					pinconfig.pinNumber = GPIO_PIN_1 ;
					break;
				}
			case CH3 :
				{
					//set pin output
					pinconfig.pinNumber = GPIO_PIN_2 ;
					break;
				}
			case CH4 :
				{
					//set pin output
					pinconfig.pinNumber = GPIO_PIN_3 ;
					break;
				}
			}
			MCAL_GPIO_Init(GPIOA, &pinconfig) ;
			//Disable interrupt
			 NVIC_IRQ28_TIM2_Disable();
		}
		else if(TIMx==TIM3)
		{
			pinconfig.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP  ;
			pinconfig.GPIO_OUTPUT_Speed = GPIO_speed_10M ;
			switch(Chan)
			{
			case CH1 :
				{
					//set pin output
					pinconfig.pinNumber = GPIO_PIN_6 ;
					MCAL_GPIO_Init(GPIOA, &pinconfig) ;
					break;
				}
			case CH2 :
				{
					//set pin output
					pinconfig.pinNumber = GPIO_PIN_7 ;
					MCAL_GPIO_Init(GPIOA, &pinconfig) ;
					break;
				}
			case CH3 :
				{
					//set pin output
					pinconfig.pinNumber = GPIO_PIN_0 ;
					MCAL_GPIO_Init(GPIOB, &pinconfig) ;
					break;
				}
			case CH4 :
				{
					//set pin output
					pinconfig.pinNumber = GPIO_PIN_1 ;
					MCAL_GPIO_Init(GPIOB, &pinconfig) ;
					break;
				}
			}
			//Disable interrupt
			 NVIC_IRQ28_TIM2_Disable();
		}
		else if(TIMx==TIM4)
		{
			pinconfig.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP  ;
			pinconfig.GPIO_OUTPUT_Speed = GPIO_speed_10M ;
			switch(Chan)
			{
			case CH1 :
				{
					//set pin output
					pinconfig.pinNumber = GPIO_PIN_6 ;
					break;
				}
			case CH2 :
				{
					//set pin output
					pinconfig.pinNumber = GPIO_PIN_7 ;
					break;
				}
			case CH3 :
				{
					//set pin output
					pinconfig.pinNumber = GPIO_PIN_8 ;
					break;
				}
			case CH4 :
				{
					//set pin output
					pinconfig.pinNumber = GPIO_PIN_9 ;

					break;
				}
			}
			MCAL_GPIO_Init(GPIOB, &pinconfig) ;
			//Disable interrupt
			 NVIC_IRQ30_TIM4_Disable();
		}
		// set PWM mode 1 or PWM mode 2 and Output compare  preload enable
		switch(Chan)
		{
		case CH1 :
			{
				TIMx->CCMR1 |=15<<3;
				break;
			}
		case CH2 :
			{
				TIMx->CCMR1 |=15<<11;
				break;
			}
		case CH3 :
			{
				TIMx->CCMR2 |=15<<3;
				break;
			}
		case CH4 :
			{
				TIMx->CCMR2 |=15<<11;
				break;
			}
		}
	}
	else
	{
		//delay mode
		switch(Chan)
		{
		case CH1 :
			{
				TIMx->CCMR1 &=~(15<<3);
				break;
			}
		case CH2 :
			{
				TIMx->CCMR1 &=~(15<<11);
				break;
			}
		case CH3 :
			{
				TIMx->CCMR2 &=~(15<<3);
				break;
			}
		case CH4 :
			{
				TIMx->CCMR2  &=~(15<<11);
				break;
			}
		}
	}
	//output polarity and  output enable
	switch(Chan)
	{
	case CH1 :
		{
			TIMx->CCER|=3<<0;
			//set init Compare value 10000
			TIMx->CCR1 = 10000;
			break;
		}
	case CH2 :
		{
			TIMx->CCER|=3<<4;
			//set init Compare value 10000
			TIMx->CCR2 = 10000;
			break;
		}
	case CH3 :
		{
			TIMx->CCER|=3<<8;
			//set init Compare value 10000
			TIMx->CCR3 = 10000;
			break;
		}
	case CH4 :
		{
			TIMx->CCER|=3<<12;
			//set init Compare value 10000
			TIMx->CCR4 = 10000;
			break;
		}
	}
	// set Prescalers
	TIMx->PSC = TIMx_Config->Prescalers;
	//set init top value 20000
	TIMx->ARR = 20000;
}

/**================================================================
* @Fn				-MCAL_TIMx_Set_Compare_Value
* @brief		  	-set a compare value to compared with the counter value  to generate waveform output (at PWM Mode)
* @param [in] 		-TIMx:  specified TIMx x=[ 2 : 3 ]
* @param [in] 		-Compare_Value: Compare_Value pass to CCRx x=[1:4]
* @param [in] 		-Chan: Chose channel 1,2,3 or 4 (TIMx contains 4 channel)
* @retval 			-none
* Note				-none
*/
void MCAL_TIMx_Set_Compare_Value( TIMx_TypeDef* TIMx  , uint16_t Compare_Value , channel Chan )
{

	switch(Chan)
	{
	case CH1 :
		{
			TIMx->CCR1 = Compare_Value;
			break;
		}
	case CH2 :
		{
			TIMx->CCR2 = Compare_Value;
			break;
		}
	case CH3 :
		{
			TIMx->CCR3 = Compare_Value;
			break;
		}
	case CH4 :
		{
			TIMx->CCR4 = Compare_Value;
			break;
		}
	}
	TIM3->EGR |=1<<0;
}

/**================================================================
* @Fn				-MCAL_TIMx_Set_TOP_Value
* @brief		  	-set a TOP value , it is maximum value the timer can reach (to control the output frequency)
* @param [in] 		-TOP_Value: TOP_Value pass to ARR
* @param [in] 		-TIMx:  specified TIMx x=[ 2 : 3 ]
* @retval 			-none
* Note				-none
*/
void MCAL_TIMx_Set_TOP_Value( TIMx_TypeDef* TIMx  , uint16_t TOP_Value )
{
	TIMx->ARR=TOP_Value;
}


/**================================================================
* @Fn				-MCAL_TIMx_DeInit
* @brief		  	-Disable counter
* @param [in] 		-TIMx:  specified TIMx x=[ 2 : 3 ]
* @retval 			-none
* Note				-none
*/
void MCAL_TIMx_DeInit( TIMx_TypeDef* TIMx )
{
	TIMx->ARR=0;
	TIMx->CR1=0;
}
//================================================================================================
