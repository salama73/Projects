/*
 * Servo_Motor.c
 *
 * Created: 10/13/2022 11:07:43 PM
 *  Author: Salama Mohamed
 */ 

#include "Servo_Motor.h"

// Calculate the compare value to determine duty cycle   
#define Get_freq						((uint32_t)(F_CPU/64))
#define Get_periodic					((1.0/Get_freq))
#define Get_Compare_Value(angle)		((uint16_t)(((0.001+(0.00000555555556*angle))/Get_periodic )-0.5))


/**================================================================
* @Fn				-Servo_Init
* @brief		  	-Initializes the TIMER1  to act in mode Fast PWM at 50HZ Output and F_CPU / 64 Input 
* @retval 			-none
* Note				-Disable all pointers
*/
void Servo_Init(void) 
{
	PWM_config_t PWM_Config ;
	PWM_Config.Compare_Value_CH_B = 0 ;
	PWM_Config.Compare_Value_CH_A = 0 ;
	PWM_Config.Output_Compare_pin_B = PWM_Output_Compare_pin_B_Disable ;
	PWM_Config.Output_Compare_pin_A = PWM_Output_Compare_pin_A_Clear_At_Compare_Value_Set_At_TOP ;
	PWM_Config.Clock_Source = PWM_Clock_Source_clk_64 ;
	PWM_Config.TOP_Value = (uint16_t)((F_CPU/(64*50))-1) ;
	PWM_Config.OCIE1A_EN = PWM_OCIE1A_ENABLE_Disable ;
	PWM_Config.OCIE1B_EN = PWM_OCIE1B_ENABLE_Disable ;
	PWM_Config.TOIE1_EN = PWM_TOIE1_ENABLE_Disable ;
	PWM_Config.P_OCIE1A_CALL = NULL ;
	PWM_Config.P_OCIE1B_CALL = NULL ;
	PWM_Config.P_TOIE1_CALL = NULL ;
	MCAL_PWM_Init(&PWM_Config) ;
}

/**================================================================
* @Fn				-My_Servo
* @brief		  	-Disable  TIMER1 and Disable global interrupt and clear register For TIMER1
* @param [in] 		-Angel: rotation angle from 0 to 180
* @retval 			-none
* Note				-none
*/
void My_Servo(uint8_t angle) 
{
	uint16_t Compare_Value = 0;
	Compare_Value = Get_Compare_Value(angle) ;
	MCAL_PWM_Set_Compare_Value(Compare_Value,A) ;
}


/**================================================================
* @Fn				-Servo_DInit
* @brief		  	-Disable  TIMER1 and Disable global interrupt and clear register For TIMER1
* @retval 			-none
* Note				-none
*/
void Servo_DInit(void) 
{
	MCAL_PWM_DInit();
}