/*
 * SPI_Driver.c
 *
 * Created: 13/09/2022 
 *  Author: Salama Mohamed
 */ 


#include "SPI_Driver.h"

/*
 * ===============================================================
 *
 *                      Generic Variable
 *
 * ===============================================================
 */
SPI_config_t* g_SPI_Config =NULL ;

//=================================================================================


/*
 * ===============================================================
 *
 *                      API Function Definitions
 *
 * ===============================================================
 */

void MCAL_SPI_Init(  SPI_config_t* SPI_Config )
{
	g_SPI_Config = SPI_Config  ;
	// Safety for register
	uint8_t Temp_SPCR=0 , Temp_SPSR=0 ;
	//Set mode
	if( SPI_Config->MODE == SPI_MODE_Master )
	{
		Temp_SPCR |=SPI_Config->MODE ;
	}
	else
	{
		Temp_SPCR &=SPI_Config->MODE ;
	}
	//set BaudRate_Prescalers
	if( SPI_Config->BaudRate_Prescalers == SPI_BaudRate_Prescalers_4)
	{
		Temp_SPCR &=SPI_Config->BaudRate_Prescalers ;
	}
	else
	{
		Temp_SPCR |=SPI_Config->BaudRate_Prescalers ;
	}
	switch( SPI_Config->Speed_Communication )
	{
	case SPI_Speed_Communication_Normal :
		Temp_SPSR &=SPI_Config->Speed_Communication ;
		break ;
	case SPI_Speed_Communication_Double_Speed :
		Temp_SPSR |=SPI_Config->Speed_Communication ;
		break ;	
	}
	//set Polarity
	if( SPI_Config->Polarity == SPI_Polarity_High_level_idle_state)
	{
		Temp_SPCR |=SPI_Config->Polarity ;
	}
	else
	{
		Temp_SPCR &=SPI_Config->Polarity ;
	}
	// set Phase
	if( SPI_Config->Phase == SPI_Phase_Data_Latched_On_First_Clock )
	{
		Temp_SPCR &=SPI_Config->Phase ;
	}
	else
	{
		Temp_SPCR |=SPI_Config->Phase ;
	}
	//set Data_Order
	if( SPI_Config->Data_Order == SPI_Data_Order_LSB_Transmitted_First )
	{
		Temp_SPCR |=SPI_Config->Data_Order ;
	}
	else
	{
		Temp_SPCR &=SPI_Config->Data_Order ;
	}
	// set IRQ_EN
	if( SPI_Config->IRQ_EN == SPI_IRQ_ENABLE_Disable)
	{
		Temp_SPCR &=SPI_Config->IRQ_EN ;
		EXTI_GLOBAL_Disable() ;
	}
	else
	{
		Temp_SPCR |=SPI_Config->IRQ_EN ;
		EXTI_GLOBAL_Enable() ;
	}
	SPI->SPSR = Temp_SPSR ;
	SPI->SPCR = Temp_SPCR ;
}


//=================================================================================