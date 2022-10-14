/*
 * I2C_Driver.c
 *
 * Created: 9/25/2022 3:18:46 PM
 *  Author: salama
 */ 

#include "I2C_Driver.h"

/*
 * ===============================================================
 *
 *                      Generic Variable
 *
 * ===============================================================
 */

I2C_config_t* g_I2C_Config = NULL ;

//===============================================================================


/*
 * ===============================================================
 *
 *                      API Function Definitions
 *
 * ===============================================================
 */


/**================================================================
* @Fn				-MCAL_I2C_Init
* @brief		  	-Initializes the I2C  according to the specified parameters in the I2C_Config
* 					 @ ref  I2C_Speed_MODE_Define  and  @ ref  I2C_Own_Address_Define  and ....
* @param [in] 		-I2C_Config: configuration information for  I2C 
* 					 take a pointer to function (this function calling at interrupt)
* @retval 			-none
* Note				-none
*/
void MCAL_I2C_Init(I2C_config_t* I2C_Config)
{
	g_I2C_Config = I2C_Config ;
	I2C->TWAR = I2C_Config->Own_Address ;
	I2C->TWSR = I2C_Config->Prescaler  ;
	if(I2C_Config->IRQ_EN == I2C_IRQ_ENABLE_Enable)
	{
		TWCR |=I2C_Config->IRQ_EN ;
		EXTI_GLOBAL_Enable();
	}
	else
	{
		TWCR &=I2C_Config->IRQ_EN ;
		EXTI_GLOBAL_Disable() ;
	}
	I2C->TWBR =(uint8_t)(((F_CPU/I2C_Config->Speed_MODE)-16)/(2*1)) ;  
	// enable I2C and ACK 
	TWCR |=(1<<2 ) | (1<<6) ;
}


/**================================================================
* @Fn				-MCAL_I2C_Master_TX
* @brief		  	-send data by I2C from master to slave , data must be 8 
* @param [in] 		-PTXBuffer:  the data to be send
* @param [in] 		-Address: slave address
* @retval 			-none
* Note				-this function contains the I2C_Generate_Start and I2C_Generate_Stop function .
*/
void MCAL_I2C_Master_TX( uint8_t Address , uint8_t* PTXBuffer , uint8_t Datalen  , stop_cmd Stop )
{
	uint8_t i ;
	// send start bit
	I2C_Generate_Start();
	// send address slave
	I2C->TWDR = (Address) ;
	TWCR |=(1<<7) ;
	while(!(Get_flag_stutus(TWINT))); // Wait until receive ACK from Slave
	if(Get_flag_stutus(SLA_W_Transmitted))
	{
		//while(1);
		//ERROR
	}
	// send data
	for(i=0 ; i<Datalen ; i++)
	{
		I2C->TWDR =PTXBuffer[i];
		TWCR |=(1<<7) ;
		while(!(Get_flag_stutus(TWINT))); // Wait until receive ACK from Slave
		if(Get_flag_stutus(M_DATA_Transmitted))
		{
			//ERROR
		}
	}
	// send stop bit
	if ( Stop == With_Stop)
	{
		I2C_Generate_Stop();
	}
}



/**================================================================
* @Fn				-MCAL_I2C_Master_RX
* @brief		  	-Receive  data by I2C from slave tto master , data must be 8 .
* @param [in] 		-Address: slave address
* @retval 			-none
* Note				-this function contains the I2C_Generate_Start and I2C_Generate_Stop function .
*/
uint8_t MCAL_I2C_Master_RX( uint8_t Address )
{
	uint8_t data ;
	// send start bit
	I2C_Generate_Start();
	// send address slave
	I2C->TWDR = (Address) ;
	TWCR |=(1<<7) ;  
	while(!(Get_flag_stutus(TWINT)));  // Wait until receive ACK from Slave
	if(Get_flag_stutus(SLA_R_Transmitted))
	{
		//ERROR
	}
	// receive data from slave	
	TWCR |=(1<<7) ; 
	while(!(Get_flag_stutus(TWINT))); // Wait until receive ACK from Slave ( complete receive data )
	if(Get_flag_stutus(M_DATA_Received))
	{
		//ERROR
	}
	// return data and generate stop 
	data= I2C->TWDR ;
	I2C_Generate_Stop();
	return data ;
}


/**================================================================
* @Fn				-I2C_Generate_Start
* @brief		  	-generate start condition to start transmitter .
* @retval 			-none
* Note				-none
*/
void I2C_Generate_Start( void )
{
	TWCR =(1<<7) | (1<<5) | (1<<2) ;
	while(!(Get_flag_stutus(TWINT)));
	if(Get_flag_stutus(START_Transmitted))
	{
		//ERROR
	}
	// clear start bit
	TWCR &=~(160) ;
}



/**================================================================
* @Fn				-Get_flag_stutus
* @brief		  	-check the current state to I2C ( busy , receive data , receive address ...... ) .
* @param [in] 		-flag: the status to be check 
* @retval 			-FlagStatus 
* Note				-none
*/
FlagStatus Get_flag_stutus(  Status flag )
{
	FlagStatus current_state ;
	switch( flag )
	{
	case TWINT :
		if (TWCR & 1<<7 )
			current_state=SET ;
		else
			current_state=RESET ;
		break;
	case START_Transmitted :
		if ((I2C->TWSR & 0XF8) != 0X08 )
			current_state=SET ;
		else
			current_state=RESET ;
		break;
	case SLA_W_Transmitted :
		if ((I2C->TWSR & 0XF8) != 0X18 )
			current_state=SET ;
		else
			current_state=RESET ;
		break;
	case M_DATA_Transmitted :
		if ((I2C->TWSR & 0XF8) != 0X28 )
			current_state=SET ;
		else
			current_state=RESET ;
		break;
	case SLA_W_Received :
		if ((I2C->TWSR & 0XF8) != 0X60 )
			current_state=SET ;
		else
			current_state=RESET ;
		break;
	case S_DATA_Received :
		if ((I2C->TWSR & 0XF8) != 0X80 )
			current_state=SET ;
		else
			current_state=RESET ;
		break;
	case SLA_R_Transmitted :
		if ((I2C->TWSR & 0XF8) != 0X40 )
			current_state=SET ;
		else
			current_state=RESET ;
		break;
	case M_DATA_Received :
		if ((I2C->TWSR & 0XF8) != 0X50 )
			current_state=SET ;
		else
			current_state=RESET ;
		break;
	case SLA_R_Received :
		if ((I2C->TWSR & 0XF8) != 0XA8 )
			current_state=SET ;
		else
			current_state=RESET ;
		break;
	case S_DATA_Transmitted :
		if ((I2C->TWSR & 0XF8) != 0XB8 )
			current_state=SET ;
		else
			current_state=RESET ;
		break;
	}
	return current_state ;
}



/**================================================================
* @Fn				-I2C_Generate_Stop
* @brief		  	-generate stop condition to end transmitter .
* @retval 			-none
* Note				-none
*/
void I2C_Generate_Stop(void )
{	
	TWCR =(1<<7) | (1<<4) | (1<<2) ;
}



/**================================================================
* @Fn				-MCAL_I2C_Slave_TX
* @brief		  	-send data by I2C from  slave to master , data must be 8
* @param [in] 		-PTXBuffer:  the data to be send
* @retval 			-none
* Note				-none.
*/
void MCAL_I2C_Slave_TX( uint8_t PTXBuffer  )
{
	// wait until receive address from master
	while(!(Get_flag_stutus(TWINT)));
	if(Get_flag_stutus(SLA_R_Received))
	{
		//ERROR
	}
	// send data to master
	I2C->TWDR = PTXBuffer ;
	TWCR |=(1 << 7)  ; 
	while(!(Get_flag_stutus(TWINT)));
	if(Get_flag_stutus(S_DATA_Transmitted))
	{
		//ERROR
	}
	// clear flag
	TWCR |=(1 << 7) ;
}



/**================================================================
* @Fn				-MCAL_I2C_Slave_RX
* @brief		  	-Receive data by I2C from  master to slave , data must be 8
* @retval 			-return data received from master .
* Note				-none.
*/
uint8_t MCAL_I2C_Slave_RX( void )
{
	// set ACK , enable I2C , clear flag
	TWCR =(1 << 7) | (1 << 6) | (1 << 2);
	// wait until receive address
	while(!(Get_flag_stutus(TWINT))); 
	if(Get_flag_stutus(SLA_W_Received))
	{
		//ERROR
	}
	// receive data from master
	TWCR =(1 << 7) | (1 << 6) | (1 << 2);
	while(!(Get_flag_stutus(TWINT)));
	if(Get_flag_stutus(S_DATA_Received))
	{
		//ERROR
	}
	// return data
	return I2C->TWDR;
}

/*
 * ===============================================================
 *
 *                      ISR Function Definitions
 *
 * ===============================================================
 */


void __vector_19 (void) __attribute__((signal));
void __vector_19 (void)
{
	g_I2C_Config->P_IRQ_CALL() ;
}

//====================================================================