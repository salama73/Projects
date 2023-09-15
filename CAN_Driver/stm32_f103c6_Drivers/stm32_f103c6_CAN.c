/*
 * stm32_f103c6_CAN.c
 *  Created on: 6/9/2023
 *  Author: Salama mohamed
 */

#include "stm32_f103c6_CAN.h"

CAN_Config_t g_Can_Config;

/**================================================================
* @Fn				-MCAL_CAN_Init
* @brief		  	-Initializes the CAN according to the specified parameters in the Can_Config
* 					 @ ref  CAN_MODE_Define  and @ ref  CAN_Fifo_Locked_Define and @ ref  CAN_BaudRate_Define and ....
* @param [in] 		-Can_Config: configuration information for the specified Can
* 					 take a pointers to function (this function calling at interrupt)
* @retval 			-Can_Status_t: status of Can hardware (CAN_OK,CAN_ERROR,...)
* Note				-at using MCAL_CAN_Init after MCAL_CAN_DeInit must Enable RCC Clock for can
*/
Can_Status_t MCAL_CAN_Init(CAN_Config_t* Can_Config)
{
	Can_Status_t status;
	//Check Message_Info pointer
	if(Can_Config==NULL)
	{
		status=CAN_ERROR;
		return status;
	}
	//Software sets this bit to request the CAN hardware to enter initialization mode.
	CAN_MCR &=~(1<<1);
	CAN_MCR |=(1<<0);
	//CAN bit timing register (baud Rate)
	CAN_BTR=0X0000000;
	switch (Can_Config->BaudRate)
	{
		case CAN_BaudRate_1000:
			CAN_BTR |=0x00050000;
			break;
		case CAN_BaudRate_800:
			CAN_BTR |=0x00070000;
			break;
		case CAN_BaudRate_500:
			CAN_BTR |=0x001C0000;
			break;
		case CAN_BaudRate_250:
			CAN_BTR |=0x001C0001;
			break;
		case CAN_BaudRate_125:
			CAN_BTR |=0x001C0003;
			break;
		case CAN_BaudRate_100:
			CAN_BTR |=0x001C0004;
			break;
		case CAN_BaudRate_50:
			CAN_BTR |=0x001C0009;
			break;
		default:
			status=CAN_ERROR;
			break;
	}
	//Configure CAN operating mode
	switch (Can_Config->Mode)
	{
		case CAN_MODE_Silent:
			CAN_BTR |=(1<<31);
			CAN_BTR &=~(1<<30);
			break;
		case CAN_MODE_Loop_back:
			CAN_BTR |=(1<<30);
			CAN_BTR &=~(1<<31);
			break;
		case CAN_MODE_Loop_back_Silent:
			CAN_BTR |=(1<<31);
			CAN_BTR |=(1<<30);
			break;
		case CAN_MODE_Normal:
			CAN_BTR &=~(1<<31);
			CAN_BTR &=~(1<<30);
			break;
		default:
			status=CAN_ERROR;
			break;
	}
	// Configure recover from Bus-Off  either automatically or on software
	switch (Can_Config->AutoBusOff)
	{
		case CAN_AutoBusOff_Disable:
			CAN_MCR &=~(1<<6);
			break;
		case CAN_AutoBusOff_Enable:
			CAN_MCR |=(1<<6);
			break;
		default:
			status=CAN_ERROR;
			break;
	}
	//Enable or disable the non automatic retransmission mode.
	switch (Can_Config->AutoRetransmission)
	{
		case CAN_AutoRetransmission_Disable:
			CAN_MCR |=(1<<4);
			break;
		case CAN_AutoRetransmission_Enable:
			CAN_MCR &=~(1<<4);
			break;
		default:
			status=CAN_ERROR;
			break;
	}
	// Enable or disable FIFO lock function
	switch (Can_Config->Fifo_Locked)
	{
		case CAN_Fifo_Locked_Disable:
			CAN_MCR &=~(1<<3);
			break;
		case CAN_Fifo_Locked_Enable:
			CAN_MCR |=(1<<3);
			break;
		default:
			status=CAN_ERROR;
			break;
	}
	// Configure FIFO priority By identifier (Enable) or By transmit request order
	switch (Can_Config->Transmit_Priority)
	{
		case CAN_Fifo_Transmit_Priority_Disable:
			CAN_MCR |=(1<<2);
			break;
		case CAN_Fifo_Transmit_Priority_Enable:
			CAN_MCR &=~(1<<2);
			break;
		default:
			status=CAN_ERROR;
			break;
	}
	// disable or enable Transmit interrupt
	switch (Can_Config->TX_IRQ_EN)
	{
		case CAN_TX_IRQ_EN_Disable:
			CAN_IER &=~(1<<0);
			//assign null pointer to call back function
			Can_Config->P_TX_IRQ=NULL;
			break;
		case CAN_TX_IRQ_EN_Enable:
			CAN_IER |=(1<<0);
			NVIC_IRQ19_CAN_TX_Enable();
			break;
		default:
			status=CAN_ERROR;
			break;
	}
	// disable or enable Receive Fifo 0 interrupt
	switch (Can_Config->RX0_IRQ_EN)
	{
		case CAN_RX0_IRQ_EN_Disable:
			//FIFO message pending interrupt disable
			CAN_IER &=~(1<<1);
			//FIFO full interrupt disable
			CAN_IER &=~(1<<2);
			//FIFO overrun interrupt disable
			CAN_IER &=~(1<<3);
			//assign null pointer to call back function
			Can_Config->P_RX0_IRQ=NULL;
			break;
		case CAN_RX0_IRQ_EN_Enable:
			//FIFO message pending interrupt enable
			CAN_IER |=(1<<1);
			//FIFO full interrupt enable
			CAN_IER |=(1<<2);
			//FIFO overrun interrupt enable
			CAN_IER |=(1<<3);
			NVIC_IRQ20_CAN_RX0_Enable();
			break;
		default:
			status=CAN_ERROR;
			break;
	}
	// disable or enable Receive Fifo 1 interrupt
	switch (Can_Config->RX1_IRQ_EN)
	{
		case CAN_RX1_IRQ_EN_Disable:
			//FIFO message pending interrupt disable
			CAN_IER &=~(1<<4);
			//FIFO full interrupt disable
			CAN_IER &=~(1<<5);
			//FIFO overrun interrupt disable
			CAN_IER &=~(1<<6);
			//assign null pointer to call back function
			Can_Config->P_RX1_IRQ=NULL;
			break;
		case CAN_RX1_IRQ_EN_Enable:
			//FIFO message pending interrupt enable
			CAN_IER |=(1<<4);
			//FIFO full interrupt enable
			CAN_IER |=(1<<5);
			//FIFO overrun interrupt enable
			CAN_IER |=(1<<6);
			NVIC_IRQ21_CAN_RX1_Enable();
			break;
		default:
			status=CAN_ERROR;
			break;
	}
	// disable or enable Error interrupt
	switch (Can_Config->SCE_IRQ_EN)
	{
		case CAN_SCE_IRQ_EN_Disable:
			// general Error interrupt disable
			CAN_IER &=~(1<<15);
			 //Error warning interrupt disable
			CAN_IER &=~(1<<8);
			 //Error passive interrupt disable
			CAN_IER &=~(1<<9);
			 //Bus-off interrupt disable
			CAN_IER &=~(1<<10);
			//assign null pointer to call back function
			Can_Config->P_SCE_IRQ=NULL;
			//1: ERRI bit will be set when the error code in LEC[2:0] is set by hardware on error detection.
			// Bit dominant Error or  CRC Error ....
			CAN_IER &=~(1<<11);
			break;
		case CAN_SCE_IRQ_EN_Enable:
			// general Error interrupt enable
			CAN_IER |=(1<<15);
			 //Error warning interrupt enable
			CAN_IER |=(1<<8);
			 //Error passive interrupt enable
			CAN_IER |=(1<<9);
			 //Bus-off interrupt enable
			CAN_IER |=(1<<10);
			//1: ERRI bit will be set when the error code in LEC[2:0] is set by hardware on error detection.
			// Bit dominant Error or  CRC Error ....
			CAN_IER |=(1<<11);
			NVIC_IRQ22_CAN_SCE_Enable();
			break;
		default:
			status=CAN_ERROR;
			break;
	}
	/*can set pin mode
	 PA12 CAN_TX (Transmit data line) Alternate function push-pull
	 PA11 CAN_RX (Receive data line) Input floating / Input pull-up
	 */
	GPIO_Pinconfig_t PIN;
	//CAN_TX
	PIN.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
	PIN.GPIO_OUTPUT_Speed=GPIO_speed_10M;
	PIN.pinNumber=GPIO_PIN_12;
	MCAL_GPIO_Init(GPIOA, &PIN);
	//CAN_RX
	PIN.GPIO_MODE=GPIO_MODE_INPUT_PU;
	PIN.pinNumber=GPIO_PIN_11;
	MCAL_GPIO_Init(GPIOA, &PIN);
	g_Can_Config=*Can_Config;
	return status;
}
/**================================================================
* @Fn				-MCAL_CAN_DeInit
* @brief		  	-Disable all interrupt and CAN_MCR Register for can
* @param [in] 		-None
* @retval 			-Can_Status_t	status of Can hardware (CAN_OK,CAN_ERROR,...)
* Note				-None
*/
void MCAL_CAN_DeInit(void)
{
	//Disable all interrupt
	NVIC_IRQ19_CAN_TX_Disable();
	NVIC_IRQ20_CAN_RX0_Disable();
	NVIC_IRQ21_CAN_RX1_Disable();
	NVIC_IRQ22_CAN_SCE_Disable();
	/*
	bxCAN software master reset
	Force a master reset of the bxCAN -> Sleep mode activated after reset (FMP bits and
	CAN_MCR register are initialized to the reset values). This bit is automatically reset to 0.
	*/
	CAN_MCR |=(1<<15);
	//Disable Clock
	RCC_CAN_CLK_Disable();
}
/**================================================================
* @Fn				-MCAL_CAN_Config_Filter
* @brief		  	-Initializes the CAN Filters to the specified parameters in the Filter_Config
* 					 @ ref  CAN_Filter_Bank_Define  and @ ref  CAN_Filter_Mode_Define and @ ref  CAN_Filter_Scale_Define and ....
* @param [in] 		-Filter_Config: configuration information for the specified Can Filter
* @retval 			-Can_Status_t	status of Can hardware (CAN_OK,CAN_ERROR,...)
* Note				-None
*/
Can_Status_t MCAL_CAN_Config_Filter(CAN_Filter_Config_t* Filter_Config)
{
	Can_Status_t status;
	//Check Message_Info pointer
	if(Filter_Config==NULL)
	{
		status=CAN_ERROR;
		return status;
	}
	// Current Filter Bank
	CAN_Filter_Bank_TypeDef* Current_Bank ;
	Current_Bank=NULL;
	switch (Filter_Config->Filter_Bank)
	{
		case CAN_Filter_Bank_0:
			Current_Bank=CAN_FBank_0;
			break;
		case CAN_Filter_Bank_1:
			Current_Bank=CAN_FBank_1;
			break;
		case CAN_Filter_Bank_2:
			Current_Bank=CAN_FBank_2;
			break;
		case CAN_Filter_Bank_3:
			Current_Bank=CAN_FBank_3;
			break;
		case CAN_Filter_Bank_4:
			Current_Bank=CAN_FBank_4;
			break;
		case CAN_Filter_Bank_5:
			Current_Bank=CAN_FBank_5;
			break;
		case CAN_Filter_Bank_6:
			Current_Bank=CAN_FBank_6;
			break;
		case CAN_Filter_Bank_7:
			Current_Bank=CAN_FBank_7;
			break;
		case CAN_Filter_Bank_8:
			Current_Bank=CAN_FBank_8;
			break;
		case CAN_Filter_Bank_9:
			Current_Bank=CAN_FBank_9;
			break;
		case CAN_Filter_Bank_10:
			Current_Bank=CAN_FBank_10;
			break;
		case CAN_Filter_Bank_11:
			Current_Bank=CAN_FBank_11;
			break;
		case CAN_Filter_Bank_12:
			Current_Bank=CAN_FBank_12;
			break;
		case CAN_Filter_Bank_13:
			Current_Bank=CAN_FBank_13;
			break;
		default:
			status=CAN_ERROR;
			break;
	}
	// To configure a filter bank it must be deactivated by clearing the FACT bit in the CAN_FAR register
	// Initialization mode for the filters
	CAN_FMR |=(1<<0);
	//Filter x is not active
	CAN_FA1R &=~(1<<Filter_Config->Filter_Bank);
	// The filter scale is configured by means of the corresponding FSCx bit in the CAN_FS1R register
	switch (Filter_Config->Filter_Scale)
	{
		case CAN_Filter_Scale_16:
			CAN_FS1R &=~(1<<Filter_Config->Filter_Bank);
			// configure filter bank
			Current_Bank->CAN_FiR1=(Filter_Config->Filter_ID &(0xffff))|((Filter_Config->Filter_Mask_ID &(0xffff))<<16);
			Current_Bank->CAN_FiR2=((Filter_Config->Filter_ID &(0xffff0000))>>16)|(Filter_Config->Filter_Mask_ID &(0xffff0000));
			break;
		case CAN_Filter_Scale_32:
			CAN_FS1R |=(1<<Filter_Config->Filter_Bank);
			// configure filter bank
			Current_Bank->CAN_FiR1=Filter_Config->Filter_ID;
			Current_Bank->CAN_FiR2=Filter_Config->Filter_Mask_ID;
			break;
		default:
			status=CAN_ERROR;
			break;
	}
	//The identifier list or identifier mask mode is configured by means of the FBMx bits in the CAN_FM1R register.
	switch (Filter_Config->Filter_Mode)
	{
		case CAN_Filter_Mode_Mask:
			CAN_FM1R &=~(1<<Filter_Config->Filter_Bank);
			break;
		case CAN_Filter_Mode_List:
			CAN_FM1R |=(1<<Filter_Config->Filter_Bank);
			break;
		default:
			status=CAN_ERROR;
			break;
	}
	//The message passing through this filter will be stored in the specified FIFO
	switch (Filter_Config->Filter_FIFO_Assignment)
	{
		case CAN_Filter_FIFO_Assignment_FIFO0:
			CAN_FFA1R &=~(1<<Filter_Config->Filter_Bank);
			break;
		case CAN_Filter_FIFO_Assignment_FIFO1:
			CAN_FFA1R |=(1<<Filter_Config->Filter_Bank);
			break;
		default:
			status=CAN_ERROR;
			break;
	}
	// Filter Bank active mode
	CAN_FMR &=~(1<<0);
	//Filter x is not active
	CAN_FA1R |=(1<<Filter_Config->Filter_Bank);
	return status;
}
/**================================================================
* @Fn				-MCAL_CAN_Start
* @brief		  	-This function is used to enter the can to the normal Mode.
* @param [in] 		-None
* @retval 			-Can_Status_t	status of Can hardware (CAN_OK,CAN_ERROR,...)
* Note				-None
*/
Can_Status_t MCAL_CAN_Start(void)
{
	// enter Normal mode
	CAN_MCR &=~(1<<0);
	CAN_MCR &=~(1<<1);
	/*
	 This bit is cleared by hardware when the CAN hardware has left the initialization mode (to
	 be synchronized on the CAN bus). To be synchronized the hardware has to monitor a
	 sequence of 11 consecutive recessive bits on the CAN RX signal.
	 */
	while(CAN_MSR & (1<<0));
}
/**================================================================
* @Fn				-MCAL_CAN_Get_TX_Mailboxes_Empty
* @brief		  	-Queries and returns the number of available empty transmit mailboxes in the CAN unit
* 					 Transmi_mailbox_0,Transmi_mailbox_1 or Transmi_mailbox_2
* @retval 			-Can_Status_t	The number of an empty transmit mailbox (Transmi_mailbox_0,Transmi_mailbox_1 or Transmi_mailbox_2)
* Note				-None
*/
uint8_t MCAL_CAN_Get_TX_Mailboxes_Empty(void)
{
	if(CAN_TSR & 1<<26)
		return Transmi_mailbox_0;
	else if (CAN_TSR & 1<<27)
		return Transmi_mailbox_1;
	else if (CAN_TSR & 1<<28)
		return Transmi_mailbox_2;
	else
		return Transmi_mailbox_Full;
}
/**================================================================
* @Fn				-MCAL_CAN_Add_TX_Message
* @brief		  	-Adds a new transmit message to the CAN transmit mailbox with the provided data
* 					 and retrieves the assigned mailbox.
* @param [in] 		-Message_Info: Pointer to a structure containing information about the CAN message,
* 					 including ID , ID Type , DLC, and transmission mode.
* @param [in] 		-Data: Pointer to an array containing the data to be transmitted.
* @param [output] 	-pMailbox: Pointer to a variable that will store the assigned transmit mailbox number.
* @retval 			-Can_Status_t	status of Can hardware (CAN_OK,CAN_ERROR,...)
* Note				-None
*/
Can_Status_t MCAL_CAN_Add_TX_Message(CAN_Message_Info_t* Message_Info, uint8_t Data[], uint8_t *Mailbox)
{
	Can_Status_t status;
	status=CAN_OK;
	//Check Message_Info pointer
	if(Message_Info==NULL)
	{
		status=CAN_ERROR;
		return status;
	}
	else
	{
		//CAN_OK;
	}
	uint8_t Mailboxe=0;
	CAN_TX_mailbox_TypeDef* Current_Mailboxe=NULL;
	Mailboxe=MCAL_CAN_Get_TX_Mailboxes_Empty();
	*Mailbox=Mailboxe;
	switch (Mailboxe)
	{
		case Transmi_mailbox_0:
			Current_Mailboxe=CAN_TX_mailbox_0;
			break;
		case Transmi_mailbox_1:
			Current_Mailboxe=CAN_TX_mailbox_1;
			break;
		case Transmi_mailbox_2:
			Current_Mailboxe=CAN_TX_mailbox_2;
			break;
		default:
			status=CAN_ERROR;
			break;
	}
	//reset Current Mailboxe
	Current_Mailboxe->CAN_TDHxR=0X00000000;
	Current_Mailboxe->CAN_TDLxR=0X00000000;
	Current_Mailboxe->CAN_TDTxR=0X00000000;
	Current_Mailboxe->CAN_TIxR=0X00000000;
	//set the type of frame
	switch (Message_Info->RTR)
	{
		case CAN_RTR_Remote_Frame:
			Current_Mailboxe->CAN_TIxR |=(1<<1);
			break;
		case CAN_RTR_Data_Frame:
			Current_Mailboxe->CAN_TIxR &=~(1<<1);
			break;
		default:
			status=CAN_ERROR;
			break;
	}
	//set the identifier
	switch (Message_Info->IDE)
	{
		case CAN_IDE_Standard:
			Current_Mailboxe->CAN_TIxR &=~(1<<2);
			Current_Mailboxe->CAN_TIxR |=(uint32_t)(Message_Info->Std_ID<<21);
			break;
		case CAN_IDE_Extended:
			Current_Mailboxe->CAN_TIxR |=(1<<2);
			Current_Mailboxe->CAN_TIxR |=(uint32_t)(Message_Info->Ext_ID<<3);
			break;
		default:
			status=CAN_ERROR;
			break;
	}
	//length of the frame
	if(Message_Info->DLC != CAN_DLC_0)
	{
		Current_Mailboxe->CAN_TDTxR |=(Message_Info->DLC<<0);
	}
	else
	{
		Current_Mailboxe->CAN_TDTxR &=~(Message_Info->DLC<<0);
	}
	//Data
	for(uint8_t i=0 ; i<(uint8_t)Message_Info->DLC ; i++)
	{
		if(i<4)
		{
			Current_Mailboxe->CAN_TDLxR |=Data[i]<<(8*i);
		}
		else
		{
			Current_Mailboxe->CAN_TDHxR |=Data[i]<<(8*(i-4));
		}
	}
	// Transmit mailbox request
	Current_Mailboxe->CAN_TIxR |=(1<<0);
	// Wait for the previous transmission was successful
	//while(!(CAN_TSR & (1<<1)));
	return status;
}
/**================================================================
* @Fn				-MCAL_CAN_Set_BaudRate
* @brief		  	-Configures the CAN bus baud rate settings according to BaudRate_Config.
* 					 @ ref  number of time quanta in Bit Segment 1,number of time quanta in Bit Segment 2 and prescalers
* @param [in] 		-BaudRate_Config:  Pointer to a structure containing the CAN bus baud rate configuration parameters.
* @retval 			-Can_Status_t	status of Can hardware (CAN_OK,CAN_ERROR,...)
* Note				-This function allows the user to configure the CAN bus baud rate settings according to their requirements.
*                 	 It takes a pointer to a structure 'BaudRate_Config' that contains the necessary parameters for configuring
*                 	 the baud rate, such as prescaler and time quantum settings.
*/
Can_Status_t MCAL_CAN_Set_BaudRate(CAN_BaudRate_Config_t* BaudRate_Config)
{
	uint32_t CAN_BTR_temp=0;
	CAN_BTR_temp=CAN_BTR;
	CAN_BTR_temp &=0XC0000000;
	Can_Status_t status;
	status=CAN_OK;
	//Check Message_Info pointer
	if(BaudRate_Config==NULL)
	{
		status=CAN_ERROR;
		return status;
	}
	//set Prescaler
	CAN_BTR_temp |=(BaudRate_Config->Prescaler-1)<<0;
	//set TimeSeg1
	CAN_BTR_temp |=(BaudRate_Config->TimeSeg1-1)<<16;
	//set TimeSeg2
	CAN_BTR_temp |=(BaudRate_Config->TimeSeg2-1)<<20;
	CAN_BTR=CAN_BTR_temp;
	return status;
}
/**================================================================
* @Fn				-MCAL_CAN_Abort_TX_Message
* @brief		  	-Aborts a pending transmit message in the specified transmit mailbox.
* @param [in] 		-TX_Mailboxe: The number of the transmit mailbox to abort the message in.
* @retval 			-Can_Status_t	status of Can hardware (CAN_OK,CAN_ERROR,...)
* Note				-None
*/
Can_Status_t MCAL_CAN_Abort_TX_Message(uint32_t TX_Mailboxe)
{
	Can_Status_t status;
	status=CAN_OK;
	//Check Message_Info pointer
	if(TX_Mailboxe > 2 || TX_Mailboxe < 0)
	{
		status=CAN_ERROR;
		return status;
	}
	switch (TX_Mailboxe)
	{
		case Transmi_mailbox_0:
			CAN_TSR |=(1<<7);
			//wait for request completed
			while(!(CAN_TSR &(1<<0)));
			CAN_TSR |=(1<<0);
			break;
		case Transmi_mailbox_1:
			CAN_TSR |=(1<<15);
			//wait for request completed
			while(!(CAN_TSR &(1<<8)));
			CAN_TSR |=(1<<8);
			break;
		case Transmi_mailbox_2:
			CAN_TSR |=(1<<23);
			//wait for request completed
			while(!(CAN_TSR &(1<<16)));
			CAN_TSR |=(1<<16);
			break;
		default:
			status=CAN_ERROR;
			break;
	}
	return status;
}
/**================================================================
* @Fn				-MCAL_CAN_TX_Message_Pending
* @brief		  	-Checks if a transmit message is pending in the specified transmit mailbox and retrieves its status.
* @param [in] 		-TX_Mailboxe: The number of the transmit mailbox to check for a pending message.
* @param [output] 	-pMailbox: Pointer to a variable that will store the status of the specified transmit mailbox.
* @retval 			-Can_Status_t	status of Can hardware (CAN_OK,CAN_ERROR,...)
* Note				-his function is used to check if a transmit message is pending in the specified transmit mailbox
* 					 Transmi_mailbox_Pending or Transmi_mailbox_Not_Pending
*/
Can_Status_t MCAL_CAN_TX_Message_Pending(uint32_t TX_Mailboxe , uint8_t* Mailboxe_Statuts)
{
	Can_Status_t status;
	status=CAN_OK;
	//Check Message_Info pointer
	if(TX_Mailboxe > 2 || TX_Mailboxe < 0)
	{
		status=CAN_ERROR;
		return status;
	}
	switch (TX_Mailboxe)
	{
		case Transmi_mailbox_0:
			if((CAN_TSR & (1<<26))==1)
			{
				*Mailboxe_Statuts=Transmi_mailbox_Not_Pending;
			}
			else if ((CAN_TSR & (1<<26))==0)
			{
				*Mailboxe_Statuts=Transmi_mailbox_Pending;
			}
			else
			{
				status=CAN_ERROR;
			}
			break;
		case Transmi_mailbox_1:
			if((CAN_TSR & (1<<27))==1)
			{
				*Mailboxe_Statuts=Transmi_mailbox_Not_Pending;
			}
			else if ((CAN_TSR & (1<<27))==0)
			{
				*Mailboxe_Statuts=Transmi_mailbox_Pending;
			}
			else
			{
				status=CAN_ERROR;
			}
			break;
		case Transmi_mailbox_2:
			if((CAN_TSR & (1<<28))==1)
			{
				*Mailboxe_Statuts=Transmi_mailbox_Not_Pending;
			}
			else if ((CAN_TSR & (1<<28))==0)
			{
				*Mailboxe_Statuts=Transmi_mailbox_Pending;
			}
			else
			{
				status=CAN_ERROR;
			}
			break;
		default:
			status=CAN_ERROR;
			break;
	}
	return status;
}
/**================================================================
* @Fn				-MCAL_CAN_Receive_Message
* @brief		  	-Receives a CAN message from any available receive FIFO and stores it in the provided buffer.
* @param [out]    	-Message_Info: Pointer to a structure where received CAN message information will be stored (ID, DLC, etc.).
* @param [out]    	-RX_Buffer: Pointer to an array where the received data will be stored.
* @retval         	-Can_Status_t: Status of the message reception (CAN_OK, CAN_ERROR, CAN_NOT_RX_MESSAGE, etc.).
* Note				-None
*/
Can_Status_t MCAL_CAN_Receive_Message(CAN_Message_Info_t* Message_Info, uint8_t* RX_Buffer)
{
	Can_Status_t status;
	status=CAN_OK;
	// Check fifo empty (fifo 0 and fifo 1)
	//fifo 0
	if((CAN_RF0R & (3<<0)) != 0)
	{
		//Identifier extension
		if((CAN_RX_FIFO_0->CAN_RIxR & (1<<2))==1)
		{
			//1: Extended identifier
			Message_Info->IDE=CAN_IDE_Extended;
			//get id
			Message_Info->Ext_ID=(CAN_RX_FIFO_0->CAN_RIxR>>3);
		}
		else
		{
			//0: Standard identifier
			Message_Info->IDE=CAN_IDE_Standard;
			//get id
			Message_Info->Std_ID=(CAN_RX_FIFO_0->CAN_RIxR>>21);
		}
		//Type of data frame
		if((CAN_RX_FIFO_0->CAN_RIxR & (1<<1))==1)
		{
			//1: Remote frame
			Message_Info->RTR=CAN_RTR_Remote_Frame;
		}
		else
		{
			//0: Data frame
			Message_Info->RTR=CAN_RTR_Data_Frame;
		}
		//This field defines the number of data bytes a data frame contains (0 to 8).
		Message_Info->DLC=(CAN_RX_FIFO_0->CAN_RDTxR & 0x0000000F);
		//CAN receive FIFO mailbox data
		*((volatile uint32_t*)RX_Buffer)=CAN_RX_FIFO_0->CAN_RDLxR;
		*(((volatile uint32_t*)RX_Buffer)+1)=CAN_RX_FIFO_0->CAN_RDHxR;
		/*
		for (int Len = 0; Len < Message_Info->DLC; ++Len)
		{
			if(Len < 3 )
			{
				*((volatile uint32_t*)RX_Buffer)=CAN_RX_FIFO_0->CAN_RDLxR;
				*(((volatile uint32_t*)RX_Buffer)+1)=CAN_RX_FIFO_0->CAN_RDHxR;
			}
			else
			{

			}
		}
		*/
		//Set by software to release the output mailbox of the FIFO
		CAN_RF0R |=(1<<5);
	}
	//fifo 1
	else if ((CAN_RF1R & (3<<0)) != 0)
	{
		//Identifier extension
		if((CAN_RX_FIFO_1->CAN_RIxR & (1<<2))==1)
		{
			//1: Extended identifier
			Message_Info->IDE=CAN_IDE_Extended;
			//get id
			Message_Info->Ext_ID=(CAN_RX_FIFO_1->CAN_RIxR>>3);
		}
		else
		{
			//0: Standard identifier
			Message_Info->IDE=CAN_IDE_Standard;
			//get id
			Message_Info->Std_ID=(CAN_RX_FIFO_1->CAN_RIxR>>21);
		}
		//Type of data frame
		if((CAN_RX_FIFO_1->CAN_RIxR & (1<<1))==1)
		{
			//1: Remote frame
			Message_Info->RTR=CAN_RTR_Remote_Frame;
		}
		else
		{
			//0: Data frame
			Message_Info->RTR=CAN_RTR_Data_Frame;
		}
		//This field defines the number of data bytes a data frame contains (0 to 8).
		Message_Info->DLC=(CAN_RX_FIFO_1->CAN_RDTxR & 0x0000000F);
		//CAN receive FIFO mailbox data
		*((volatile uint32_t*)RX_Buffer)=CAN_RX_FIFO_1->CAN_RDLxR;
		*(((volatile uint32_t*)RX_Buffer)+1)=CAN_RX_FIFO_1->CAN_RDHxR;
		//Set by software to release the output mailbox of the FIFO
		CAN_RF1R |=(1<<5);
	}
	else
	{
		// not received any data
		status=CAN_NOT_RX_MESSAGE;
	}
	return status;
}
/**================================================================
* @Fn				-MCAL_CAN_Get_Receive_Message
* @brief		  	-Receives a CAN message from the specified receive FIFO and stores it in the provided buffer.
* @param [in]     	-RX_FIFO: The receive FIFO from which to receive the CAN message.
* @param [out]    	-Message_Info: Pointer to a structure where received CAN message information will be stored (ID, DLC, etc.).
* @param [out]    	-RX_Buffer: Pointer to an array where the received data will be stored.
* @retval         	-Can_Status_t: Status of the message reception (CAN_OK, CAN_ERROR, CAN_NOT_RX_MESSAGE, etc.).
* Note				-None
*/
Can_Status_t MCAL_CAN_Get_Receive_Message(uint8_t RX_FIFO , CAN_Message_Info_t* Message_Info, uint8_t* RX_Buffer)
{
	Can_Status_t status;
	status=CAN_OK;
	CAN_RX_FIFO_TypeDef* Current_Fifo=NULL;
	if(RX_FIFO != Receive_Fifo_0 || RX_FIFO != Receive_Fifo_1)
	{
		status=CAN_ERROR;
		return status;
	}
	else
	{
		//no error
	}
	switch (RX_FIFO)
	{
		case Receive_Fifo_0:
			Current_Fifo=CAN_RX_FIFO_0;
			break;
		case Receive_Fifo_1:
			Current_Fifo=CAN_RX_FIFO_0;
			break;
		default:
			break;
	}
	//Identifier extension
	if((Current_Fifo->CAN_RIxR & (1<<2))==1)
	{
		//1: Extended identifier
		Message_Info->IDE=CAN_IDE_Extended;
		//get id
		Message_Info->Ext_ID=(Current_Fifo->CAN_RIxR>>3);
	}
	else
	{
		//0: Standard identifier
		Message_Info->IDE=CAN_IDE_Standard;
		//get id
		Message_Info->Std_ID=(Current_Fifo->CAN_RIxR>>21);
	}
	//Type of data frame
	if((Current_Fifo->CAN_RIxR & (1<<1))==1)
	{
		//1: Remote frame
		Message_Info->RTR=CAN_RTR_Remote_Frame;
	}
	else
	{
		//0: Data frame
		Message_Info->RTR=CAN_RTR_Data_Frame;
	}
	//This field defines the number of data bytes a data frame contains (0 to 8).
	Message_Info->DLC=(Current_Fifo->CAN_RDTxR & 0x0000000F);
	//CAN receive FIFO mailbox data
	*((volatile uint32_t*)RX_Buffer)=Current_Fifo->CAN_RDLxR;
	*(((volatile uint32_t*)RX_Buffer)+1)=Current_Fifo->CAN_RDHxR;
	//Set by software to release the output mailbox of the FIFO
	switch (RX_FIFO)
	{
		case Receive_Fifo_0:
			CAN_RF0R |=(1<<5);
			break;
		case Receive_Fifo_1:
			CAN_RF0R |=(1<<5);
			break;
		default:
			break;
	}
	return status;
}
/**================================================================
* @Fn				-MCAL_CAN_Request_Sleep
* @brief		  	-Requests the CAN controller to enter Sleep mode.
* @param [in] 		-None
* @retval 			-None
* Note				-None
*/
void MCAL_CAN_Request_Sleep(void)
{
	/*
	 This bit is set by software to request the CAN hardware to enter the Sleep mode. Sleep
	 mode will be entered as soon as the current CAN activity (transmission or reception of a
	 CAN frame) has been completed.
	 */
	CAN_MCR |=(1<<1);
	/*
	 This bit is cleared by software to exit Sleep mode.
	This bit is cleared by hardware when the AWUM bit is set and a SOF bit is detected on the
	CAN RX signal.
	This bit is set after reset - CAN starts in Sleep mode
	 */
}
/**================================================================
* @Fn				-MCAL_CAN_Get_Mode
* @brief		  	-Returns the current operating mode of the CAN controller.
* @param [in] 		-None
* @retval         	-Can_Mode_t: The current operating mode of the CAN controller (CAN_NORMAL_MODE, CAN_INITIALIZATION_MODE, CAN_SLEEP_MODE).
* Note				-None
*/
Can_Mode_t MCAL_CAN_Get_Mode(void)
{
	Can_Mode_t Mode;
	switch (CAN_MCR & 3)
	{
		case CAN_Normal_Mode:
			Mode=CAN_NORMAL_MODE;
			return Mode;
			break;
		case CAN_Initialization_Mode:
			Mode=CAN_INITIALIZATION_MODE;
			return Mode;
			break;
		case CAN_Sleep_Mode:
			Mode=CAN_SLEEP_MODE;
			return Mode;
			break;
		default:
			break;
	}
}
/*************************************************************************
 *************************************ISR*********************************
 ************************************************************************/
void USB_HP_CAN_TX_IRQHandler(void)
{
	//Check which mailbox transmit is complete
	// RQCPx: Request completed mailbox
	//Set by hardware when the last request (transmit or abort) has been performed.
	if((CAN_TSR & (1<<0))==1)
	{
		 //Request completed mailbox0
		CAN_TSR |=1<<0;
		if(g_Can_Config.P_TX_IRQ==NULL)
		{
			MCAL_CAN_Mailbox_0_Empty_Callback();
		}
		else
		{
			g_Can_Config.P_TX_IRQ();
		}
	}
	else if((CAN_TSR & (1<<8))==1)
	{
		 //Request completed mailbox1
		CAN_TSR |=1<<8;
		if(g_Can_Config.P_TX_IRQ==NULL)
		{
			MCAL_CAN_Mailbox_1_Empty_Callback();
		}
		else
		{
			g_Can_Config.P_TX_IRQ();
		}
	}
	else if((CAN_TSR & (1<<16))==1)
	{
		 //Request completed mailbox2
		CAN_TSR |=1<<16;
		if(g_Can_Config.P_TX_IRQ==NULL)
		{
			MCAL_CAN_Mailbox_1_Empty_Callback();
		}
		else
		{
			g_Can_Config.P_TX_IRQ();
		}
	}
	else
	{
		// no call back
	}
}
void USB_LP_CAN_RX0_IRQHandler(void)
{
	//These bits indicate how many messages are pending in the receive FIFO
	if ((CAN_RF0R & (3<<0))!=0)
	{
		//FIFO 0 message pending
		if(g_Can_Config.P_RX0_IRQ==NULL)
		{
			MCAL_CAN_FIFO_0_Receive_Callback();
		}
		else
		{
			g_Can_Config.P_RX0_IRQ();
		}

	}
	else if((CAN_RF0R & (1<<3))==1)
	{
		// FIFO 0 full
		if(g_Can_Config.P_RX0_IRQ==NULL)
		{
			MCAL_CAN_FIFO_0_Full_Callback();
		}
		else
		{
			g_Can_Config.P_RX0_IRQ();
		}
	}
	else if((CAN_RF0R & (1<<4))==1)
	{
		// FIFO 0 overrun
		if(g_Can_Config.P_RX0_IRQ==NULL)
		{
			MCAL_CAN_FIFO_0_Overrun_Callback();
		}
		else
		{
			g_Can_Config.P_RX0_IRQ();
		}
	}
	else
	{

	}
}
void CAN_RX1_IRQHandler(void)
{
	//These bits indicate how many messages are pending in the receive FIFO
	if ((CAN_RF1R & (3<<0))!=0)
	{
		//FIFO 1 message pending
		if(g_Can_Config.P_RX1_IRQ==NULL)
		{
			MCAL_CAN_FIFO_1_Receive_Callback();
		}
		else
		{
			g_Can_Config.P_RX1_IRQ();
		}

	}
	else if((CAN_RF1R & (1<<3))==1)
	{
		// FIFO 1 full
		if(g_Can_Config.P_RX1_IRQ==NULL)
		{
			MCAL_CAN_FIFO_1_Full_Callback();
		}
		else
		{
			g_Can_Config.P_RX1_IRQ();
		}
	}
	else if((CAN_RF1R & (1<<4))==1)
	{
		// FIFO 1 overrun
		if(g_Can_Config.P_RX1_IRQ==NULL)
		{
			MCAL_CAN_FIFO_1_Overrun_Callback();
		}
		else
		{
			g_Can_Config.P_RX1_IRQ();
		}
	}
	else
	{

	}
}
void CAN_SCE_IRQHandler(void)
{
	if((CAN_ESR & (1<<0))==1)
	{
		//Error warning flag
		if(g_Can_Config.P_SCE_IRQ==NULL)
		{
			MCAL_CAN_Error_Warning_Callback();
		}
		else
		{
			g_Can_Config.P_SCE_IRQ();
		}
	}
	else if((CAN_ESR & (1<<1))==1)
	{
		// Error passive flag
		if(g_Can_Config.P_SCE_IRQ==NULL)
		{
			MCAL_CAN_Error_Passive_Callback();
		}
		else
		{
			g_Can_Config.P_SCE_IRQ();
		}
	}
	else if((CAN_ESR & (1<<2))==1)
	{
		// Bus-off flag
		if(g_Can_Config.P_SCE_IRQ==NULL)
		{
			MCAL_CAN_Error_Bus_Off_Callback();
		}
		else
		{
			g_Can_Config.P_SCE_IRQ();
		}
	}
	else
	{
		/*
		 * Last error code
			000: No Error
			001: Stuff Error
			010: Form Error
			011: Acknowledgment Error
			100: Bit recessive Error
			101: Bit dominant Error
			110: CRC Error
			111: Set by software
		 */
		switch ((CAN_ESR>>4)&(7<<0))
		{
			case CAN_Stuff_Error:
				if(g_Can_Config.P_SCE_IRQ==NULL)
				{
					MCAL_CAN_Error_Stuff_Callback();
				}
				else
				{
					g_Can_Config.P_SCE_IRQ();
				}
				break;
			case CAN_Form_Error:
				if(g_Can_Config.P_SCE_IRQ==NULL)
				{
					MCAL_CAN_Error_Form_Callback();
				}
				else
				{
					g_Can_Config.P_SCE_IRQ();
				}
				break;
			case CAN_Acknowledgment_Error:
				if(g_Can_Config.P_SCE_IRQ==NULL)
				{
					MCAL_CAN_Error_Acknowledgment_Callback();
				}
				else
				{
					g_Can_Config.P_SCE_IRQ();
				}
				break;
			case CAN_Bit_Recessive_Error:
				if(g_Can_Config.P_SCE_IRQ==NULL)
				{
					MCAL_CAN_Error_Bit_Recessive_Callback();
				}
				else
				{
					g_Can_Config.P_SCE_IRQ();
				}
				break;
			case CAN_Bit_Dominant_Error:
				if(g_Can_Config.P_SCE_IRQ==NULL)
				{
					MCAL_CAN_Error_Bit_Dominant_Callback();
				}
				else
				{
					g_Can_Config.P_SCE_IRQ();
				}
				break;
			case CAN_CRC_Error:
				if(g_Can_Config.P_SCE_IRQ==NULL)
				{
					MCAL_CAN_Error_CRC__Callback();
				}
				else
				{
					g_Can_Config.P_SCE_IRQ();
				}
				break;
			default:
				break;
		}
	}
}
/*************************************************************************
 *************************************CallBack****************************
 ************************************************************************/
__attribute__((weak)) void MCAL_CAN_Error_Bus_Off_Callback(void)
{

}

__attribute__((weak)) void MCAL_CAN_Error_Passive_Callback(void)
{

}

__attribute__((weak)) void MCAL_CAN_Error_Warning_Callback(void)
{

}
__attribute__((weak)) void MCAL_CAN_Error_Stuff_Callback(void)
{

}
__attribute__((weak)) void MCAL_CAN_Error_Form_Callback(void)
{

}
__attribute__((weak)) void MCAL_CAN_Error_Bit_Recessive_Callback(void)
{

}
__attribute__((weak)) void MCAL_CAN_Error_Bit_Dominant_Callback(void)
{

}
__attribute__((weak)) void MCAL_CAN_Error_Acknowledgment_Callback(void)
{

}
__attribute__((weak)) void MCAL_CAN_Error_CRC__Callback(void)
{

}
__attribute__((weak)) void MCAL_CAN_Mailbox_0_Empty_Callback(void)
{

}
__attribute__((weak)) void MCAL_CAN_Mailbox_1_Empty_Callback(void)
{

}
__attribute__((weak)) void MCAL_CAN_Mailbox_2_Empty_Callback(void)
{

}
__attribute__((weak)) void MCAL_CAN_FIFO_0_Receive_Callback(void)
{

}
__attribute__((weak)) void MCAL_CAN_FIFO_0_Full_Callback(void)
{

}
__attribute__((weak)) void MCAL_CAN_FIFO_0_Overrun_Callback(void)
{

}
__attribute__((weak)) void MCAL_CAN_FIFO_1_Receive_Callback(void)
{

}
__attribute__((weak)) void MCAL_CAN_FIFO_1_Full_Callback(void)
{

}
__attribute__((weak)) void MCAL_CAN_FIFO_1_Overrun_Callback(void)
{

}
