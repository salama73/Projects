/*
 * TIMER0_Driver.h
 *
 * Created: 10/11/2022 3:06:51 AM
 *  Author: Salama Mohamed
 */ 


#ifndef TIMER0_DRIVER_H_
#define TIMER0_DRIVER_H_


//Include
#include "Atmega32.h"
#include "GPIO_Driver.h"

//============================================================


//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
	uint8_t Timer0_Mode 				;	//specified the Timer0 mode 
											//this parameter must be set based on  @ ref  TIMER0_MODE_Define
	
	uint8_t Output_Compare_pin			; 	//These bits control the Output Compare pin (OC0) behavior
											//this parameter must be set based on  @ ref  TIMER0_Output_Compare_pin_Define

	uint8_t Clock_Source				;	//select the clock source to be used by the Timer/Counter
											//this parameter must be set based on  @ ref  TIMER0_Clock_Source_Define
	
	uint8_t OCIE0_EN					;	// Timer/Counter0 Output Compare Match Interrupt Enable (disable or enable )  .
											//this parameter must be set based on  @ ref  TIMER0_TOIE0_ENABLE_Define
											
	uint8_t TOIE0_EN					;	//  Timer/Counter0 Overflow Interrupt Enable (disable or enable )  .
											//this parameter must be set based on  @ ref  TIMER0_OCIE0_ENABLE_Define
		
	uint8_t Compare_Value				;	//The Output Compare Register contains an 8-bit value that is continuously compared with the counter value

	void (*P_TOIE0_CALL)()				;   // set the function which will be call at IRQ happen (TOIE0)
	
	void (*P_OCIE0_CALL)()				;   // set the function which will be call at IRQ happen (OCIE0)

}TIMER0_config_t;

//=========================================================================

//-----------------------------
//Macros Configuration References
//-----------------------------

//@ ref  TIMER0_MODE_Define
#define TIMER0_MODE_Normal								(uint8_t)(0)
#define TIMER0_MODE_CTC									(uint8_t)(1<<6)

//TIMER0_Output_Compare_pin_Define
/*
Compare Output Mode, non-PWM Mode
	COM01	COM00	Description
	  0       0		Normal port operation, OC0 disconnected.
	  0		  1		Toggle OC0 on compare match
	  1		  0		Clear OC0 on compare match
	  1		  1		Set OC0 on compare match
*/
#define TIMER0_Output_Compare_pin_Disable				(uint8_t)(0)
#define TIMER0_Output_Compare_pin_Toggle				(uint8_t)(1<<4)
#define TIMER0_Output_Compare_pin_Clear					(uint8_t)(2<<4)
#define TIMER0_Output_Compare_pin_Set					(uint8_t)(3<<4)

//@ ref  TIMER0_Clock_Source_Define
// 8/64/256/1024 is  prescaler -->>>>( F_CPU / prescaler )
#define TIMER0_Clock_Source_Stop						(uint8_t)(0)
#define TIMER0_Clock_Source_clk							(uint8_t)(1<<0)
#define TIMER0_Clock_Source_clk_8						(uint8_t)(2<<0)
#define TIMER0_Clock_Source_clk_64						(uint8_t)(3<<0)
#define TIMER0_Clock_Source_clk_256						(uint8_t)(4<<0)
#define TIMER0_Clock_Source_clk_1024					(uint8_t)(5<<0)
#define TIMER0_Clock_Source_External_falling_Edge		(uint8_t)(6<<0)
#define TIMER0_Clock_Source_External_Rising_Edge		(uint8_t)(6<<0)


//@ ref  TIMER0_OCIE0_ENABLE_Define
#define TIMER0_OCIE0_ENABLE_Enable						(uint8_t)(1)
#define TIMER0_OCIE0_ENABLE_Disable						(uint8_t)(0)

//@ ref  TIMER0_TOIE0_ENABLE_Define
#define TIMER0_TOIE0_ENABLE_Enable						(uint8_t)(1)
#define TIMER0_TOIE0_ENABLE_Disable						(uint8_t)(0)

//========================================================================================

/*
* ===============================================
* APIs Supported by "MCAL I2C DRIVER"
* ===============================================
*/
void MCAL_TIMER0_Init(TIMER0_config_t* TIMER0_Config);
void MCAL_TIMER0_Set_Compare_Value(uint8_t Compare_Value) ;
uint8_t MCAL_TIMER0_Read_Compare_Value() ;
uint8_t MCAL_TIMER0_Read_Counter_Value() ;
//=========================================================================================

#endif /* TIMER0_DRIVER_H_ */