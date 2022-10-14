/*
 * stm32_f103c6_USART.h
 *
 *  Created on: ٠٤‏/٠٩‏/٢٠٢٢
 *  Author: Salama mohamed
 */

#ifndef INC_STM32_F103C6_USART_H_
#define INC_STM32_F103C6_USART_H_

//Include
#include "stm32f103x6.h"
#include "stm32_f103c6_RCC.h"
#include"stm32_f103c6_GPIO.h"




//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
	uint8_t MODE 			 ; 		//specified the USART (TX/RX) to be configured .
					     	 	  //this parameter must be set based on  @ ref  USART_MODE_Define

	uint8_t NUM_DATA_BIT	;	//specified the number of data bit (8or 9 ) .
								//this parameter must be set based on  @ ref USART_NUM_DATA_BIT_Define

	uint8_t NUM_STOP_BIT	;	//specified the number of stop bit ( 0.5 or 1 or 1.5 or 2 ) .
								//this parameter must be set based on  @ ref  USART_NUM_STOP_BIT_Define

	uint32_t BAUDRATE		;	//specified the baudrate  .
								//this parameter must be set based on  @ ref  USART_BAUDRATE_Define

	uint8_t PARITY			;	//specified the parity disable or enable (odd or even ) .
								//this parameter must be set based on  @ ref  USART_PARITY_Define

	uint8_t HWFLOWCTL		;	//specified the hardware flow control mode (disable or enable )  .
								//this parameter must be set based on  @ ref  USART_HWFLOWCTL_Define

	uint8_t IRQ_EN		;	//specified the interrupt (disable or enable )  .
								//this parameter must be set based on  @ ref  USART_IRQ_ENABLE_Define

	void (*P_IRQ_CALL)(void);     // set the function which will be call at IRQ happen

}USART_config_t;

enum polling_mechanism
{
	Enable ,
	Disable
};

//=========================================================================

//-----------------------------
//Macros Configuration References
//-----------------------------

// @ ref  USART_MODE_Define
/*
Bit 2 RE: Receiver enable
This bit enables the receiver. It is set and cleared by software.
0: Receiver is disabled
1: Receiver is enabled and begins searching for a start bit

Bit 3 TE: Transmitter enable
This bit enables the transmitter. It is set and cleared by software.
0: Transmitter is disabled
1: Transmitter is enabled
 */
#define USART_MODE_TX			(uint32_t)(1<<2)
#define USART_MODE_RX			(uint32_t)(1<<3)
#define USART_MODE_TX_RX		(uint32_t)(1<<2 | 1<<3 )


// @ ref USART_NUM_DATA_BIT_Define
/*
 Bit 12 M: Word length
This bit determines the word length. It is set or cleared by software.
0: 1 Start bit, 8 Data bits, n Stop bit
1: 1 Start bit, 9 Data bits, n Stop bit
 */
#define USART_NUM_DATA_BIT_8		(uint32_t)(0)
#define USART_NUM_DATA_BIT_9		(uint32_t)(1<<12)

//@ ref  USART_NUM_STOP_BIT_Define
/*
 Bits 13:12 STOP: STOP bits
These bits are used for programming the stop bits.
00: 1 Stop bit
01: 0.5 Stop bit
10: 2 Stop bits
11: 1.5 Stop bit
 */

#define USART_NUM_STOP_BIT_0_5		(uint32_t)(1<<12)
#define USART_NUM_STOP_BIT_1		(uint32_t)(0)
#define USART_NUM_STOP_BIT_1_5		(uint32_t)(3<<12)
#define USART_NUM_STOP_BIT_2		(uint32_t)(2<<12)

//  @ ref  USART_BAUDRATE_Define
#define USART_BAUDRATE_2400				2400
#define USART_BAUDRATE_9600				9600
#define USART_BAUDRATE_19200			19200
#define USART_BAUDRATE_57600			57600
#define USART_BAUDRATE_115200			115200
#define USART_BAUDRATE_230400			230400
#define USART_BAUDRATE_460800			460800
#define USART_BAUDRATE_921600			921600
#define USART_BAUDRATE_2250000			2250000
#define USART_BAUDRATE_4500000			4500000


//  @ ref  USART_PARITY_Define
/*
 Bit 10 PCE: Parity control enable
 0: Parity control disabled
 1: Parity control enabled

 Bit 9 PS: Parity selection
 0: Even parity
 1: Odd parity
 */
#define USART_PARITY_Disable			(uint32_t)(0)
#define USART_PARITY_ODD				(uint32_t)( 1<<10 | 1<<9 )
#define USART_PARITY_EVEN				(uint32_t)( 1<<10 )


// @ ref  USART_HWFLOWCTL_Define
/*
 Bit 9 CTSE: CTS enable
 0: CTS hardware flow control disabled
 1: CTS mode enabled

 Bit 8 RTSE: RTS enable
 0: RTS hardware flow control disabled
 1: RTS interrupt enabled
 */
#define USART_HWFLOWCTL_Disable				(uint32_t)(0)
#define USART_HWFLOWCTL_RTS					(uint32_t)( 1<<8 )
#define USART_HWFLOWCTL_CTS					(uint32_t)( 1<<9 )
#define USART_HWFLOWCTL_RTS_CTS				(uint32_t)( 1<<8 | 1<<9 )


// @ ref  USART_IRQ_ENABLE_Define
#define USART_IRQ_ENABLE_Disable			(uint32_t)(0)
#define USART_IRQ_ENABLE_TXE				(uint32_t)( 1<<7 )//Transmit data register empty
#define USART_IRQ_ENABLE_TC					(uint32_t)( 1<<6 )//Transmission complete
#define USART_IRQ_ENABLE_RXNE				(uint32_t)( 1<<5 )//Received data ready to be read
#define USART_IRQ_ENABLE_PE					(uint32_t)( 1<<8 )//Parity error

// Baudrate calculation
#define USARTDIV( PCLK , BAUD)				( uint32_t )( PCLK / ( 16 * BAUD ) )
#define USARTDIV_MUL100( PCLK , BAUD)		( uint32_t )( ( 25 * PCLK ) / ( 4 * BAUD ) )
#define Mantissa_MUL100( PCLK , BAUD)		( uint32_t )( USARTDIV( PCLK , BAUD) * 100 )
#define Mantissa( PCLK , BAUD)				( uint32_t )( USARTDIV( PCLK , BAUD) )
#define DIV_Fraction( PCLK , BAUD)			( uint32_t )(( USARTDIV_MUL100( PCLK , BAUD) - Mantissa_MUL100( PCLK , BAUD) ) * 100 )
#define USART_BRR_Reg( PCLK , BAUD)			( (Mantissa( PCLK , BAUD)) << 4 ) | ( ( DIV_Fraction( PCLK , BAUD) ) &0XF )
//=============================================================================

/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/
void MCAL_USART_Init( USART_TypeDef* USARTx , USART_config_t* USART_Config );
void MCAL_USART_DeInit( USART_TypeDef* USARTx );
void MCAL_USART_Set_Pin( USART_TypeDef* USARTx );
void MCAL_USART_ReceiveData( USART_TypeDef* USARTx , uint16_t* PRXBuffer , enum polling_mechanism polling_EN);
void MCAL_USART_SendData( USART_TypeDef* USARTx , uint16_t* PTXBuffer , enum polling_mechanism polling_EN);
void MCAL_USART_WAIT_TC( USART_TypeDef* USARTx );
void MCAL_USART_Send_String( USART_TypeDef* USARTx , uint8_t* PTXBuffer , enum polling_mechanism polling_EN);
void MCAL_USART_Receive_String( USART_TypeDef* USARTx , uint8_t* PRXBuffer , enum polling_mechanism polling_EN);
//===============================================================================

#endif /* INC_STM32_F103C6_USART_H_ */
