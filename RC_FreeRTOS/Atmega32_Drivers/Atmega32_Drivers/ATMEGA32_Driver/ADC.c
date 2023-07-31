/*
 * ADC.c
 *
 * Created: 12/2/2022 10:10:03 PM
 *  Author: Salama Mohamed
 */ 

#include "ADC.h"

/**================================================================
* @Fn				-MCAL_ADC_Init
* @brief		  	-Initializes the ADC  according to the specified parameters in the ADC_Config
* 					 @ ref  ADC_Prescaler_Define  and  @ ref  ADC_Voltage_Reference_Define  and ....
* @param [in] 		-ADC_Config: configuration information for  ADC {CH0 TO CH7}
* 					 take  pointer to function (this function calling at interrupt)
* @retval 			-none
* Note				-Support CH0 TO CH7 (Single_Ended Mode)
*/
void MCAL_ADC_Init( ADC_config_t* ADC_Config )
{
	switch(ADC_Config->Voltage_Reference)
	{
		case ADC_Voltage_Reference_AREF :
		{
			ADC->ADMUX &= ~(ADC_Config->Voltage_Reference);
			break;
		}
		case ADC_Voltage_Reference_256 :
		case ADC_Voltage_Reference_AVCC :
		{
			ADC->ADMUX |= ADC_Config->Voltage_Reference;
			break;
		}
	}
	
	ADC->ADCSRA|= ADC_Config->Prescaler ;
	
	ADC->ADCSRA|=(1<<7);
	
}


/**================================================================
* @Fn				-MCAL_ADC_Read
* @brief		  	-Read the ADC value
* @param [in]		-enum NUM_CH CH :Select ADC channel {CH0 TO CH7}
* @retval 			-ADC value 
* Note				-Support CH0 TO CH7 (Single_Ended Mode)
*/
uint16_t MCAL_ADC_Read( enum NUM_CH CH )
{
	uint16_t data =0;
	if(CH==0)
	{
		ADC->ADMUX &=~(CH);
	}
	else
	{
		ADC->ADMUX |=CH;
	}
	ADC->ADCSRA|=(1<<6);
	
	while(!(ADC->ADCSRA && (1<<6) ) );
	
	data = ADC->ADCL ;
	data |= (ADC->ADCH <<8) ;
	return data ;
}