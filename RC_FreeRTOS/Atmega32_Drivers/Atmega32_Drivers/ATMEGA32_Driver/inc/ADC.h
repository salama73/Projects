/*
 * ADC.h
 *
 * Created: 12/2/2022 10:10:17 PM
 *  Author: vip
 */ 


#ifndef ADC_H_
#define ADC_H_

//Include
#include "Atmega32.h"
#include "GPIO_Driver.h"

//============================================================

//-----------------------------
//User type definitions (structures)
//-----------------------------

enum NUM_CH
{
	CH0=0,
	CH1,
	CH2,
	CH3,
	CH4,
	CH5,
	CH6,
	CH7
	
};

typedef struct
{
/*	uint8_t MODE 						; 	//Select between Single Ended Input or  Differential Input
											//this parameter must be set based on  @ ref  ADC_MODE_Define
*/
	uint8_t Voltage_Reference 			; 	//These bits select the voltage reference for the ADC,
											//this parameter must be set based on  @ ref  ADC_Voltage_Reference_Define
	
	uint8_t Prescaler 					; 	//These bits determine the division factor between the XTAL frequency and the input clock to the ADC .
											//this parameter must be set based on  @ ref  ADC_Prescaler_Define

	uint8_t IRQ_EN						;	//specified the interrupt (disable or enable )  .
											//this parameter must be set based on  @ ref  ADC_IRQ_ENABLE_Define

	void (*P_IRQ_CALL)(void)			;	// set the function which will be call at IRQ happen

}ADC_config_t;


//=============================================================

//-----------------------------
//Macros Configuration References
//-----------------------------


// @ ref ADC_Voltage_Reference_Define

#define ADC_Voltage_Reference_AREF			(uint8_t)(0)
#define ADC_Voltage_Reference_AVCC			(uint8_t)(1<<6)
#define ADC_Voltage_Reference_256			(uint8_t)(3<<6)

//@ ref  ADC_Prescaler_Define

#define ADC_Prescaler_2						(uint8_t)(1)
#define ADC_Prescaler_4						(uint8_t)(2)
#define ADC_Prescaler_8						(uint8_t)(3)
#define ADC_Prescaler_16					(uint8_t)(4)
#define ADC_Prescaler_32					(uint8_t)(5)
#define ADC_Prescaler_64					(uint8_t)(6)
#define ADC_Prescaler_128					(uint8_t)(7)

// @ ref  ADC_IRQ_ENABLE_Define

#define ADC_IRQ_ENABLE_Disable				(uint8_t)(0)
#define ADC_IRQ_ENABLE_Enable				(uint8_t)(1)

//==============================================================

/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/

void MCAL_ADC_Init( ADC_config_t* ADC_Config );
uint16_t MCAL_ADC_Read( enum NUM_CH CH );

//==================================================================

#endif /* ADC_H_ */