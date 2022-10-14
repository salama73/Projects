/*
 * stm32_f103c6_EXTI.c
 *
 *  Created on: Aug 29, 2022
 *      Author: Salama Mohamed
 */

#include"stm32_f103c6_EXTI.h"
#include"stm32_f103c6_GPIO.h"



/*
 * ===============================================================
 *
 *                      Generic Variable
 *
 * ===============================================================
 */

void (*GP_IRQ_CALL[15])(void);

/*
 * ===============================================================
 *
 *                      Generic Macro
 *
 * ===============================================================
 */
#define AFIO_GPIO_MAP(X)		((X==GPIOA) ? 0 : (X==GPIOB) ? 1 : (X==GPIOC) ? 2 : (X==GPIOA) ? 3 : 0 )



/*
 * ===============================================================
 *
 *                      Generic Function
 *
 * ===============================================================
 */

void Enable_NVIC (uint16_t IRQ_Line)
{
	switch(IRQ_Line)
	{
	case 0:
		NVIC_IRQ6_EXTI0_Enable();
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Enable();
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Enable();
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Enable();
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Enable();
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_to_EXTI9_Enable();
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_to_EXTI15_Enable();
		break;
	}
}

void Disable_NVIC (uint16_t IRQ_Line)
{
	switch(IRQ_Line)
	{
	case 0:
		NVIC_IRQ6_EXTI0_Disable();
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Disable();
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Disable();
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Disable();
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Disable();
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_to_EXTI9_Disable();
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_to_EXTI15_Disable();
		break;
	}
}




void Configuration_EXTI(EXTI_PinConfig_t* EXTI_Config)
{
	//1 GPIO_Init
	GPIO_Pinconfig_t pinconfig;
	pinconfig.pinNumber=EXTI_Config->EXTI_Pin.GPIO_Pin;
	pinconfig.GPIO_MODE=GPIO_MODE_INPUT_AF;
	MCAL_GPIO_Init(EXTI_Config->EXTI_Pin.GPIO_PORT, &pinconfig);

	//2 INIT AFIO
	uint8_t posation   = EXTI_Config->EXTI_Pin.ETI_LineNumber / 4;
	uint8_t bit_shift  = (EXTI_Config->EXTI_Pin.ETI_LineNumber % 4) * 4;
	//Clear bits
	AFIO->EXTICR[posation] &=~(0XF<<bit_shift);
	//Clear bits
	AFIO->EXTICR[posation] |= (AFIO_GPIO_MAP(EXTI_Config->EXTI_Pin.GPIO_PORT) << bit_shift);

	// 3 Set Rising and Falling
	//Clear bits
	EXTI->RTSR &=~(1 << EXTI_Config->EXTI_Pin.ETI_LineNumber );
	EXTI->FTSR &=~(1 << EXTI_Config->EXTI_Pin.ETI_LineNumber );

	if(EXTI_Config->Trigger_case == EXTI_Trigger_Rising )
	{
		EXTI->RTSR |=(1 << EXTI_Config->EXTI_Pin.ETI_LineNumber );
	}
	else if ( EXTI_Config->Trigger_case == EXTI_Trigger_Falling )
	{
		EXTI->FTSR |=(1 << EXTI_Config->EXTI_Pin.ETI_LineNumber );
	}
	else
	{
		EXTI->RTSR |=(1 << EXTI_Config->EXTI_Pin.ETI_LineNumber );
		EXTI->FTSR |=(1 << EXTI_Config->EXTI_Pin.ETI_LineNumber );
	}

	//4 IRQ Function Coll
	GP_IRQ_CALL[EXTI_Config->EXTI_Pin.ETI_LineNumber] = EXTI_Config->P_IRQ_CALL ;

	//5 Enable VNIC and MASK

	if( EXTI_Config->IRQ_EN == EXTI_IRQ_Enable)
	{
		EXTI->IMR |=( 1 << EXTI_Config->EXTI_Pin.ETI_LineNumber );
		Enable_NVIC( EXTI_Config->EXTI_Pin.ETI_LineNumber );
	}
	else
	{
		EXTI->IMR &=~( 1 << EXTI_Config->EXTI_Pin.ETI_LineNumber );
		Disable_NVIC( EXTI_Config->EXTI_Pin.ETI_LineNumber );
	}


}




/*
 * ===============================================================
 *
 *                      API Function Definitions
 *
 * ===============================================================
 */

/**================================================================
* @Fn				-MCAL_EXTI_GPIO_Init
* @brief		  	-Initializes the EXTI [0-15] according to the specified parameters in the EXTI_Config
* 					 @ ref  EXTI_Define And @ ref  EXTI_Trigger_Define Trigger and @ ref  EXTI_IRQ_Define to enable and disable
* @param [in] 		-EXTI_Config: configuration information for the specified EXTI from 0 to 15  and GPIOA to GPIOB
* 					 take a pointer to function (this function calling at interrupt)
* @retval 			-none
* Note				-stm32f103c6 has GPIO (A--->> E)but the LQFP48 package has GPIO (A---->> D)
*/

void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t* EXTI_Config)
{

	Configuration_EXTI(EXTI_Config);
}



/**================================================================
* @Fn				-MCAL_EXTI_GPIO_DeInit
* @brief		  	-Reset all the EXTI Register
* @retval 			-none
* Note				-none
*/

void MCAL_EXTI_GPIO_DeInit(void)
{
	EXTI->EMR  = 0X00000000;
	EXTI->IMR  = 0X00000000;
	EXTI->RTSR = 0X00000000;
	EXTI->FTSR = 0X00000000;
	EXTI->SWIER= 0X00000000;
	EXTI->PR   = 0XFFFFFFFF;
	NVIC_IRQ6_EXTI0_Disable();
	NVIC_IRQ7_EXTI1_Disable();
	NVIC_IRQ8_EXTI2_Disable();
	NVIC_IRQ9_EXTI3_Disable();
	NVIC_IRQ10_EXTI4_Disable();
	NVIC_IRQ23_EXTI5_to_EXTI9_Disable();
	NVIC_IRQ40_EXTI10_to_EXTI15_Disable();
}





/**================================================================
* @Fn				-MCAL_EXTI_GPIO_Update
* @brief		  	-Initializes the EXTI [0-15] according to the specified parameters in the EXTI_Config
* 					 @ ref  EXTI_Define And @ ref  EXTI_Trigger_Define Trigger and @ ref  EXTI_IRQ_Define to enable and disable
* @param [in] 		-EXTI_Config: configuration information for the specified EXTI from 0 to 15  and GPIOA to GPIOB
* 					 take a pointer to function (this function calling at interrupt)
* @retval 			-none
* Note				-stm32f103c6 has GPIO (A--->> E)but the LQFP48 package has GPIO (A---->> D)
*/

void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t* EXTI_Config)
{
	Configuration_EXTI(EXTI_Config);
}



/*
 * ===============================================================
 *
 *                      ISR Function Definitions
 *
 * ===============================================================
 */

void EXTI0_IRQHandler (void)
{
	// Clear Pending register
	EXTI->PR |=(1<<0);
	//Call function
	GP_IRQ_CALL[0]();
}

void EXTI1_IRQHandler (void)
{
	// Clear Pending register
	EXTI->PR |=(1<<1);
	//Call function
	GP_IRQ_CALL[1]();
}

void EXTI2_IRQHandler (void)
{
	// Clear Pending register
	EXTI->PR |=(1<<2);
	//Call function
	GP_IRQ_CALL[2]();
}

void EXTI3_IRQHandler (void)
{
	// Clear Pending register
	EXTI->PR |=(1<<3);
	//Call function
	GP_IRQ_CALL[3]();
}

void EXTI4_IRQHandler (void)
{
	// Clear Pending register
	EXTI->PR |=(1<<4);
	//Call function
	GP_IRQ_CALL[4]();
}


void EXTI9_5_IRQHandler (void)
{
	if( EXTI->PR & 1<<5 )	{ EXTI->PR |=( 1 << 5 ) ;		GP_IRQ_CALL[5]() ; }
	if( EXTI->PR & 1<<6 )	{ EXTI->PR |=( 1 << 6 ) ;		GP_IRQ_CALL[6]() ; }
	if( EXTI->PR & 1<<7 )	{ EXTI->PR |=( 1 << 7 ) ;		GP_IRQ_CALL[7]() ; }
	if( EXTI->PR & 1<<8 )	{ EXTI->PR |=( 1 << 8 ) ;		GP_IRQ_CALL[8]() ; }
	if( EXTI->PR & 1<<9 )	{ EXTI->PR |=( 1 << 9 ) ;		GP_IRQ_CALL[9]() ; }
}


void EXTI15_10_IRQHandler (void)
{
	if( EXTI->PR & 1<<10 )	{ EXTI->PR |=( 1 << 10 ) ;		GP_IRQ_CALL[10]() ; }
	if( EXTI->PR & 1<<11 )	{ EXTI->PR |=( 1 << 11 ) ;		GP_IRQ_CALL[11]() ; }
	if( EXTI->PR & 1<<12 )	{ EXTI->PR |=( 1 << 12 ) ;		GP_IRQ_CALL[12]() ; }
	if( EXTI->PR & 1<<13 )	{ EXTI->PR |=( 1 << 13 ) ;		GP_IRQ_CALL[13]() ; }
	if( EXTI->PR & 1<<14 )	{ EXTI->PR |=( 1 << 14 ) ;		GP_IRQ_CALL[14]() ; }
	if( EXTI->PR & 1<<15 )	{ EXTI->PR |=( 1 << 15 ) ;		GP_IRQ_CALL[15]() ; }
}


