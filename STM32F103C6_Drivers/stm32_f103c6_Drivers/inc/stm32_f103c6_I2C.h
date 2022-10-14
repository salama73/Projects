/*
 * stm32_f103c6_I2C.h
 *  Created on: 20/9/2022
 *  Author: Salama mohamed
 */

#ifndef INC_STM32_F103C6_I2C_H_
#define INC_STM32_F103C6_I2C_H_


//Include
#include "stm32f103x6.h"
#include"stm32_f103c6_GPIO.h"
#include "stm32_f103c6_RCC.h"


//-----------------------------
//User type definitions (enum)
//-----------------------------
typedef enum
{
	I2C_EV_STOP,
	I2C_EV_ADDR_Matched,
	I2C_EV_DATA_REQ,
	I2C_EV_DATA_RCV
}Slave_State;

typedef enum
{
	WithStop,
	WithoutStop
}Stop_Stute;

typedef enum
{
	Start,
	RepeatedSart
}Repeated_Start;

typedef enum
{
	RESET,
	SET
}FlagStatus;

typedef enum
{
	I2C_Busy,
	EV5     , // 1: Start condition generated
	EV6 	, // 1: Received address matched.
	EV8_1	, // 1: Data register empty
	EV8_2	, // 1: Data byte transfer succeeded
	EV7 	, // 1: Data register not empty
}Status;

typedef enum
{
	Transmitter,
	Recieve
}I2C_Direction;

//============================================================

//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
	uint16_t Own_Address 			;
	uint16_t Dual_Address_Enable 	;	//specified the Dual Address Enable or Disable
										//this parameter must be set based on  @ ref  I2C_Dual_Address_Enable_Define
	uint16_t Dual_Address 			;
}I2C_Address_config_t;


typedef struct
{
	uint32_t MODE_Speed 			; 	 //specified the I2C Speed  (Fm, up to 400 kHz) or (Sm, up to 100 kHz) a.
										 //this parameter must be set based on  @ ref  I2C_Speed_MODE_Define

	uint16_t NUM_Address_BIT		;	 //specified the number of  addressING bit (7 or 10 ) .
										 //this parameter must be set based on  @ ref I2C_NUM_Address_BIT_Define
	I2C_Address_config_t Address	;

	uint16_t IRQ_EN					;	 //specified the interrupt (disable or enable )  .
										 //this parameter must be set based on  @ ref  I2C_IRQ_ENABLE_Define

	uint32_t Stretch_Mode			;	 //specified the Stretch (disable or enable )  .
	 	 	 	 	 	 	 	 	 	 //this parameter must be set based on  @ ref  I2C_Stretch_Mode_Define

	uint16_t ACK_Control			;	 //specified the ACK (disable or enable )  .
										 //this parameter must be set based on  @ ref  I2C_ACK_Control_Define

	void (*P_IRQ_CALL)(Slave_State state)			;    // set the function which will be call at IRQ happen

}I2C_config_t;

//===================================================
//=========================================================================

//-----------------------------
//Macros Configuration References
//-----------------------------

//@ ref  I2C_Speed_MODE_Define
#define I2C_Speed_MODE_FM			0
#define I2C_Speed_MODE_SM_100		(100000U)

/*
at 7_address mode address is from bit 1 to 7 ;
at 10_address mode address is from bit 0 to 9 ;
 */
//@ ref I2C_NUM_Address_BIT_Define
#define I2C_NUM_Address_BIT_7						(uint16_t)(~(1<<15))
#define I2C_NUM_Address_BIT_10						(uint16_t)(1<<15)

// @ ref  I2C_IRQ_ENABLE_Define
#define I2C_IRQ_ENABLE_Disable 						(uint16_t)(~(7<<5))
#define I2C_IRQ_ENABLE_I2C_EV						(uint16_t)(1<<9)
#define I2C_IRQ_ENABLE_I2C_ER						(uint16_t)(1<<8)

/*
Bit 0 ENDUAL: Dual addressing mode enable
0: Only OAR1 is recognized in 7-bit addressing mode
1: Both OAR1 and OAR2 are recognized in 7-bit addressing mode
 */
// @ ref  I2C_Dual_Adress_Enable_Define
#define I2C_Dual_Adress_Enable_Enable				(uint16_t)(~(1<<0))
#define I2C_Dual_Adress_Enable_Disable				(uint16_t)(1<<0)


//@ ref  I2C_ACK_Control_Define
#define I2C_ACK_Control_Enable						(uint16_t)(1<<10)
#define I2C_ACK_Control_Disable						(uint16_t)(~(1<<10))

/*
This bit is used to disable clock stretching in slave mode when ADDR or BTF flag is set, until
it is reset by software.
0: Clock stretching enabled
1: Clock stretching disabled
 */
//@ ref  I2C_Stretch_Mode_Define
#define I2C_Stretch_Mode_Enable						(uint16_t)(~(1<<7))
#define I2C_Stretch_Mode_Disable					(uint16_t)(1<<7)
/*
* ===============================================
* APIs Supported by "MCAL I2C DRIVER"
* ===============================================
*/

void MCAL_I2C_Init(I2C_TypeDef* I2Cx, I2C_config_t* I2C_Config);
void MCAL_I2C_DInit(I2C_TypeDef* I2Cx);
void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef* I2Cx);
void MCAL_I2C_Master_TX(I2C_TypeDef *I2Cx , uint16_t Address , uint8_t* PTXBuffer , uint32_t DataLen , Stop_Stute Stop , Repeated_Start Start);
void MCAL_I2C_Master_RX(I2C_TypeDef *I2Cx , uint16_t Address , uint8_t* PRXBuffer , uint32_t DataLen , Stop_Stute Stop , Repeated_Start Start);
uint8_t MCAL_I2C_Slave_RX(I2C_TypeDef *I2Cx );
void MCAL_I2C_Slave_TX(I2C_TypeDef *I2Cx ,uint8_t PTXBuffer);

#endif /* INC_STM32_F103C6_RCC_H_ */
