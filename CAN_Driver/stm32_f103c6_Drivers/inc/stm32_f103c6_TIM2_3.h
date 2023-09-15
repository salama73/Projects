/*
 * stm32_f103c6_TIM2_3.h
 *
 *  Created on: 13/2/2023
 *  Author: Salama mohamed
 */

#ifndef INC_STM32_F103C6_TIM2_3_H_
#define INC_STM32_F103C6_TIM2_3_H_

//Include
#include "stm32f103x6.h"
#include "stm32_f103c6_RCC.h"
#include"stm32_f103c6_GPIO.h"




//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
	uint16_t MODE 			 ; 	   //specified the Timer2 Mode (Support PWM only) to be configured .
					     	 	  //this parameter must be set based on  @ ref  TIM2_MODE_Define

	uint16_t COUNT_MODE	     ;	  //specified the Counter mode (UP,DOWN,UP/DOWN ).
								 //this parameter must be set based on  @ ref TIM2_COUNT_MODE_Define

	uint16_t Prescalers		 ;	//The prescaler can divide the counter clock frequency by any factor between 1 and 65536..
								//this parameter must be set based on  @ ref TIM2_Prescalers_Define

}TIMx_config_t;

typedef enum
{
	CH1,
	CH2,
	CH3,
	CH4
}channel;

//=========================================================================

//-----------------------------
//Macros Configuration References
//-----------------------------

// @ ref  TIMx_MODE_Define

/*
: PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1
else inactive. In downcounting, channel 1 is inactive (OC1REF=‘0) as long as
TIMx_CNT>TIMx_CCR1 else active (OC1REF=1)

111: PWM mode 2 - In upcounting, channel 1 is inactive as long as TIMx_CNT<TIMx_CCR1
else active. In downcounting, channel 1 is active as long as TIMx_CNT>TIMx_CCR1 else
inactive.
 */
#define  TIMx_MODE_PWM1				(uint16_t)(0)
#define  TIMx_MODE_PWM2				(uint16_t)(1)
#define  TIMx_MODE_Delay			(uint16_t)(2)




//@ ref TIMx_Prescalers_Define

/*
The counter clock frequency CK_CNT is equal to fCK_PSC / (PSC[15:0] + 1).
PSC contains the value to be loaded in the active prescaler register at each update event
(including when the counter is cleared through UG bit of TIMx_EGR register or through
trigger controller when configured in “reset mode”).
 */



// @ ref  @ ref TIMx_COUNT_MODE_Define

#define  TIMx_COUNT_MODE_UP			(uint16_t)(0)
#define  TIMx_COUNT_MODE_DOWN		(uint16_t)(1<<4)


/* ===============================================
* APIs Supported by "MCAL TIMER DRIVER"
* ===============================================
*/
void MCAL_TIMx_Init( TIMx_TypeDef* TIMx , TIMx_config_t* TIMx_Config , channel Chan );
void MCAL_TIMx_Set_Compare_Value( TIMx_TypeDef* TIMx  , uint16_t Compare_Value , channel Chan ) ;
void MCAL_TIMx_Set_TOP_Value( TIMx_TypeDef* TIMx  , uint16_t TOP_Value ) ;
void MCAL_TIMx_DeInit( TIMx_TypeDef* TIMx );


//===============================================================================

#endif /* INC_STM32_F103C6_TIM2_3_H_ */
