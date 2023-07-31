/*
 * I2C_Driver.h
 *
 * Created: 9/25/2022 3:18:02 PM
 *  Author: salama
 */ 


#ifndef I2C_DRIVER_H_
#define I2C_DRIVER_H_

//Include
#include "Atmega32.h"
#include "GPIO_Driver.h"

//============================================================


//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
	uint8_t Own_Address 				;	// slave address
	
	uint8_t Speed_MODE			 		; 	//specified the I2C Speed  up to 400 khz.
											//this parameter must be set based on  @ ref  I2C_Speed_MODE_Define

	uint8_t IRQ_EN						;	//specified the interrupt (disable or enable )  .
											//this parameter must be set based on  @ ref  I2C_IRQ_ENABLE_Define
																																	
	uint8_t Prescaler					;	//These bits can be read and written, and control the bit rate prescaler .
											//this parameter must be set based on  @ ref  I2C_Prescaler_Define								

	void (*P_IRQ_CALL)()				;   // set the function which will be call at IRQ happen

}I2C_config_t;

typedef enum
{
	Start,
	RepeatedSart
}Repeated_Start;

typedef enum
{
	TWINT,
	START_Transmitted	,
	SLA_W_Transmitted   ,
	SLA_R_Transmitted   ,
	M_DATA_Transmitted	,
	SLA_W_Received		,
	SLA_R_Received		,
	S_DATA_Received		,
	S_DATA_Transmitted	,
	M_DATA_Received		,
}Status;

typedef enum
{
	RESET,
	SET
}FlagStatus;

typedef enum
{
	With_Stop,
	Without_Stop
}stop_cmd;

//=========================================================================

//-----------------------------
//Macros Configuration References
//-----------------------------

//@ ref  I2C_Speed_MODE_Define
#define I2C_Speed_MODE_50							(50000U)
#define I2C_Speed_MODE_100							(100000U)
#define I2C_Speed_MODE_150							(150000U)
#define I2C_Speed_MODE_200							(200000U)

// @ ref  I2C_IRQ_ENABLE_Define
#define I2C_IRQ_ENABLE_Disable 						(uint8_t)~(1<<0)
#define I2C_IRQ_ENABLE_Enable						(uint8_t)(1<<0)

//@ ref  I2C_Prescaler_Define	
#define I2C_Prescaler_1								1
#define I2C_Prescaler_4								4
#define I2C_Prescaler_16							16
#define I2C_Prescaler_64							64

/*
* ===============================================
* APIs Supported by "MCAL I2C DRIVER"
* ===============================================
*/

void MCAL_I2C_Init(I2C_config_t* I2C_Config);

void MCAL_I2C_DInit(void);

void MCAL_I2C_Master_TX( uint8_t Address , uint8_t* PTXBuffer , uint8_t Datalen , stop_cmd Stop) ;

void MCAL_I2C_Master_RX( uint8_t Address , uint8_t* PRXBuffer , uint8_t Dataln );

void MCAL_I2C_Slave_TX( uint8_t PTXBuffer  ) ;

uint8_t MCAL_I2C_Slave_RX( void) ;

FlagStatus Get_flag_stutus(  Status flag );

void I2C_Generate_Start( void );

void I2C_Generate_Stop(void );

#endif /* I2C_DRIVER_H_ */