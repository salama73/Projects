/*
 * stm32_f103c6_USART.c
 *
 *  Created on: ٠٤‏/٠٩‏/٢٠٢٢
 *  Author: Salama mohamed
 */

#include"stm32_f103c6_USART.h"


/*
 * ===============================================================
 *
 *                      Generic Variable
 *
 * ===============================================================
 */
USART_config_t* g_USART_Config[3] ={ NULL , NULL ,NULL } ;

//===================================================================================


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
* @Fn				-MCAL_USART_Init
* @brief		  	-Initializes the USART [1-3] according to the specified parameters in the USART_Config
* 					 @ ref  USART_MODE_Define  and @ ref  USART_NUM_DATA_BIT_Define and @ ref  USART_NUM_STOP_BIT_Define and ....
* @param [in] 		-USART_Config: configuration information for the specified USART from 1 to 3
* 					 take a pointer to function (this function calling at interrupt)
* @param [in] 		-USARTx:  specified USARTx x=[ 1 : 3 ]
* @retval 			-none
* Note				-stm32f103c6 has USART (1---3 )
*/
void MCAL_USART_Init( USART_TypeDef* USARTx , USART_config_t* USART_Config )
{
	uint32_t PCLK , BRR ;

	// Enable clock for usartx
	 if ( USARTx == USART1 )
	 {
		 g_USART_Config[0] = USART_Config ;// configuration the USART1
		 RCC_USART1_CLK_Enable() ;
	 }
	 else if ( USARTx == USART2 )
	 {
		 g_USART_Config[1] = USART_Config ;// configuration the USART2
		 RCC_USART2_CLK_Enable() ;
	 }
	 else if ( USARTx == USART3 )
	 {
		 g_USART_Config[2] = USART_Config ;// configuration the USART3
		 RCC_USART3_CLK_Enable() ;
	 }

	 // Enable USARTx
	 USARTx->CR1 |= 1 << 13 ;

	 //Enable mode
	 USARTx->CR1 |= USART_Config->MODE ;

	 // number of data bit
	 USARTx->CR1 |= USART_Config->NUM_DATA_BIT ;

	 //set parity
	 USARTx->CR1 |= USART_Config->PARITY ;

	 // number of  stop bit
	 USARTx->CR2 |= USART_Config->NUM_STOP_BIT ;

	 // hardware flow control
	 USARTx->CR3 |= USART_Config->HWFLOWCTL ;

	 // baudrate
	 if ( USARTx == USART1 )
	 {
		 PCLK = MCAL_Get_PCLC2_FREQ() ;
	 }
	 else
	 {
		 PCLK = MCAL_Get_PCLC1_FREQ() ;
	 }
	 BRR =  USART_BRR_Reg( PCLK , USART_Config->BAUDRATE ) ;
	 USARTx->BRR = BRR ;

	 // Enable or Disable interrupt
	 if ( USART_Config->IRQ_EN != USART_IRQ_ENABLE_Disable )
	 {
		 USARTx->CR1 |= USART_Config->IRQ_EN ;

		 // en NVIC
		 if ( USARTx == USART1 )
		 {
			 NVIC_IRQ37_USART1_Enable() ;
		 }
		 else if ( USARTx == USART2 )
		 {
			 NVIC_IRQ38_USART2_Enable() ;
		 }
		 else if ( USARTx == USART3 )
		 {
			 NVIC_IRQ39_USART3_Enable() ;
		 }
	 }
}


/**================================================================
* @Fn				-MCAL_USART_DeInit
* @brief		  	-Disable clock to USARTx an Disable global interrupt
* @param [in] 		-USARTx:  specified USARTx x=[ 1 : 3 ]
* @retval 			-none
* Note				-none
*/
void MCAL_USART_DeInit( USART_TypeDef* USARTx )
{
	 if ( USARTx == USART1 )
	 {
		 NVIC_IRQ37_USART1_Disable() ;
		 RCC_USART1_CLK_Disable() ;
	 }
	 else if ( USARTx == USART2 )
	 {
		 NVIC_IRQ38_USART2_Disable() ;
		 RCC_USART2_CLK_Disable() ;
	 }
	 else if ( USARTx == USART3 )
	 {
		 NVIC_IRQ39_USART3_Disable() ;
		 RCC_USART3_CLK_Disable() ;
	 }
}


/**================================================================
* @Fn				-MCAL_USART_Set_Pin
* @brief		  	-set bit to specified USART from 1 to 3 (set pin to act as alternate-function to USARTx)
* @param [in] 		-USARTx:  specified USARTx x=[ 1 : 3 ]
* @retval 			-none
* Note				-none
*/
void MCAL_USART_Set_Pin( USART_TypeDef* USARTx )
{
	GPIO_Pinconfig_t pinconfig ;
	if( USARTx == USART1 )
	{
		//PA9--->TX
		//PA10-->RX
		//PA11-->CTS
		//PA12-->RTS
		pinconfig.pinNumber = GPIO_PIN_9 ;
		pinconfig.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP  ;
		pinconfig.GPIO_OUTPUT_Speed = GPIO_speed_10M ;
		MCAL_GPIO_Init(GPIOA, &pinconfig) ;

		pinconfig.pinNumber = GPIO_PIN_10 ;
		pinconfig.GPIO_MODE = GPIO_MODE_INPUT_AF  ;
		MCAL_GPIO_Init(GPIOA, &pinconfig) ;

		if( g_USART_Config[0]->HWFLOWCTL == USART_HWFLOWCTL_CTS || g_USART_Config[0]->HWFLOWCTL == USART_HWFLOWCTL_RTS_CTS )
		{
			pinconfig.pinNumber = GPIO_PIN_11 ;
			pinconfig.GPIO_MODE = GPIO_MODE_INPUT_FLO  ;
			MCAL_GPIO_Init(GPIOA, &pinconfig) ;
		}
		else if( g_USART_Config[0]->HWFLOWCTL == USART_HWFLOWCTL_RTS || g_USART_Config[0]->HWFLOWCTL == USART_HWFLOWCTL_RTS_CTS )
		{
			pinconfig.pinNumber = GPIO_PIN_12 ;
			pinconfig.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP  ;
			pinconfig.GPIO_OUTPUT_Speed = GPIO_speed_10M ;
			MCAL_GPIO_Init(GPIOA, &pinconfig) ;
		}
	}

	if( USARTx == USART2 )
	{
		//PA2--->TX
		//PA3-->RX
		//PA0-->CTS
		//PA1-->RTS
		pinconfig.pinNumber = GPIO_PIN_2 ;
		pinconfig.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP  ;
		pinconfig.GPIO_OUTPUT_Speed = GPIO_speed_10M ;
		MCAL_GPIO_Init(GPIOA, &pinconfig) ;

		pinconfig.pinNumber = GPIO_PIN_3 ;
		pinconfig.GPIO_MODE = GPIO_MODE_INPUT_AF  ;
		MCAL_GPIO_Init(GPIOA, &pinconfig) ;

		if( g_USART_Config[1]->HWFLOWCTL == USART_HWFLOWCTL_CTS || g_USART_Config[1]->HWFLOWCTL == USART_HWFLOWCTL_RTS_CTS )
		{
			pinconfig.pinNumber = GPIO_PIN_0 ;
			pinconfig.GPIO_MODE = GPIO_MODE_INPUT_FLO  ;
			MCAL_GPIO_Init(GPIOA, &pinconfig) ;
		}
		else if( g_USART_Config[1]->HWFLOWCTL == USART_HWFLOWCTL_RTS || g_USART_Config[1]->HWFLOWCTL == USART_HWFLOWCTL_RTS_CTS )
		{
			pinconfig.pinNumber = GPIO_PIN_1 ;
			pinconfig.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP  ;
			pinconfig.GPIO_OUTPUT_Speed = GPIO_speed_10M ;
			MCAL_GPIO_Init(GPIOA, &pinconfig) ;
		}
	}

	if( USARTx == USART3 )
	{
		//PB10--->TX
		//PB11-->RX
		//PB13-->CTS
		//PB14-->RTS
		pinconfig.pinNumber = GPIO_PIN_10 ;
		pinconfig.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP  ;
		pinconfig.GPIO_OUTPUT_Speed = GPIO_speed_10M ;
		MCAL_GPIO_Init(GPIOB, &pinconfig) ;

		pinconfig.pinNumber = GPIO_PIN_11 ;
		pinconfig.GPIO_MODE = GPIO_MODE_INPUT_AF  ;
		MCAL_GPIO_Init(GPIOB, &pinconfig) ;

		if( g_USART_Config[2]->HWFLOWCTL == USART_HWFLOWCTL_CTS || g_USART_Config[2]->HWFLOWCTL == USART_HWFLOWCTL_RTS_CTS )
		{
			pinconfig.pinNumber = GPIO_PIN_13 ;
			pinconfig.GPIO_MODE = GPIO_MODE_INPUT_FLO  ;
			MCAL_GPIO_Init(GPIOB, &pinconfig) ;
		}
		else if( g_USART_Config[2]->HWFLOWCTL == USART_HWFLOWCTL_RTS || g_USART_Config[2]->HWFLOWCTL == USART_HWFLOWCTL_RTS_CTS )
		{
			pinconfig.pinNumber = GPIO_PIN_14 ;
			pinconfig.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP  ;
			pinconfig.GPIO_OUTPUT_Speed = GPIO_speed_10M ;
			MCAL_GPIO_Init(GPIOB, &pinconfig) ;
		}
	}
}


/**================================================================
* @Fn				-MCAL_USART_Send_String
* @brief		  	-send string by USARTx data you can used polling_mechanism or interrupt
* @param [in] 		-USARTx:  specified USARTx x=[ 1 : 3 ]
* @param [in] 		-polling_mechanism:  Disable or Enable polling_mechanism
* @param [in] 		-PTXBuffer: pointer to buffer to send data
* @retval 			-none
* Note				-to finish the sending process you must send #
*/
void MCAL_USART_Send_String( USART_TypeDef* USARTx , uint8_t* PTXBuffer , enum polling_mechanism polling_EN)
{
	//usart1
	if(  USARTx == USART1 )
	{

		if (g_USART_Config[0]->NUM_DATA_BIT == USART_NUM_DATA_BIT_8 )
		{
			while( *PTXBuffer != '#' )
			{
				MCAL_USART_SendData(USARTx,(uint16_t*)PTXBuffer, polling_EN);
				PTXBuffer++;
			}
		}
	}
	//usart2
	if(  USARTx == USART2 )
	{

		if (g_USART_Config[1]->NUM_DATA_BIT == USART_NUM_DATA_BIT_8 )
		{
			while( *PTXBuffer != '#' )
			{
				MCAL_USART_SendData(USARTx, (uint16_t*)PTXBuffer, polling_EN);
				PTXBuffer++;
			}
		}
	}
	//usart3
	if(  USARTx == USART3 )
	{

		if (g_USART_Config[2]->NUM_DATA_BIT == USART_NUM_DATA_BIT_8 )
		{
			while( *PTXBuffer != '#' )
			{
				MCAL_USART_SendData(USARTx, (uint16_t*)PTXBuffer, polling_EN);
				PTXBuffer++;
			}
		}
	}
}


/**================================================================
* @Fn				-MCAL_USART_Receive_String
* @brief		  	-Receive data by USARTx data can be 8 or 9 bit and you can used polling_mechanism or interrupt
* @param [in] 		-USARTx:  specified USARTx x=[ 1 : 3 ]
* @param [in] 		-polling_mechanism:  Disable or Enable polling_mechanism
* @param [out] 		-PRXBuffer: pointer to buffer to Receive data
* @retval 			-none
* Note				-send process terminates when # is reached
*/
void MCAL_USART_Receive_String( USART_TypeDef* USARTx , uint8_t* PRXBuffer , enum polling_mechanism polling_EN)
{
	//usart1
	if(  USARTx == USART1 )
	{

		if (g_USART_Config[0]->NUM_DATA_BIT == USART_NUM_DATA_BIT_8 )
		{
			while( *(PRXBuffer-1) != '#' )
			{
				MCAL_USART_ReceiveData(USARTx, PRXBuffer, polling_EN);
				PRXBuffer++;
			}
		}
	}
	//usart2
	if(  USARTx == USART2 )
	{

		if (g_USART_Config[1]->NUM_DATA_BIT == USART_NUM_DATA_BIT_8 )
		{
			while( *PRXBuffer != '#' )
			{
				MCAL_USART_ReceiveData(USARTx, PRXBuffer, polling_EN);
				PRXBuffer++;
			}
		}
	}
	//usart3
	if(  USARTx == USART3 )
	{

		if (g_USART_Config[2]->NUM_DATA_BIT == USART_NUM_DATA_BIT_8 )
		{
			while( *PRXBuffer != '#' )
			{
				MCAL_USART_ReceiveData(USARTx, PRXBuffer, polling_EN);
				PRXBuffer++;
			}
		}
	}
}



/**================================================================
* @Fn				-MCAL_USART_SendData
* @brief		  	-send data by USARTx data can be 8 or 9 bit and you can used polling_mechanism or interrupt
* @param [in] 		-USARTx:  specified USARTx x=[ 1 : 3 ]
* @param [in] 		-polling_mechanism:  Disable or Enable polling_mechanism
* @param [in] 		-PTXBuffer: pointer to buffer to send data
* @retval 			-none
* Note				-stm32f103c6 has USART (1---3 )
*/
void MCAL_USART_SendData( USART_TypeDef* USARTx , uint16_t* PTXBuffer , enum polling_mechanism polling_EN)
{
	if ( polling_EN == Enable )
		while( ! ( USARTx->SR & 1<<7 ) ) ;

	if( USARTx == USART1 )
	{
		if ( g_USART_Config[0]->NUM_DATA_BIT == USART_NUM_DATA_BIT_9 )
		{
			USARTx->DR = ( *PTXBuffer & (uint16_t)0x01FF ) ;
		}
		else
		{
			USARTx->DR = ( *PTXBuffer & (uint8_t)0xFF ) ;
		}
	}
	if( USARTx == USART2 )
	{
		if ( g_USART_Config[1]->NUM_DATA_BIT == USART_NUM_DATA_BIT_9 )
		{
			USARTx->DR = ( *PTXBuffer & (uint16_t)0x01FF ) ;
		}
		else
		{
			USARTx->DR = ( *PTXBuffer & (uint8_t)0xFF ) ;
		}
	}
	if( USARTx == USART3 )
	{
		if ( g_USART_Config[2]->NUM_DATA_BIT == USART_NUM_DATA_BIT_9 )
		{
			USARTx->DR = ( *PTXBuffer & (uint16_t)0x01FF ) ;
		}
		else
		{
			USARTx->DR = ( *PTXBuffer & (uint8_t)0xFF ) ;
		}
	}

}



/**================================================================
* @Fn				-MCAL_USART_WAIT_TC
* @brief		  	- wait till completed transmit data
* @param [in] 		-USARTx:  specified USARTx x=[ 1 : 3 ]
* @retval 			-none
* Note				-none
*/
void MCAL_USART_WAIT_TC( USART_TypeDef* USARTx )
{
	// wait to complied transmit date
	while( ! ( USARTx->SR & 1<<6 ) ) ;
}



/**================================================================
* @Fn				-MCAL_USART_ReceiveData
* @brief		  	-send data by USARTx data can be 8 or 9 bit and you can used polling_mechanism or interrupt
* @param [in] 		-USARTx:  specified USARTx x=[ 1 : 3 ]
* @param [in] 		-polling_mechanism:  Disable or Enable polling_mechanism
* @param [out] 		-PRXBuffer: pointer to buffer to Receive data
* @retval 			-none
* Note				-stm32f103c6 has USART (1---3 )
*/
void MCAL_USART_ReceiveData( USART_TypeDef* USARTx , uint16_t* PRXBuffer , enum polling_mechanism polling_EN)
{
	// at parity is enable the MSB of data Replace whit parity bit
	if ( polling_EN == Enable )
		while( ! ( USARTx->SR & 1<<5 ) ) ;
	if( USARTx == USART1 )
	{
		if ( g_USART_Config[0]->NUM_DATA_BIT == USART_NUM_DATA_BIT_9 )
		{
			if ( g_USART_Config[0]->PARITY == USART_PARITY_Disable )
			{
				*((uint16_t*)PRXBuffer) = USARTx->DR ;
			}
			else
			{
				*((uint16_t*)PRXBuffer) = ( USARTx->DR & (uint8_t)0xff);
			}
		}
		else
		{
			if ( g_USART_Config[0]->PARITY == USART_PARITY_Disable )
			{
				*((uint16_t*)PRXBuffer) = ( USARTx->DR & (uint8_t)0xff);
			}
			else
			{
				*((uint16_t*)PRXBuffer) = ( USARTx->DR & (uint8_t)0x7f);
			}
		}
	}
	if( USARTx == USART2 )
	{
		if ( g_USART_Config[1]->NUM_DATA_BIT == USART_NUM_DATA_BIT_9 )
		{
			if ( g_USART_Config[1]->PARITY == USART_PARITY_Disable )
			{
				*((uint16_t*)PRXBuffer) = USARTx->DR ;
			}
			else
			{
				*((uint16_t*)PRXBuffer) = ( USARTx->DR & (uint8_t)0xff);
			}
		}
		else
		{
			if ( g_USART_Config[1]->PARITY == USART_PARITY_Disable )
			{
				*((uint16_t*)PRXBuffer) = ( USARTx->DR & (uint8_t)0xff);
			}
			else
			{
				*((uint16_t*)PRXBuffer) = ( USARTx->DR & (uint8_t)0x7f);
			}
		}
	}
	if( USARTx == USART3 )
	{
		if ( g_USART_Config[2]->NUM_DATA_BIT == USART_NUM_DATA_BIT_9 )
		{
			if ( g_USART_Config[2]->PARITY == USART_PARITY_Disable )
			{
				*((uint16_t*)PRXBuffer) = USARTx->DR ;
			}
			else
			{
				*((uint16_t*)PRXBuffer) = ( USARTx->DR & (uint8_t)0xff);
			}
		}
		else
		{
			if ( g_USART_Config[2]->PARITY == USART_PARITY_Disable )
			{
				*((uint16_t*)PRXBuffer) = ( USARTx->DR & (uint8_t)0xff);
			}
			else
			{
				*((uint16_t*)PRXBuffer) = ( USARTx->DR & (uint8_t)0x7f);
			}
		}
	}

}

//============================================================================================

/*
 * ===============================================================
 *
 *                      ISR Function Definitions
 *
 * ===============================================================
 */
void USART1_IRQHandler (void)
{
	g_USART_Config[0]->P_IRQ_CALL() ;
}

void USART2_IRQHandler (void)
{
	g_USART_Config[1]->P_IRQ_CALL() ;
}

void USART3_IRQHandler (void)
{
	g_USART_Config[2]->P_IRQ_CALL() ;
}
//=============================================================================================
