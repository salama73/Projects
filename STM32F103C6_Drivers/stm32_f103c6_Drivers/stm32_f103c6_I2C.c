/*
 * stm32_f103c6_RCC.c
 *
 *  Created on: 20/9/2022
 *  Author: Salama mohamed
 */

#include "stm32_f103c6_I2C.h"

/*
 * ===============================================================
 *
 *                      Generic Variable
 *
 * ===============================================================
 */
I2C_config_t g_I2C_Config[2] ={ NULL , NULL } ;

//=================================================================================
/*
 * ===============================================================
 *
 *                      Generic Macro
 *
 * ===============================================================
 */


/*
 * ===============================================================
 *
 *                      Generic Function
 *
 * ===============================================================
 */


/**================================================================
* @Fn				-Slave_Status
* @brief		  	-check the current state to I2C ( busy , receive data , receive address ...... ) to determine source of current interrupt  .
* @param [in] 		-state: the status to be check
* @param [in] 		-I2Cx:  specified I2Cx x=[ 1 : 2 ]
* @retval 			-none
* Note				-this function jump to call_interrupt in main .
*/
void Slave_Status(I2C_TypeDef* I2Cx , Slave_State state)
{
	uint8_t index =  I2Cx == I2C1 ? 0 : 1 ;

	switch(state)
	{
	case I2C_EV_STOP :
		if(I2Cx->SR2 & (I2C_SR2_TRA))
		{
			//Stop condition is detected on the bus by the slave after an acknowledge
			g_I2C_Config[index].P_IRQ_CALL(I2C_EV_STOP);
		}
		break;
	case I2C_EV_ADDR_Matched :
		//address matched with the OAR registers content or a general call
		g_I2C_Config[index].P_IRQ_CALL(I2C_EV_ADDR_Matched);
		break;
	case I2C_EV_DATA_REQ :
		if(I2Cx->SR2 & (I2C_SR2_TRA))
		{
			// the APP layer should send the data
			g_I2C_Config[index].P_IRQ_CALL(I2C_EV_DATA_REQ);
		}
		break;
	case I2C_EV_DATA_RCV :
		// Make Sure the Slave is really in receiver mode
		if(!(I2Cx->SR2 & (I2C_SR2_TRA)))
		{
			// the APP layer should read the data
			g_I2C_Config[index].P_IRQ_CALL(I2C_EV_DATA_RCV);
		}
		break;
	}
}


/**================================================================
* @Fn				-Get_flag_stutus
* @brief		  	-check the current state to I2C ( busy , receive data , receive address ...... ) .
* @param [in] 		-flag: the status to be check
* @param [in] 		-I2Cx:  specified I2Cx x=[ 1 : 2 ]
* @retval 			-FlagStatus
* Note				-none
*/
FlagStatus Get_flag_stutus( I2C_TypeDef *I2Cx , Status flag )
{
	FlagStatus current_state ;
	switch( flag )
	{
	case I2C_Busy :
		if (I2Cx->SR2 & I2C_SR2_BUSY)
			current_state=SET ;
		else
			current_state=RESET ;
		break;
	case EV5 :
		if (I2Cx->SR1 & I2C_SR1_SB)
			current_state=SET ;
		else
			current_state=RESET ;
		break;
	case EV6 :
		if (I2Cx->SR1 & I2C_SR1_ADDR)
			current_state=SET ;
		else
			current_state=RESET ;
		break;
	case EV8_1 :
		if (I2Cx->SR1 & I2C_SR1_TXE)
			current_state=SET ;
		else
			current_state=RESET ;
		break;
	case EV8_2 :
		if (I2Cx->SR1 & I2C_SR1_BTF)
			current_state=SET ;
		else
			current_state=RESET ;
		break;
	case EV7 :
		if (I2Cx->SR1 & I2C_SR1_RXNE)
			current_state=SET ;
		else
			current_state=RESET ;
		break;
	}
	return current_state ;
}

/**================================================================
* @Fn				-I2C_Generate_Start
* @brief		  	-generate start condition to start transmitter .
* @param [in] 		-I2Cx:  specified I2Cx x=[ 1 : 2 ]
* @param [in] 		-Start:  send start or Repeated start
* @retval 			-none
* Note				-none
*/
void I2C_Generate_Start(I2C_TypeDef* I2Cx , Repeated_Start Start)
{
	if ( Start != RepeatedSart )
	{
		while( Get_flag_stutus(I2Cx, I2C_Busy)) ;
	}
	I2Cx->CR1 |=I2C_CR1_START ;
}

/**================================================================
* @Fn				-I2C_Send_Address
* @brief		  	-send address by I2C from master to slave , address is (7  or 10)bit
* @param [in] 		-I2Cx:  specified I2Cx x=[ 1 : 2 ]
* @param [in] 		-Address: slave address
* @param [in] 		-Dir: Direction of communication ( Transmitter or Receiver )
* @retval 			-none
* Note				-none.
*/
void I2C_Send_Address(I2C_TypeDef* I2Cx, uint16_t Address , I2C_Direction Dir)
{
	Address = Address<<1 ;
	if (Dir == Transmitter )
		Address &= ~(1 << 0);
	else
		Address |= (1 << 0);
	I2Cx->DR = Address;
}

/**================================================================
* @Fn				-I2C_Generate_Stop
* @brief		  	-generate stop condition to end transmitter .
* @param [in] 		-I2Cx:  specified I2Cx x=[ 1 : 2 ]
* @retval 			-none
* Note				-none
*/
void I2C_Generate_Stop(I2C_TypeDef* I2Cx )
{
	I2Cx->CR1 |=I2C_CR1_STOP ;
}

/*
 * ===============================================================
 *
 *                      API Function Definitions
 *
 * ===============================================================
 */


/**================================================================
* @Fn				-MCAL_I2C_Init
* @brief		  	-Initializes the I2Cx  according to the specified parameters in the I2C_Config
* 					 @ ref  I2C_Speed_MODE_Define  and  @ ref  I2C_Own_Address_Define  and ....
* @param [in] 		-I2C_Config: configuration information for  I2Cx
* 					 take a pointer to function (this function calling at interrupt)
* @retval 			-none
* Note				-stm32f103c6 has I2C (1---2 )
*/
void MCAL_I2C_Init(I2C_TypeDef* I2Cx, I2C_config_t* I2C_Config)
{
	uint16_t TempReg = 0 , FreqReg = 0 , result = 0;
	uint32_t pclk1 = 0;

	// Set RCC
	if( I2Cx == I2C1)
	{
		g_I2C_Config[0]=*I2C_Config;
		RCC_I2C1_CLK_Enable();
	}
	else
	{
		g_I2C_Config[1]=*I2C_Config;
		RCC_I2C2_CLK_Enable();
	}

	//Set MODE_Speed

	// set Bits 5:0 FREQ[5:0]: Peripheral clock frequency
	TempReg=I2Cx->CR2;
	TempReg  &=~(I2C_CR2_FREQ);
	pclk1=MCAL_Get_PCLC1_FREQ();
	FreqReg = (uint16_t)( pclk1 / 1000000);
	TempReg |=FreqReg;
	I2Cx->CR2 = TempReg ;
	//set Bits 5:0 TRISE[5:0]: Maximum rise time in Fm/Sm mode (Master mode) and CCR
	// Disable I2C
	I2Cx->CR1 &=~(I2C_CR1_PE);
	if( I2C_Config->MODE_Speed == I2C_Speed_MODE_SM_100)
	{
		TempReg=0;
		// CCR = Fpclk1 / (2 * I2C_Clock_freq )
		TempReg = I2Cx->CCR ;
		result = (uint16_t)( pclk1 / ( I2C_Config->MODE_Speed *2 ));
		TempReg |=result ;
		I2Cx->CCR = TempReg ;
		//set Bits 5:0 TRISE[5:0]: Maximum rise time in Fm/Sm mode (Master mode)
		TempReg=0;
		TempReg=(uint16_t)(FreqReg+1);
		I2Cx->TRISE = TempReg ;
	}
	else
	{
		//FM NOT SPORTED
	}
	// set CR1 SET ACK
	TempReg = 0;
	TempReg = I2Cx->CR1;
	if (I2C_Config->ACK_Control == I2C_ACK_Control_Enable)
	{
		TempReg |= ( I2C_CR1_ACK) ;
		I2Cx->CR1 = TempReg ;
	}
	else
	{
		TempReg &= ~( I2C_CR1_ACK) ;
		I2Cx->CR1 = TempReg ;
	}
	// Set Address
	TempReg=0;
	if(I2C_Config->Address.Dual_Address_Enable)
	{
		TempReg |= I2C_OAR2_ENDUAL;
		TempReg |= I2C_Config->Address.Dual_Address << I2C_OAR2_ADD2_Pos ;
		I2Cx->OAR2 = TempReg;
		// set own address in 7 bit mode
		TempReg=0;
		TempReg &=I2C_NUM_Address_BIT_7 ;
		TempReg |= I2C_Config->Address.Own_Address << 1;
		I2Cx->OAR1 = TempReg ;
	}
	else
	{
		if( I2C_Config->NUM_Address_BIT==I2C_NUM_Address_BIT_10)
		{
			TempReg |=I2C_NUM_Address_BIT_10 ;
			TempReg |= I2C_Config->Address.Own_Address ;
			I2Cx->OAR1 = TempReg ;
		}
		else
		{
			TempReg &=I2C_NUM_Address_BIT_7 ;
			TempReg |= I2C_Config->Address.Own_Address << 1;
			I2Cx->OAR1 = TempReg ;
		}
	}
	//Set interrupt event
	if( I2C_Config->IRQ_EN==I2C_IRQ_ENABLE_I2C_EV)
	{
		I2Cx->CR2 |= (I2C_CR2_ITBUFEN) | (I2C_CR2_ITEVTEN);
		if(I2Cx == I2C1)
		{
			NVIC_IRQ31_I2C1_EV_Enable();
			NVIC_IRQ32_I2C1_ER_Enable();
		}

		else
		{
			NVIC_IRQ33_I2C2_EV_Enable();
			NVIC_IRQ34_I2C2_ER_Enable();
		}
		I2Cx->SR1 = 0;
		I2Cx->SR2 = 0;
	}
	// Enable I2Cx Peripheral
	I2Cx->CR1 |= I2C_CR1_PE;
}


/**================================================================
* @Fn				-MCAL_I2C_DInit
* @brief		  	-Disable clock to I2Cx an Disable global interrupt
* @param [in] 		-I2Cx:  specified I2Cx x=[ 1 : 2 ]
* @retval 			-none
* Note				-none
*/
void MCAL_I2C_DInit(I2C_TypeDef* I2Cx)
{
	if( I2Cx == I2C1)
	{
		NVIC_IRQ31_I2C1_EV_Disable();
		NVIC_IRQ32_I2C1_ER_Disable();
		RCC_I2C1_CLK_Disable();
		I2Cx->CR1 &=~I2C_CR1_PE;
	}
	else
	{
		NVIC_IRQ33_I2C2_EV_Disable();
		NVIC_IRQ34_I2C2_ER_Disable();
		RCC_I2C2_CLK_Disable();
		I2Cx->CR1 &=~I2C_CR1_PE;
	}
}


/**================================================================
* @Fn				-MCAL_I2C_GPIO_Set_Pins
* @brief		  	-set PIN to specified I2C from 1 to 2 (set pin to act as alternate-function to I2Cx)
* @param [in] 		-I2Cx:  specified I2Cx x=[ 1 : 2 ]
* @retval 			-none
* Note				-none
*/
void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef* I2Cx)
{
	GPIO_Pinconfig_t pinCnfg;
	if(I2Cx == I2C1)
	{
		// PB6 :SCL
		// PB7 :SDA
		pinCnfg.pinNumber =GPIO_PIN_6;
		pinCnfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		pinCnfg.GPIO_OUTPUT_Speed=GPIO_speed_10M ;
		MCAL_GPIO_Init(GPIOB, &pinCnfg);

		pinCnfg.pinNumber =GPIO_PIN_7;
		pinCnfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		pinCnfg.GPIO_OUTPUT_Speed = GPIO_speed_10M;
		MCAL_GPIO_Init(GPIOB, &pinCnfg);
	}

	else
	{
		// PB10 :SCL
		// PB11 :SDA
		pinCnfg.pinNumber =GPIO_PIN_10;
		pinCnfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		pinCnfg.GPIO_OUTPUT_Speed= GPIO_speed_10M;
		MCAL_GPIO_Init(GPIOB, &pinCnfg);

		pinCnfg.pinNumber =GPIO_PIN_11;
		pinCnfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		pinCnfg.GPIO_OUTPUT_Speed = GPIO_speed_10M;
		MCAL_GPIO_Init(GPIOB, &pinCnfg);
	}
}


/**================================================================
* @Fn				-MCAL_I2C_Master_TX
* @brief		  	-send data by I2C from master to slave , data must be 8
* @param [in] 		-PTXBuffer: pointer to buffer to send data
* @param [in] 		-I2Cx:  specified I2Cx x=[ 1 : 2 ]
* @param [in] 		-Stop:  send stop or no
* @param [in] 		-Start:  send start or Repeated start
* @param [in] 		-DataLen:  length of data send
* @param [in] 		-Address: slave address
* @retval 			-none
* Note				-this function contains the I2C_Generate_Start and I2C_Generate_Stop function .
*/
void MCAL_I2C_Master_TX(I2C_TypeDef *I2Cx , uint16_t Address , uint8_t* PTXBuffer , uint32_t DataLen , Stop_Stute Stop , Repeated_Start Start)
{
	int i ;
	// Set the START bit
	I2C_Generate_Start(I2Cx, Start);
	while(!(Get_flag_stutus(I2Cx, EV5))) ;
	I2C_Send_Address(I2Cx, Address, Transmitter) ;
	while(!(Get_flag_stutus(I2Cx, EV6))) ;
	while(!(Get_flag_stutus(I2Cx, EV8_1))) ;
	 for( i=0 ; i<DataLen ; i++ )
	 {
		 I2Cx->DR = PTXBuffer[i];
		 while(!(Get_flag_stutus(I2Cx, EV8_1))) ;
	 }
	 while(!(Get_flag_stutus(I2Cx, EV8_2))) ;
	 if( Stop == WithStop )
	 {
		 I2C_Generate_Stop(I2Cx) ;
	 }
}


/**================================================================
* @Fn				-MCAL_I2C_Master_RX
* @brief		  	-receive data by I2C from  slave , data must be 8
* @param [out] 		-PTXBuffer: pointer to buffer to receive data
* @param [in] 		-I2Cx:  specified I2Cx x=[ 1 : 2 ]
* @param [in] 		-Stop:  send stop or no
* @param [in] 		-Start:  send start or Repeated start
* @param [in] 		-DataLen:  length of data send
* @param [in] 		-Address: slave address
* @retval 			-none
* Note				-this function contains the I2C_Generate_Start and I2C_Generate_Stop function .
*/
void MCAL_I2C_Master_RX(I2C_TypeDef *I2Cx , uint16_t Address , uint8_t* PRXBuffer , uint32_t DataLen , Stop_Stute Stop , Repeated_Start Start)
{
	int i ;
	// Set the START bit
	I2C_Generate_Start(I2Cx, Start);
	while(!(Get_flag_stutus(I2Cx, EV5))) ;
	I2C_Send_Address(I2Cx, Address, Recieve) ;
	while(!(Get_flag_stutus(I2Cx, EV6))) ;
	 for( i=0 ; i<DataLen ; i++ )
	 {
		 while(!(Get_flag_stutus(I2Cx, EV7))) ;
		 PRXBuffer[i]= I2Cx->DR ;
	 }
	 // not ACK
	I2Cx->CR1 &=~(I2C_CR1_ACK) ;
	 if( Stop == WithStop )
	 {
		 I2C_Generate_Stop(I2Cx) ;
	 }
	 //Set ACK
	 I2Cx->CR1 |=(I2C_CR1_ACK) ;
}





/**================================================================
* @Fn				-MCAL_I2C_Slave_TX
* @brief		  	-send data by I2C from  slave to master , data must be 8
* @param [in] 		-data:  the data to be send
* @param [in] 		-I2Cx:  specified I2Cx x=[ 1 : 2 ]
* @retval 			-none
* Note				-none.
*/
void MCAL_I2C_Slave_TX(I2C_TypeDef *I2Cx ,uint8_t data)
{
	I2Cx->DR = data;
}

/**================================================================
* @Fn				-MCAL_I2C_Slave_RX
* @brief		  	-Receive data by I2C from  master to slave , data must be 8
* @param [in] 		-I2Cx:  specified I2Cx x=[ 1 : 2 ]
* @retval 			-return data received from master .
* Note				-none.
*/
uint8_t MCAL_I2C_Slave_RX(I2C_TypeDef *I2Cx )
{
	return (uint8_t)I2Cx->DR;

}

//============================================================================================

/*
 * ===============================================================
 *
 *                      ISR Function Definitions
 *
 * ===============================================================
 */
void I2C1_EV_IRQHandler()
{
	volatile uint32_t Dummy_Read = 0;

	uint32_t Temp_1, Temp_2, Temp_3;

	Temp_3 = (I2C1->SR1 & (I2C_SR1_STOPF));		// Stop detection (slave mode)
	Temp_1 = (I2C1->CR2 & (I2C_CR2_ITEVTEN));	// Event interrupt enable
	Temp_2 = (I2C1->CR2 & (I2C_CR2_ITBUFEN));	// Buffer interrupt enable
	//check Stop detection
	if(Temp_1 && Temp_3)
	{
		//Cleared by software reading the SR1 register followed by a write in the CR1 register, or by hardware when PE=0
		I2C1->CR1 |= 0x0000;
		Slave_Status(I2C1 , I2C_EV_STOP);
	}
	// Check address matched.
	Temp_3 = (I2C1->SR1 & (I2C_SR1_ADDR));
	if(Temp_1 && Temp_3)
	{
		// Note: In slave mode, it is recommended to perform the complete clearing sequence (READ SR1 then READ SR2) after ADDR is set. Refer to Figure 272
		// Check master mode or slave mode
		if(I2C1->SR2 & (I2C_SR2_MSL))
		{
			// Master mode
		}
		else
		{
			// Slave mode
			Dummy_Read  = I2C1->SR1 ;
			Dummy_Read  = I2C1->SR2 ;
			Slave_Status(I2C1 , I2C_EV_ADDR_Matched) ;
		}
	}
	// Data register empty at slave_transmitter
	Temp_3 = (I2C1->SR1 & (I2C_SR1_TXE));
	if(Temp_1 && Temp_2 && Temp_3)
	{
		//Cleared by software writing to the DR register or by hardware after a start or a stop condition or when PE=0
		// Check master mode or slave mode
		if(I2C1->SR2 & (I2C_SR2_MSL))
		{
			// Master mode
		}
		else
		{
			// Slave mode
			Slave_Status(I2C1 , I2C_EV_DATA_REQ);
		}
	}
	// Data register not empty at slave receive
	Temp_3 = (I2C1->SR1 & (I2C_SR1_RXNE));
	if(Temp_1 && Temp_2 && Temp_3)
	{
		// Check master mode or slave mode
		if(I2C1->SR2 & (I2C_SR2_MSL))
		{
			// Master mode
		}
		else
		{
			// Slave mode
			Slave_Status(I2C1 , I2C_EV_DATA_RCV);
		}
	}
}




