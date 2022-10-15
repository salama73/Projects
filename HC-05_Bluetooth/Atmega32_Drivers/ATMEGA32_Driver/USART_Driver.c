/*
 * USART_Driver.c
 *
 * Created: 05/09/2022 09:45:17 م
 *  Author: salama mohamed
 */ 

#include "USART_Driver.h"



/*
 * ===============================================================
 *
 *                      Generic Variable
 *
 * ===============================================================
 */
USART_config_t* g_USART_Config = NULL ;

void (*GPU_IRQ_CALL[3])(void);
//===================================================================================


/*
 * ===============================================================
 *
 *                      API Function Definitions
 *
 * ===============================================================
 */


/**================================================================
* @Fn				-MCAL_USART_Init
* @brief		  	-Initializes the USART  according to the specified parameters in the USART_Config
* 					 @ ref  USART_MODE_Define  and @ ref  USART_NUM_DATA_BIT_Define and @ ref  USART_NUM_STOP_BIT_Define and ....
* @param [in] 		-USART_Config: configuration information for the  USART 
* 					 take a pointer to function (this function calling at interrupt)
* @retval 			-none
* Note				-none
*/
void MCAL_USART_Init( USART_config_t* USART_Config )
{
	
	uint16_t  BRR ;
	g_USART_Config = USART_Config ;

	//set Communication_MODE (Asynchronous Normal Mode or Asynchronous Double Speed Mode or Synchronous Master Mode or Slave Synchronous mode)
	if ( USART_Config->Communication_MODE == USART_Communication_MODE_synchronous_Master || USART_Config->Communication_MODE == USART_Communication_MODE_synchronous_Slave )
	{
		UCSRC |= ( 1<<7 ) ;  //This bit selects between accessing the UCSRC or the UBRRH Register. It is read as one when reading UCSRC.
		UCSRC |= 1<<6 ;
		//Clock_Polarity
		if( USART_Config->Clock_Polarity == USART_Clock_Polarity_Trans_Falling )
		{
			UCSRC |= ( 1<<7 ) ;  //This bit selects between accessing the UCSRC or the UBRRH Register. It is read as one when reading UCSRC.
			UCSRC |= USART_Config->Clock_Polarity ;
		}
		else if( USART_Config->Clock_Polarity == USART_Clock_Polarity_Trans_Rising )
		{
			UCSRC |= ( 1<<7 ) ; //This bit selects between accessing the UCSRC or the UBRRH Register. It is read as one when reading UCSRC.
			UCSRC &= USART_Config->Clock_Polarity ;
		}
		// calculate  baudrate 
		BRR= ( ((float)(F_CPU))/ ( 2.0 * USART_Config->BAUDRATE) ) - 0.5 ;
	}
	else if( USART_Config->Communication_MODE == USART_Communication_MODE_Asynchronous_Double_Speed)
	{
		UCSRC |= ( 1<<7 ) ; //This bit selects between accessing the UCSRC or the UBRRH Register. It is read as one when reading UCSRC.
		UCSRC &= ~( 1<<6 ) ;
		USART->UCSRA |= 1<<1 ;
		// calculate  baudrate 
		BRR= ( ((float)(F_CPU))/ ( 8.0 * USART_Config->BAUDRATE) ) - 0.5 ;
	}
	else
	{	UCSRC |= ( 1<<7 ) ; //This bit selects between accessing the UCSRC or the UBRRH Register. It is read as one when reading UCSRC.
		UCSRC &= ~( 1<<6 ) ;
		USART->UCSRA &= ~(1<<1) ;
		// calculate  baudrate 
		BRR= ( ((float)(F_CPU))/ ( 16.0 * USART_Config->BAUDRATE) ) - 0.5 ;
	}
	//set number of date from 5 to 9
	switch( USART_Config->NUM_DATA_BIT )
	{
		case USART_NUM_DATA_BIT_5 :
		{
			USART->UCSRB &=~( 1 << 2 )	;
			UCSRC |= ( 1<<7 ) ; //This bit selects between accessing the UCSRC or the UBRRH Register. It is read as one when reading UCSRC.
			UCSRC &= ~( 3 << 1 ) ;
			break;
		}
		case USART_NUM_DATA_BIT_6 :
		{
			USART->UCSRB &=~( 1 << 2 )	;
			//clear 2 bit 
			UCSRC |= ( 1<<7 ) ; //This bit selects between accessing the UCSRC or the UBRRH Register. It is read as one when reading UCSRC.
			UCSRC &= ~( 3 << 1 ) ;	
			UCSRC |= ( 1 << 1 ) ;
			break;
		}
		case USART_NUM_DATA_BIT_7 :
		{
			USART->UCSRB &=~( 1 << 2 )	;
			//clear 2 bit
			UCSRC |= ( 1<<7 ) ; //This bit selects between accessing the UCSRC or the UBRRH Register. It is read as one when reading UCSRC.
			UCSRC &= ~( 3 << 1 ) ;
			UCSRC |= ( 2 << 1 ) ;		
			break;
		}
		case USART_NUM_DATA_BIT_8 :
		{
			USART->UCSRB &=~( 1 << 2 )	;
			UCSRC |= ( 1<<7 ) ; //This bit selects between accessing the UCSRC or the UBRRH Register. It is read as one when reading UCSRC.
			UCSRC |= ( 0b11 << 1 ) ;				
			break;
		}
		case USART_NUM_DATA_BIT_9 :
		{
			USART->UCSRB |=( 1 << 2 )	;
			UCSRC |= ( 1<<7 ) ; //This bit selects between accessing the UCSRC or the UBRRH Register. It is read as one when reading UCSRC.
			UCSRC |= ( 0b11 << 1 ) ;					
			break;
		}
		default:
			break;
	}
	//NUM_STOP_BIT
	switch( USART_Config->NUM_STOP_BIT )
	{
		case USART_NUM_STOP_BIT_1 :
		{
			UCSRC |= ( 1<<7 ) ; //This bit selects between accessing the UCSRC or the UBRRH Register. It is read as one when reading UCSRC.
			UCSRC &= USART_Config->NUM_STOP_BIT ;
			break;
		}
		case USART_NUM_STOP_BIT_2 :
		{
			UCSRC |= ( 1<<7 ) ; //This bit selects between accessing the UCSRC or the UBRRH Register. It is read as one when reading UCSRC.
			UCSRC |= USART_Config->NUM_STOP_BIT ;
			break;
		}
		default:
		break;		
	}
	//Set parity
	switch( USART_Config->PARITY )
	{
		case USART_PARITY_Disable :
		{
			UCSRC |= ( 1<<7 ) ; //This bit selects between accessing the UCSRC or the UBRRH Register. It is read as one when reading UCSRC.
			UCSRC &= USART_Config->PARITY ;
			break;
		}
		case USART_PARITY_Even_Parity :
		{
			UCSRC |= ( 1<<7 ) ; //This bit selects between accessing the UCSRC or the UBRRH Register. It is read as one when reading UCSRC.
			UCSRC |= USART_Config->PARITY ;
			break;
		}
		case USART_PARITY_Odd_Parity :
		{
			UCSRC |= ( 1<<7 ) ; //This bit selects between accessing the UCSRC or the UBRRH Register. It is read as one when reading UCSRC.
			UCSRC |= USART_Config->PARITY ;
			break;
		}
		default:
		break;		
	}
	//set  baudrate 
	UBRRH &=~(1<<7) ;//This bit selects between accessing the UCSRC or the UBRRH Register. It is read as ZERO when reading UBRRH.
	UBRRH = ( BRR >> 8) ;
	USART->UBRRL = (uint8_t)BRR ;
	//Set IRQ_EN
	switch( USART_Config->IRQ_EN )
	{
		case USART_IRQ_ENABLE_Disable :
		{
			USART_INT_RX_Disable() ;
			USART_INT_TX_Disable() ;
			USART_INT_UDR_Disable();
			EXTI_GLOBAL_Disable()  ;
			break;
		}
		case USART_IRQ_ENABLE_TX :
		{
			GPU_IRQ_CALL[0]=USART_Config->P_IRQ_CALL ;
			USART_INT_TX_Enable() ;
			EXTI_GLOBAL_Enable()  ;
			break;
		}
		case USART_IRQ_ENABLE_UDR :
		{
			GPU_IRQ_CALL[1]=USART_Config->P_IRQ_CALL ;
			USART_INT_UDR_Enable() ;
			EXTI_GLOBAL_Enable()  ;
			break;
		}
		case USART_IRQ_ENABLE_RX :
		{
			GPU_IRQ_CALL[2]=USART_Config->P_IRQ_CALL ;
			USART_INT_RX_Enable() ;
			EXTI_GLOBAL_Enable()  ;
			break;
		}
		default:
		break;		
	}

	// set mode RX or TX or TX/RX
	USART->UCSRB |= USART_Config->MODE ;
	
	GPIO_Pinconfig_t pinconfig ;
	if( g_USART_Config->Communication_MODE == USART_Communication_MODE_synchronous_Master )
	{
		//master
		// Set XCK
		pinconfig.pinNumber = GPIO_PIN_0 ;
		pinconfig.GPIO_MODE = GPIO_MODE_OUTPUT ;
		MCAL_GPIO_Init(GPIOB , &pinconfig ) ;
	}
	else if( g_USART_Config->Communication_MODE == USART_Communication_MODE_synchronous_Slave )
	{
		//Slave
		// Set XCK
		pinconfig.pinNumber = GPIO_PIN_0 ;
		pinconfig.GPIO_MODE = GPIO_MODE_INPUT_PU ;
		MCAL_GPIO_Init(GPIOB , &pinconfig ) ;
	}
}



/**================================================================
* @Fn				-MCAL_USART_ReceiveData
* @brief		  	-send data by USART data can be 5 to 9 bit and you can used polling_mechanism or interrupt non polling
* @param [in] 		-polling_mechanism:  Disable or Enable polling_mechanism
* @param [out] 		-PRXBuffer: pointer to buffer to Receive data
* @retval 			-none
* Note				-none
*/
void MCAL_USART_ReceiveData(  uint16_t* PRXBuffer , enum polling_mechanism polling_EN)
{
	
	if ( polling_EN == Enable )
	{
		
		while( ! ( USART->UCSRA & 1<<7 ) ) ;
		if ( g_USART_Config->NUM_DATA_BIT == USART_NUM_DATA_BIT_9 )
		{
				*(PRXBuffer) = ((( USART->UCSRB >> 1) & 0X01 ) << 8 ) ;
		}
	
		*((uint16_t*)PRXBuffer) = ( USART->UDR & (uint8_t)0xff);
	}
	// non block mode 
	else
	{
		if( ( USART->UCSRA & 1<<7 ) )
		{
			if ( g_USART_Config->NUM_DATA_BIT == USART_NUM_DATA_BIT_9 )
			{
				*(PRXBuffer) = ((( USART->UCSRB >> 1) & 0X01 ) << 8 ) ;
			}
					
			*((uint16_t*)PRXBuffer) = ( USART->UDR & (uint8_t)0xff);
		}
	}
}


/**================================================================
* @Fn				-MCAL_USART_SendData
* @brief		  	-send data by USART data can be 5 to 9 bit and you can used polling_mechanism or interrupt or non polling
* @param [in] 		-polling_mechanism:  Disable or Enable polling_mechanism
* @param [in] 		-PTXBuffer: pointer to buffer to send data
* @retval 			-none
* Note				-none
*/
void MCAL_USART_SendData(  uint16_t* PTXBuffer , enum polling_mechanism polling_EN)
{
	if ( polling_EN == Enable )
	{
		while( ! ( USART->UCSRA & 1<<5 ) ) ;
		if ( g_USART_Config->NUM_DATA_BIT == USART_NUM_DATA_BIT_9 )
		{
			USART->UCSRB &=~(1<<0);
			if( *PTXBuffer & 0X0100 )
			{
				USART->UCSRB |=1<<0;
			}
		}
			USART->UDR = ( *PTXBuffer & (uint8_t)0xFF ) ;
	}
	// non block mode 
	else
	{
		if ( ( USART->UCSRA & 1<<5 ) )
		{
			if ( g_USART_Config->NUM_DATA_BIT == USART_NUM_DATA_BIT_9 )
			{
				USART->UCSRB &=~(1<<0);
				if( *PTXBuffer & 0X0100 )
				{
					USART->UCSRB |=1<<0;
				}
			}
			USART->UDR = ( *PTXBuffer & (uint8_t)0xFF ) ;
		}
	}
}


/**================================================================
* @Fn				-MCAL_USART_Send_String
* @brief		  	-send string by USART data you can used polling_mechanism or interrupt or none polling 
* @param [in] 		-polling_mechanism:  Disable or Enable polling_mechanism
* @param [in] 		-PTXBuffer: pointer to buffer to send data
* @retval 			-none
* Note				-to finish the sending process you must send #
*/
void MCAL_USART_Send_String(  uint8_t* PTXBuffer , enum polling_mechanism polling_EN)
{

	if (g_USART_Config->NUM_DATA_BIT == USART_NUM_DATA_BIT_8 )
	{
		while( *PTXBuffer != '#' )
		{
			MCAL_USART_SendData((uint16_t*)PTXBuffer, polling_EN);
			PTXBuffer++;
		}
	}
}


/**================================================================
* @Fn				-MCAL_USART_Receive_String
* @brief		  	-Receive data by USART data can be 5 to 9 bit and you can used polling_mechanism or interrupt or non polling
* @param [in] 		-polling_mechanism:  Disable or Enable polling_mechanism
* @param [out] 		-PRXBuffer: pointer to buffer to Receive data
* @retval 			-none
* Note				-send process terminates when # is reached
*/
void MCAL_USART_Receive_String( uint8_t* PRXBuffer , enum polling_mechanism polling_EN)
{
	if (g_USART_Config->NUM_DATA_BIT == USART_NUM_DATA_BIT_8 )
	{
		while( *(PRXBuffer-1) != '#' )
		{
			MCAL_USART_ReceiveData( PRXBuffer, polling_EN);
			PRXBuffer++;
		}
	}
}



/**================================================================
* @Fn				-MCAL_USART_DeInit
* @brief		  	-Disable clock to USARTx an Disable global interrupt and clear register
* @retval 			-none
* Note				-none
*/
void MCAL_USART_DeInit( void )
{
	USART_INT_RX_Disable() ;
	USART_INT_TX_Disable() ;
	USART_INT_UDR_Disable();
	EXTI_GLOBAL_Disable()  ;
	USART->UBRRL = 0 ;
	USART->UCSRB = 0 ;
	UCSRC = 0b10000110;
	UBRRH = 0;
	USART->UCSRA &=~(1<<1)	;
}

//=========================================================================================================

/*
 * ===============================================================
 *
 *                      ISR Function Definitions
 *
 * ===============================================================
 */
void __vector_13 (void) __attribute__((signal));
void __vector_13 (void)
{
	//Call function
	GPU_IRQ_CALL[2]();
}

void __vector_14 (void) __attribute__((signal));
void __vector_14 (void)
{
	//Call function
	GPU_IRQ_CALL[1]();
}

void __vector_15 (void) __attribute__((signal));
void __vector_15 (void)
{
	//Call function
	GPU_IRQ_CALL[0]();
}

