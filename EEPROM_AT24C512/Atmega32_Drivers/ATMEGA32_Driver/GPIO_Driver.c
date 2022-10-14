/*
 * GPIO_Driver.c
 *
 * Created: 30/08/2022 08:02:57 م
*  Author: salama mohamed
 */ 

#include "GPIO_Driver.h"

/**================================================================
* @Fn				-MCAL_GPIO_Init
* @brief		  	-Initializes the GPIOx according to the specified parameters in the pinconfig
* @param [in] 		-GPIOx: can be (A-->D) to select the GPIO peripheral
* @param [in] 		-configuration information for the specified pin
* @retval 			-none
* Note				-none
*/
void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx , GPIO_Pinconfig_t *pinconfig )
{
	if ( pinconfig->GPIO_MODE == GPIO_MODE_INPUT_FLO )
	{
		GPIOx->DDR &= ~(pinconfig->pinNumber);
		GPIOx->PORT &= ~(pinconfig->pinNumber);
	}
	else if ( pinconfig->GPIO_MODE == GPIO_MODE_INPUT_PU )
	{
		GPIOx->DDR &= ~(pinconfig->pinNumber);
		GPIOx->PORT |= pinconfig->pinNumber;
	}
	else
	{
		GPIOx->DDR |= pinconfig->pinNumber;
		GPIOx->PORT &= ~(pinconfig->pinNumber);
	}
}



/**================================================================
* @Fn				-MCAL_GPIO_DeInit
* @brief		  	-Reset all the GPIO Register
* @param [in] 		-GPIOx: can be (A-->D) to select the GPIO peripheral
* @retval 			-none
* Note				-none
*/
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx )
{
	GPIOx->DDR  = 0X00  ; // INPUT FLOATING
	GPIOx->PORT = 0X00  ;
}



/**================================================================
* @Fn				-MCAL_GPIO_ReadPin
* @brief		  	-Read specified pin
* @param [in] 		-GPIOx: can be (A-->D) to select the GPIO peripheral
* @param [in] 		-pinNumber: set pinNumber according to @ ref  GPIO_PINS_Define
* @retval 			-the input pin value (two value based on @ ref  GPIO_PINS_state)
* Note				-none
*/
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx ,uint8_t pinNumber )
{
	if( GPIOx->PIN & pinNumber )
	{
		return GPIO_PIN_SET;
	}
	
	return GPIO_PIN_RESET;
}



/**================================================================
* @Fn				-MCAL_GPIO_ReadPort
* @brief		  	-Read specified port
* @param [in] 		-GPIOx: can be (A-->D) to select the GPIO peripheral
* @param [in] 		-pinNumber: set pinNumber according to @ ref  GPIO_PINS_Define
* @retval 			-the input port value
* Note				-none
*/
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx )
{
	uint8_t port_value;
	port_value= (uint8_t) (GPIOx->PIN);
	return port_value;
}


/**================================================================
* @Fn				-MCAL_GPIO_WritePin
* @brief		  	-Write specified pin
* @param [in] 		-GPIOx: can be (A-->D) to select the GPIO peripheral
* @param [in] 		-pinNumber: set pinNumber according to @ ref  GPIO_PINS_Define
* @param [in] 		-value: pin value
* @retval 			-none
* Note				-none
*/
void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx ,uint8_t pinNumber ,uint8_t value)
{
	if ( value == GPIO_PIN_SET )
	{
		GPIOx->PORT |= pinNumber ;
	}
	else if(  value == GPIO_PIN_RESET)
	{
		GPIOx->PORT &= ~( pinNumber ) ;
	}
}


/**================================================================
* @Fn				-MCAL_GPIO_WritePort
* @brief		  	-Write specified port
* @param [in] 		-GPIOx: can be (A-->D) to select the GPIO peripheral
* @param [in] 		-value: port value
* @retval 			-none
* Note				-none
*/
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx ,uint8_t value)
{
	GPIOx->PORT=  value;
}



/**================================================================
* @Fn				-MCAL_GPIO_TogglePin
* @brief		  	-toggle specified pin
* @param [in] 		-GPIOx: can be (A-->D) to select the GPIO peripheral
* @param [in] 		-pinNumber: set pinNumber according to @ ref  GPIO_PINS_Define
* @retval 			-none
* Note				-none
*/
void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx ,uint8_t pinNumber )
{
	GPIOx->PORT ^=pinNumber;
}




/**================================================================
* @Fn				-MCAL_GPIO_InitPORT
* @brief		  	-Initializes the GPIOx according to the specified parameters in the pinconfig
* @param [in] 		-GPIOx: can be (A-->D) to select the GPIO peripheral
* @param [in] 		-configuration information for the specified pin
* @retval 			-none
* Note				-none
*/
/*
void MCAL_GPIO_InitPORT(GPIO_TypeDef *GPIOx , uint8_t MODE )
{
		if ( MODE == GPIO_MODE_INPUT_FLO )
		{
			GPIOx->DDR  = 0X00  ;
			GPIOx->PORT = 0X00  ;
		}
		else if ( MODE = GPIO_MODE_INPUT_PU )
		{
			GPIOx->DDR  = 0X00 ;
			GPIOx->PORT = 0XFF ;
		}
		else if ( MODE == GPIO_MODE_OUTPUT )
		{
			GPIOx->DDR  = 0XFF ;
			GPIOx->PORT = 0X00 ;
		}
}
*/
