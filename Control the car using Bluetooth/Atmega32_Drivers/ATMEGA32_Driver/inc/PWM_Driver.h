/*
 * PWM_Driver.h
 *
 * Created: 10/13/2022 8:16:38 PM
 *  Author: vip Salama Mohamed
 */ 


#ifndef PWM_DRIVER_H_
#define PWM_DRIVER_H_


//Include
#include "Atmega32.h"
#include "GPIO_Driver.h"

//============================================================


//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{	
	uint8_t Output_Compare_pin_A		; 	//These bits control the Output Compare pin (OC1A) behavior
											//this parameter must be set based on  @ ref  PWM_Output_Compare_pin_A_Define
											
	uint8_t Output_Compare_pin_B		; 	//These bits control the Output Compare pin (OC1B) behavior
											//this parameter must be set based on  @ ref  PWM_Output_Compare_pin_B_Define

	uint8_t Clock_Source				;	//select the clock source to be used by the Timer/Counter
											//this parameter must be set based on  @ ref  PWM_Clock_Source_Define
	
	uint8_t TOIE1_EN					;	//  Timer/Counter1 Overflow Interrupt Enable (disable or enable )  .
											//this parameter must be set based on  @ ref  PWM_TOIE1_ENABLE_Define
	
	uint8_t OCIE1A_EN					;	// Timer/Counter1 Output Compare Match Interrupt Enable (disable or enable )  .
											//this parameter must be set based on  @ ref  PWM_OCIE1A_ENABLE_Define
	
	uint8_t OCIE1B_EN					;	//  Timer/Counter1 Output Compare Match Interrupt Enable (disable or enable )   .
											//this parameter must be set based on  @ ref  PWM_OCIE1B_ENABLE_Define
	
	uint16_t Compare_Value_CH_A			;	//The Output Compare Register for channel A contains an 16-bit value that is continuously compared with the counter value
	
	uint16_t Compare_Value_CH_B			;	//The Output Compare Register for channel B contains an 16-bit value that is continuously compared with the counter value
	
	uint16_t TOP_Value					;	//The Maximum value for counter 

	void (*P_TOIE1_CALL)()				;   // set the function which will be call at IRQ happen (TOIE1)
	
	void (*P_OCIE1A_CALL)()				;   // set the function which will be call at IRQ happen (OCIE1A)
	
	void (*P_OCIE1B_CALL)()				;   // set the function which will be call at IRQ happen (OCIE1B)

}PWM_config_t;

typedef enum
{
	A,
	B
}channel;

//=========================================================================


//-----------------------------
//Macros Configuration References
//-----------------------------

// @ ref PWM_Output_Compare_pin_A_Define
#define PWM_Output_Compare_pin_A_Disable									(uint8_t)(0)
#define PWM_Output_Compare_pin_A_Set_At_Compare_Value_Clear_At_TOP			(uint8_t)(3<<6)
#define PWM_Output_Compare_pin_A_Clear_At_Compare_Value_Set_At_TOP			(uint8_t)(2<<6)

// @ ref PWM_Output_Compare_pin_B_Define
#define PWM_Output_Compare_pin_B_Disable									(uint8_t)(0)
#define PWM_Output_Compare_pin_B_Set_At_Compare_Value_Clear_At_TOP			(uint8_t)(3<<4)
#define PWM_Output_Compare_pin_B_Clear_At_Compare_Value_Set_At_TOP			(uint8_t)(2<<4)

//@ ref  PEM_Clock_Source_Define
// 8/64/256/1024 is  prescaler -->>>>( F_CPU / prescaler )
#define PWM_Clock_Source_Stop												(uint8_t)(0)
#define PWM_Clock_Source_clk												(uint8_t)(1<<0)
#define PWM_Clock_Source_clk_8												(uint8_t)(2<<0)
#define PWM_Clock_Source_clk_64												(uint8_t)(3<<0)
#define PWM_Clock_Source_clk_256											(uint8_t)(4<<0)
#define PWM_Clock_Source_clk_1024											(uint8_t)(5<<0)
#define PWM_Clock_Source_External_falling_Edge								(uint8_t)(6<<0)
#define PWM_Clock_Source_External_Rising_Edge								(uint8_t)(6<<0)

//@ ref  PWM_OCIE1A_ENABLE_Define
#define PWM_OCIE1A_ENABLE_Enable											(uint8_t)(1)
#define PWM_OCIE1A_ENABLE_Disable											(uint8_t)(0)

//@ ref  PWM_OCIE1B_ENABLE_Define
#define PWM_OCIE1B_ENABLE_Enable											(uint8_t)(1)
#define PWM_OCIE1B_ENABLE_Disable											(uint8_t)(0)

//@ ref  PWM_TOIE1_ENABLE_Define
#define PWM_TOIE1_ENABLE_Enable												(uint8_t)(1)
#define PWM_TOIE1_ENABLE_Disable											(uint8_t)(0)

//=========================================================================


/*
* ===============================================
* APIs Supported by "MCAL I2C DRIVER"
* ===============================================
*/
void MCAL_PWM_Init(PWM_config_t* PWM_Config);
void MCAL_PWM_DInit(void);
void MCAL_PWM_Set_Compare_Value(uint16_t Compare_Value , channel Chan ) ;
void MCAL_PWM_Set_TOP_Value(uint16_t TOP_Value ) ;
//=========================================================================================


#endif /* PWM_DRIVER_H_ */