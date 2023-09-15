/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Salama Mohamed
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */

/*
 **************************************************************
 *************************Include File ************************
 **************************************************************
 */
#include"stm32_f103c6_GPIO.h"
#include "stm32f103x6.h"
#include "delay.h"
#include "stm32_f103c6_CAN.h"
/*
 **************************************************************
 *************************Global Variable **********************
 **************************************************************
 */
CAN_Message_Info_t Message_Info;
CAN_Message_Info_t RX_Message_Info ;
uint8_t Data[]={1,2,3,4,5,6,7,8};
uint8_t Data1[8]={0};
uint8_t Data2[]={'S','A','L','A','M','A',1,0};
uint8_t Data3[]={'S','A','L','A','M','A',1,1};
uint8_t pMailbox;
Can_Mode_t mode;
/*
 **************************************************************
 *************************Init Functions **********************
 **************************************************************
 */
void Clock_INIT(void)
{
    //set on the clock for PORTA
    RCC_GPIOA_CLK_EN();
    //set on the clock for PORTB
    RCC_GPIOB_CLK_EN();
    //set on the clock for AFIO
    RCC_GPIOC_CLK_EN();
    RCC_AFIO_CLK_EN();
    RCC_TIM2_CLK_Enable();
    RCC_TIM3_CLK_Enable();
    RCC_TIM4_CLK_Enable();
    RCC_ADC1_CLK_Enable();
    RCC_USART1_CLK_Enable();
    RCC_CAN_CLK_Enable();
}

void GPIO_Init(void)
{
	GPIO_Pinconfig_t PIN;
	PIN.GPIO_MODE=GPIO_MODE_OUTPUT_OD;
	PIN.GPIO_OUTPUT_Speed=GPIO_speed_2M;
	PIN.pinNumber=GPIO_PIN_13;
	MCAL_GPIO_Init(GPIOC, &PIN);
}
/*
 **************************************************************
 *************************Callback*****************************
 **************************************************************
 */
void MCAL_CAN_FIFO_0_Receive_Callback(void)
{
	while(1)
	{
		MCAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
		delay_ms(1000);
		MCAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
		delay_ms(1000);
	}
}
void Callback(void)
{
	while(1)
	{
		MCAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
		delay_ms(100);
		MCAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
		delay_ms(100);
	}
}
/*
 **************************************************************
 *************************Main *********************************
 **************************************************************
 */
int main(void)
{
	//Init
    Clock_INIT();
    GPIO_Init();
    // Get CAN Mode
    mode=MCAL_CAN_Get_Mode();
    //TX Information Message
    Message_Info.DLC=5;
    Message_Info.IDE=CAN_IDE_Standard;
    Message_Info.RTR=CAN_RTR_Data_Frame;
    Message_Info.Std_ID=0X7FF;
    //Configuration CAN
    CAN_Config_t Can_Config ;
    Can_Config.Mode=CAN_MODE_Loop_back_Silent;
    Can_Config.BaudRate=CAN_BaudRate_800;
    Can_Config.AutoBusOff=CAN_AutoBusOff_Disable;
    Can_Config.AutoRetransmission=CAN_AutoRetransmission_Disable;
	Can_Config.Fifo_Locked=CAN_Fifo_Locked_Enable;
	Can_Config.RX0_IRQ_EN=CAN_RX0_IRQ_EN_Enable;
	Can_Config.RX1_IRQ_EN=CAN_RX1_IRQ_EN_Disable;
	Can_Config.SCE_IRQ_EN=CAN_SCE_IRQ_EN_Disable;
	Can_Config.TX_IRQ_EN=CAN_TX_IRQ_EN_Disable;
	Can_Config.P_TX_IRQ=NULL;
	Can_Config.P_RX0_IRQ=Callback;
	MCAL_CAN_Init(&Can_Config);
	// Get CAN Mode
	mode=MCAL_CAN_Get_Mode();
	//Configuration Filter Bank 0
	CAN_Filter_Config_t Filter_Config;
	Filter_Config.Filter_Bank=CAN_Filter_Bank_0;
	Filter_Config.Filter_FIFO_Assignment=CAN_Filter_FIFO_Assignment_FIFO0;
	Filter_Config.Filter_ID=0XFFE0FFE8;
	Filter_Config.Filter_Mask_ID=0X1FF01FF8;
	Filter_Config.Filter_Mode=CAN_Filter_Mode_List;
	Filter_Config.Filter_Scale=CAN_Filter_Scale_16;
	MCAL_CAN_Config_Filter(&Filter_Config);
	//Configuration Filter Bank 1
	Filter_Config.Filter_Bank=CAN_Filter_Bank_1;
	Filter_Config.Filter_FIFO_Assignment=CAN_Filter_FIFO_Assignment_FIFO1;
	Filter_Config.Filter_ID=0X1FE01FE8;
	Filter_Config.Filter_Mask_ID=0X1FF01FF8;
	Filter_Config.Filter_Mode=CAN_Filter_Mode_List;
	Filter_Config.Filter_Scale=CAN_Filter_Scale_16;
	MCAL_CAN_Config_Filter(&Filter_Config);
	//Start CAN
	MCAL_CAN_Start();
	// Get CAN Mode
	mode=MCAL_CAN_Get_Mode();
	//Transmit Message
	MCAL_CAN_Add_TX_Message(&Message_Info,Data,&pMailbox);
	//Receive Message
	MCAL_CAN_Receive_Message(&RX_Message_Info,Data1);
	//CAN Sleep
	MCAL_CAN_Request_Sleep();
	// Get CAN Mode
	mode=MCAL_CAN_Get_Mode();
	MCAL_CAN_Init(&Can_Config);
	// Get CAN Mode
	mode=MCAL_CAN_Get_Mode();
	//Start CAN
	MCAL_CAN_Start();
	// Get CAN Mode
	mode=MCAL_CAN_Get_Mode();
    while(1)
    {

    }
}
/*
 **************************************************************
 *************************End *********************************
 **************************************************************
 */
