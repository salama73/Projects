/*
 * stm32_f103c6_CAN.h
 *  Created on: 6/9/2023
 *  Author: Salama mohamed
 */

#ifndef INC_STM32_F103C6_CAN_H_
#define INC_STM32_F103C6_CAN_H_
/*
 **************************************************************
 *************************Include File ************************
 **************************************************************
 */
#include "stm32f103x6.h"
#include"stm32_f103c6_GPIO.h"
#include "stm32_f103c6_RCC.h"
#include "delay.h"
/**************************************************************/

typedef enum
{
	CAN_OK,
	CAN_ERROR,
	CAN_NOT_RX_MESSAGE
}Can_Status_t;

typedef enum
{
	CAN_NORMAL_MODE,
	CAN_INITIALIZATION_MODE,
	CAN_SLEEP_MODE
}Can_Mode_t;

typedef struct
{

	uint32_t Mode;                        // specified the CAN operating mode
	 	 	 	 	 	 	 	 	      // this parameter must be set based on  @ ref CAN_MODE_Define

	uint16_t BaudRate ;					  // specified the CAN BaudRate 1000...
										  // this parameter must be set based on  @ ref CAN_BaudRate_Define

	uint8_t AutoBusOff;           		  // recover from Bus-Off  either automatically or on software request
										  // this parameter must be set based on  @ ref CAN_AutoBusOff_Define

	uint8_t AutoRetransmission;   		  // Enable or disable the non automatic retransmission mode.
	 	 	 	 	 	 	 	 	 	  // this parameter must be set based on  @ ref CAN_AutoRetransmission_Define

	uint8_t Fifo_Locked;    	  		  // If the FIFO lock function is disabled the last message stored in the FIFO will be overwritten by the new incoming message
                                          // this parameter must be set based on  @ ref CAN_Fifo_Locked_Define

	uint8_t Transmit_Priority;    		  // FIFO priority By identifier (Enable) or By transmit request order (disable) .
                                          // this parameter must be set based on  @ ref CAN_Transmit_Priority_Define

	uint8_t TX_IRQ_EN	;           	  // specified the Transmit interrupt (disable or enable )  .
										  // this parameter must be set based on  @ ref  CAN_TX_IRQ_EN_Define

	uint8_t RX0_IRQ_EN	;            	  // specified the Receive FIFO 0 interrupt (disable or enable ) .
										  // this parameter must be set based on  @ ref  CAN_RX0_IRQ_EN_Define

	uint8_t RX1_IRQ_EN	;                 // specified the Receive FIFO 1 interrupt (disable or enable ) .
										  // this parameter must be set based on  @ ref  CAN_RX1_IRQ_EN_Define

	uint8_t SCE_IRQ_EN	;            	  // specified the STATUS CHANGE interrupt (disable or enable ) .
										  // this parameter must be set based on  @ ref  CAN_SCE_IRQ_EN_Define

	void (*P_TX_IRQ)(void);               // set the function which will be call at IRQ happen
	void (*P_RX0_IRQ)(void);              // set the function which will be call at IRQ happen
	void (*P_RX1_IRQ)(void);              // set the function which will be call at IRQ happen
	void (*P_SCE_IRQ)(void);              // set the function which will be call at IRQ happen
} CAN_Config_t;

typedef struct
{
	uint32_t Prescaler;                	  //specified the can prescalers .
										  //this parameter must be set from range 1 to 1024


	uint32_t TimeSeg1;                    // Specifies the number of time quanta in Bit Segment 1.
                                          // this parameter must be set from range 1 to 16

	uint32_t TimeSeg2;                    // Specifies the number of time quanta in Bit Segment 2.
    									  // this parameter must be set from range 1 to 8

}CAN_BaudRate_Config_t;

typedef struct
{
	uint32_t Filter_ID;                   // Specifies the filter identification number
                                          // this parameter must be set from range 0X00000000 to 0XFFFFFFFF in 32 bit scale
										  // in 16 bit scale must contain 2 id from range 0X0000 to 0XFFFF (0X073F085F) ID1=0X073F ID2=0X085F

	uint32_t Filter_Mask_ID;              // Specifies the filter mask number or identification number,
                                          // this parameter must be set from range 0X00000000 to 0XFFFFFFFF in 32 bit scale
										  // in 16 bit scale must contain 2 Mask from range 0X0000 to 0XFFFF (0X073F085F) mask1=0X073F mask2=0X085F

	uint32_t Filter_FIFO_Assignment;      // Specifies the FIFO which will be assigned to the filter.
                                          // this parameter must be set based on  @ ref CAN_Filter_FIFO_Assignment_Define

	uint32_t Filter_Bank;                 // Specifies the filter bank which will be initialized from 0 to 13
										  // this parameter must be set based on  @ ref CAN_Filter_Bank_Define

	uint32_t Filter_Mode;                 // Specifies the filter mode to be initialized.
                                          // this parameter must be set based on  @ ref CAN_Filter_Mode_Define

	uint32_t Filter_Scale;                // Specifies the filter scale.
                                          // this parameter must be set based on  @ ref CAN_Filter_Scale_Define
} CAN_Filter_Config_t;

typedef struct
{
	uint32_t Ext_ID;    				  // Specifies the extended identifier.
										  // this parameter must be set from range 0X00000000 to 0x1FFFFFFF

	uint32_t Std_ID;    				  // Specifies the standard identifier.
										  // this parameter must be set from range 0X000 to 0X7FF

	uint8_t IDE;      					  // Specifies the type of identifier .
										  // this parameter cab be a value based on  @ ref CAN_IDE_Define

	uint8_t RTR;      					  // Specifies the type of frame .
										  // this parameter cab be a value based on  @ ref CAN_RTR_Define

	uint32_t DLC;      					  // Specifies the length of the frame that will be transmitted.
										  // this parameter cab be a value based on  @ ref CAN_DLC_Define
} CAN_Message_Info_t;


//-----------------------------
//Macros Configuration References
//-----------------------------
//TX Mailbox and Status Definition
#define Transmi_mailbox_0							((uint8_t)0)
#define Transmi_mailbox_1							((uint8_t)1)
#define Transmi_mailbox_2							((uint8_t)2)
#define Transmi_mailbox_Full						((uint8_t)3)
#define Transmi_mailbox_Not_Pending					((uint8_t)0)
#define Transmi_mailbox_Pending						((uint8_t)1)
//RX FIFO Definition
#define Receive_Fifo_0								((uint8_t)0)
#define Receive_Fifo_1								((uint8_t)1)
//CAN Mode
#define CAN_Normal_Mode			       				((uint32_t)0)
#define CAN_Initialization_Mode						((uint32_t)1)
#define CAN_Sleep_Mode			      	  			((uint32_t)2)
//CAN Error Definition
#define CAN_No_Error								((uint32_t)0)
#define CAN_Stuff_Error								((uint32_t)1)
#define CAN_Form_Error								((uint32_t)2)
#define CAN_Acknowledgment_Error					((uint32_t)3)
#define CAN_Bit_Recessive_Error						((uint32_t)4)
#define CAN_Bit_Dominant_Error						((uint32_t)5)
#define CAN_CRC_Error								((uint32_t)6)
//@ ref CAN_MODE_Define
#define CAN_MODE_Silent								((uint32_t)0) //In Silent mode, the bxCAN is able to receive valid data frames and valid remote frames
#define CAN_MODE_Loop_back							((uint32_t)1) // In Loop Back Mode, the bxCAN treats its own transmitted messages as received messages
#define CAN_MODE_Loop_back_Silent					((uint32_t)2) //bxCAN can be tested like in Loop Back mode but without affecting a running CAN system connected to the CANTX and CANRX pins.
#define CAN_MODE_Normal		((uint32_t)3)
//@ ref CAN_AutoBusOff_Define
#define CAN_AutoBusOff_Disable						((uint32_t)0)
#define CAN_AutoBusOff_Enable						((uint32_t)1)
// @ ref CAN_AutoRetransmission_Define
#define CAN_AutoRetransmission_Disable				((uint32_t)0)
#define CAN_AutoRetransmission_Enable				((uint32_t)1)
//@ ref CAN_Fifo_Locked_Define
#define CAN_Fifo_Locked_Disable						((uint32_t)0)
#define CAN_Fifo_Locked_Enable						((uint32_t)1)
//@ ref CAN_Transmit_Priority_Define
#define CAN_Fifo_Transmit_Priority_Disable			((uint32_t)0)
#define CAN_Fifo_Transmit_Priority_Enable			((uint32_t)1)
//@ ref CAN_BaudRate_Define
#define CAN_BaudRate_1000							((uint8_t)0)
#define CAN_BaudRate_800							((uint8_t)1)
#define CAN_BaudRate_500							((uint8_t)2)
#define CAN_BaudRate_250							((uint8_t)3)
#define CAN_BaudRate_125							((uint8_t)4)
#define CAN_BaudRate_100							((uint8_t)5)
#define CAN_BaudRate_50				    			((uint8_t)6)
//@ ref CAN_Filter_FIFO_Assignment_Define
#define CAN_Filter_FIFO_Assignment_FIFO0			((uint8_t)0)
#define CAN_Filter_FIFO_Assignment_FIFO1			((uint8_t)1)
//@ ref CAN_Filter_Bank_Define
#define CAN_Filter_Bank_0							((uint8_t)0)
#define CAN_Filter_Bank_1							((uint8_t)1)
#define CAN_Filter_Bank_2							((uint8_t)2)
#define CAN_Filter_Bank_3							((uint8_t)3)
#define CAN_Filter_Bank_4							((uint8_t)4)
#define CAN_Filter_Bank_5							((uint8_t)5)
#define CAN_Filter_Bank_6							((uint8_t)6)
#define CAN_Filter_Bank_7							((uint8_t)7)
#define CAN_Filter_Bank_8							((uint8_t)8)
#define CAN_Filter_Bank_9							((uint8_t)9)
#define CAN_Filter_Bank_10							((uint8_t)10)
#define CAN_Filter_Bank_11							((uint8_t)11)
#define CAN_Filter_Bank_12							((uint8_t)12)
#define CAN_Filter_Bank_13							((uint8_t)13)
//@ ref CAN_Filter_Mode_Define
#define CAN_Filter_Mode_Mask						((uint8_t)0)
#define CAN_Filter_Mode_List						((uint8_t)1)
//@ ref CAN_Filter_Scale_Define
#define CAN_Filter_Scale_16							((uint8_t)0)
#define CAN_Filter_Scale_32							((uint8_t)1)
// @ ref  CAN_TX_IRQ_EN_Define
#define CAN_TX_IRQ_EN_Disable						((uint8_t)0)
#define CAN_TX_IRQ_EN_Enable						((uint8_t)1)
// @ ref  CAN_RX0_IRQ_EN_Define
#define CAN_RX0_IRQ_EN_Disable						((uint8_t)0)
#define CAN_RX0_IRQ_EN_Enable						((uint8_t)1)
// @ ref  CAN_RX1_IRQ_EN_Define
#define CAN_RX1_IRQ_EN_Disable						((uint8_t)0)
#define CAN_RX1_IRQ_EN_Enable						((uint8_t)1)
// @ ref  CAN_SCE_IRQ_EN_Define
#define CAN_SCE_IRQ_EN_Disable						((uint8_t)0)
#define CAN_SCE_IRQ_EN_Enable						((uint8_t)1)
//@ ref CAN_IDE_Define
#define CAN_IDE_Standard							((uint8_t)0)
#define CAN_IDE_Extended							((uint8_t)1)
//@ ref CAN_RTR_Define
#define CAN_RTR_Data_Frame							((uint8_t)0)
#define CAN_RTR_Remote_Frame						((uint8_t)1)
// @ ref CAN_DLC_Define
#define CAN_DLC_0									((uint32_t)0)
#define CAN_DLC_1									((uint32_t)1)
#define CAN_DLC_2									((uint32_t)2)
#define CAN_DLC_3									((uint32_t)3)
#define CAN_DLC_4									((uint32_t)4)
#define CAN_DLC_5									((uint32_t)5)
#define CAN_DLC_6									((uint32_t)7)
#define CAN_DLC_7									((uint32_t)7)
#define CAN_DLC_8									((uint32_t)8)
/***********************************************************************
* *******************************APIS***********************************
* *********************************************************************/
Can_Status_t MCAL_CAN_Init(CAN_Config_t* Can_Config);
void MCAL_CAN_DeInit(void);
Can_Status_t MCAL_CAN_Config_Filter(CAN_Filter_Config_t* Filter_Config);
Can_Status_t MCAL_CAN_Set_BaudRate(CAN_BaudRate_Config_t* BaudRate_Config);
Can_Status_t MCAL_CAN_Start(void);
uint8_t MCAL_CAN_Get_TX_Mailboxes_Empty(void);
Can_Status_t MCAL_CAN_Add_TX_Message(CAN_Message_Info_t* Message_Info, uint8_t Data[], uint8_t *Mailbox);
Can_Status_t MCAL_CAN_Abort_TX_Message(uint32_t TX_Mailboxe);
Can_Status_t MCAL_CAN_TX_Message_Pending(uint32_t TX_Mailboxe , uint8_t* Mailboxe_Statuts);
Can_Status_t MCAL_CAN_Receive_Message(CAN_Message_Info_t* Message_Info, uint8_t* RX_Buffer);
Can_Status_t MCAL_CAN_Get_Receive_Message(uint8_t RX_FIFO , CAN_Message_Info_t* Message_Info, uint8_t* RX_Buffer);
void MCAL_CAN_Request_Sleep(void);
Can_Mode_t MCAL_CAN_Get_Mode(void);
/*************************************************************************
 *************************************CallBack****************************
 ************************************************************************/
void MCAL_CAN_Error_Bus_Off_Callback(void);
void MCAL_CAN_Error_Passive_Callback(void);
void MCAL_CAN_Error_Warning_Callback(void);
void MCAL_CAN_Error_Stuff_Callback(void);
void MCAL_CAN_Error_Form_Callback(void);
void MCAL_CAN_Error_Bit_Recessive_Callback(void);
void MCAL_CAN_Error_Bit_Dominant_Callback(void);
void MCAL_CAN_Error_Acknowledgment_Callback(void);
void MCAL_CAN_Error_CRC__Callback(void);
void MCAL_CAN_Mailbox_0_Empty_Callback(void);
void MCAL_CAN_Mailbox_1_Empty_Callback(void);
void MCAL_CAN_Mailbox_2_Empty_Callback(void);
void MCAL_CAN_FIFO_0_Receive_Callback(void);
void MCAL_CAN_FIFO_1_Receive_Callback(void);
void MCAL_CAN_FIFO_0_Full_Callback(void);
void MCAL_CAN_FIFO_0_Overrun_Callback(void);
void MCAL_CAN_FIFO_1_Receive_Callback(void);
void MCAL_CAN_FIFO_1_Full_Callback(void);
void MCAL_CAN_FIFO_1_Overrun_Callback(void);
#endif /* INC_STM32_F103C6_CAN_H_ */
