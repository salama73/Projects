/*
 * stm32_f103c6_GPIO.c
 *
 *  Created on: Aug 26, 2022
 *      Author: Salama Mohamed
 */

#include"stm32_f103c6_GPIO.h"


uint8_t get_position(uint16_t pinNumber)
{
	switch(pinNumber)
	{
	case GPIO_PIN_0 :
		return 0;
		break;
	case GPIO_PIN_1 :
		return 4;
		break;
	case GPIO_PIN_2 :
		return 8;
		break;
	case GPIO_PIN_3 :
		return 12;
		break;
	case GPIO_PIN_4 :
		return 16;
		break;
	case GPIO_PIN_5 :
		return 20;
		break;
	case GPIO_PIN_6 :
		return 24;
		break;
	case GPIO_PIN_7 :
		return 28;
		break;
	case GPIO_PIN_8 :
		return 0;
		break;
	case GPIO_PIN_9 :
		return 4;
		break;
	case GPIO_PIN_10 :
		return 8;
		break;
	case GPIO_PIN_11 :
		return 12;
		break;
	case GPIO_PIN_12 :
		return 16;
		break;
	case GPIO_PIN_13 :
		return 20;
		break;
	case GPIO_PIN_14 :
		return 24;
		break;
	case GPIO_PIN_15 :
		return 28;
		break;
	default:
		return 0;
	}
}

/**================================================================
* @Fn				-MCAL_GPIO_Init
* @brief		  	-Initializes the GPIOx according to the specified parameters in the pinconfig
* @param [in] 		-GPIOx: can be (A-->E) to select the GPIO peripheral
* @param [in] 		-pinconfig: configuration information for the specified pin
* @retval 			-none
* Note				-stm32f103c6 has GPIO (A--->> E)but the LQFP48 package has GPIO (A---->> D)
*/
void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx , GPIO_Pinconfig_t *pinconfig )
{
	// GPIO->CRL configure pins 0-->>7
	// GPIO->CRH configure pins 8-->>15
	volatile uint32_t *configregister =NULL;
	uint8_t pin_config=0;
	configregister = (pinconfig->pinNumber <GPIO_PIN_8) ? &GPIOx->CRL : &GPIOx->CRH ;
	//clear MODEy[1:0] and CNFy[1:0]
	(*configregister) &=~(0XF<<get_position(pinconfig->pinNumber));
	//if pin is output
	if(pinconfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_OD || pinconfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_PP || pinconfig->GPIO_MODE == GPIO_MODE_OUTPUT_OD || pinconfig->GPIO_MODE == GPIO_MODE_OUTPUT_PP)
	{
		//set MODEy[1:0] and CNFy[1:0]
		pin_config = ((((pinconfig->GPIO_MODE - 4) <<2) | (pinconfig->GPIO_OUTPUT_Speed)) & 0x0f);
	}
	//if pin is input
	else
	{
		if(pinconfig->GPIO_MODE == GPIO_MODE_INPUT_FLO || pinconfig->GPIO_MODE == GPIO_MODE_Analog)
		{
			//set MODEy[1:0] and CNFy[1:0]
			pin_config = ((((pinconfig->GPIO_MODE) <<2)) &0x0f);

		}
		else if(pinconfig->GPIO_MODE == GPIO_MODE_INPUT_AF)
		{
			//set MODEy[1:0] and CNFy[1:0]
			pin_config = ((((GPIO_MODE_INPUT_FLO) <<2)) &0x0f);
		}
		else
		{
			//set MODEy[1:0] and CNFy[1:0]
			pin_config = ((((GPIO_MODE_INPUT_PU) <<2)) &0x0f);
			if(pinconfig->GPIO_MODE == GPIO_MODE_INPUT_PU)
			{
				//  port bit configuration table px_ODR =1
				GPIOx->ODR  |=pinconfig->pinNumber;
			}
			else
			{
				//  port bit configuration table px_ODR =0
				GPIOx->ODR  &=~(pinconfig->pinNumber);
			}
		}
	}
	(*configregister) |=(pin_config<<get_position(pinconfig->pinNumber));
}


/**================================================================
* @Fn				-MCAL_GPIO_DeInit
* @brief		  	-Reset all the GPIO Register
* @param [in] 		-GPIOx: can be (A-->E) to select the GPIO peripheral
* @retval 			-none
* Note				-none
*/
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx )
{
	if(GPIOx==GPIOA)
	{
		RCC->APB2RSTR |=(1<<2);
		RCC->APB2RSTR &=~(1<<2);
	}
	else if (GPIOx==GPIOB)
	{
		RCC->APB2RSTR |=(1<<3);
		RCC->APB2RSTR &=~(1<<3);
	}
	else if (GPIOx==GPIOC)
	{
		RCC->APB2RSTR |=(1<<4);
		RCC->APB2RSTR &=~(1<<4);
	}
	else if (GPIOx==GPIOD)
	{
		RCC->APB2RSTR |=(1<<5);
		RCC->APB2RSTR &=~(1<<5);
	}
	else if (GPIOx==GPIOE)
	{
		RCC->APB2RSTR |=(1<<6);
		RCC->APB2RSTR &=~(1<<6);
	}
}


/**================================================================
* @Fn				-MCAL_GPIO_ReadPin
* @brief		  	-Read specified pin
* @param [in] 		-GPIOx: can be (A-->E) to select the GPIO peripheral
* @param [in] 		-pinNumber: set pinNumber according to @ ref  GPIO_PINS_Define
* @retval 			-the input pin value (two value based on @ ref  GPIO_PINS_state)
* Note				-none
*/
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx ,uint16_t pinNumber )
{
	uint8_t bit_state;
	if (((GPIOx->IDR) & pinNumber) !=  (uint32_t) GPIO_PIN_RESET)
	{
		bit_state=GPIO_PIN_SET;
	}
	else
	{
		bit_state=GPIO_PIN_RESET;
	}
	return bit_state;
}



/**================================================================
* @Fn				-MCAL_GPIO_ReadPort
* @brief		  	-Read specified port
* @param [in] 		-GPIOx: can be (A-->E) to select the GPIO peripheral
* @param [in] 		-pinNumber: set pinNumber according to @ ref  GPIO_PINS_Define
* @retval 			-the input port value
* Note				-none
*/
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx )
{
	uint16_t port_value;
	port_value=(uint16_t) (GPIOx->IDR);
	return port_value;
}





/**================================================================
* @Fn				-MCAL_GPIO_WritePin
* @brief		  	-Write specified pin
* @param [in] 		-GPIOx: can be (A-->E) to select the GPIO peripheral
* @param [in] 		-pinNumber: set pinNumber according to @ ref  GPIO_PINS_Define
* @param [in] 		-value: pin value
* @retval 			-none
* Note				-none
*/
void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx ,uint16_t pinNumber ,uint8_t value)
{
	if (value != GPIO_PIN_RESET)
	{
		/*
		 Bits 15:0 BSy: Port x Set bit y (y= 0 .. 15)
		These bits are write-only and can be accessed in Word mode only.
		0: No action on the corresponding ODRx bit
		1: Set the corresponding ODRx bit
		 */
		GPIOx->BSRR= (uint32_t) pinNumber;
	}
	else
	{
		/*
		Bits 31:16 Reserved
		Bits 15:0 BRy: Port x Reset bit y (y= 0 .. 15)
		These bits are write-only and can be accessed in Word mode only.
		0: No action on the corresponding ODRx bit
		1: Reset the corresponding ODRx bit
		 */
		GPIOx->BRR= (uint32_t) pinNumber;
	}
}







/**================================================================
* @Fn				-MCAL_GPIO_WritePort
* @brief		  	-Write specified port
* @param [in] 		-GPIOx: can be (A-->E) to select the GPIO peripheral
* @param [in] 		-value: port value
* @retval 			-none
* Note				-none
*/
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx ,uint16_t value)
{
	GPIOx->ODR= (uint32_t) value;
}





/**================================================================
* @Fn				-MCAL_GPIO_TogglePin
* @brief		  	-toggle specified pin
* @param [in] 		-GPIOx: can be (A-->E) to select the GPIO peripheral
* @param [in] 		-pinNumber: set pinNumber according to @ ref  GPIO_PINS_Define
* @retval 			-none
* Note				-none
*/
void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx ,uint16_t pinNumber )
{
	GPIOx->ODR ^=pinNumber;
}




/**================================================================
* @Fn				-MCAL_GPIO_LockPin
* @brief		  	-The locking mechanism allows the IO configuration to be frozen
* @param [in] 		-GPIOx: can be (A-->E) to select the GPIO peripheral
* @param [in] 		-pinNumber: set pinNumber according to @ ref  GPIO_PINS_Define
* @retval 			-OK is pin number is locked or ERROR if pin not locked @ref GPIO_Return_lock
* Note				-none
*/
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef *GPIOx ,uint16_t pinNumber )
{
	/*
	 Bits 31:17 Reserved
	Bit 16 LCKK[16]: Lock key
	This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
	0: Port configuration lock key not active
	1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
	LOCK key writing sequence:
	Write 1
	Write 0
	Write 1
	Read 0
	Read 1
	(this read is optional but confirms that the lock is active)
	Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
	Any error in the lock sequence will abort the lock.
	Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
	These bits are read write but can only be written when the LCKK bit is 0.
	0: Port configuration not locked
	1: Port configuration locked.
	 */

	//set the LCKK
	volatile uint32_t temp = 1<<16;
	//set the LCKK
	temp |= pinNumber;

	//Write 1
	GPIOx->LCKR = temp;
	//Write 0
	GPIOx->LCKR = pinNumber;
	//Write 1
	GPIOx->LCKR = temp;
	//Read 0
	temp=GPIOx->LCKR;
	//Read 1
	temp=GPIOx->LCKR;
	if(temp & (1<<16))
	{
		return GPIO_Return_lock_Enabled;
	}
	else
	{
		return GPIO_Return_lock_ERROR;
	}
}
