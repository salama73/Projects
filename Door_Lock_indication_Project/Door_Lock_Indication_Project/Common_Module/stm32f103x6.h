/******************************************************************************
* @Module      :	 Can_Module
* @File Name   :	 stm32f103x6.h
* @Description :	Addresses of the can controller
* Author       :	Salama Mohamed
*******************************************************************************/
/******************************************************************************
* Project				: CAN Module
* Platform				: stm32f103c8
* Autosar Version		: 4.8.0
* SW Version		    : 1.0.0
******************************************************************************/
#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_
#include "../Common_Module/Std_Types.h"
//-----------------------------
//Base addresses for Memories
//-----------------------------
#define PERIPHERALS_BAES	  						0X40000000UL
#define NVIC_BASE									0xE000E100UL
#define NVIC_ISER0                                  *(volatile uint32*)(NVIC_BASE+0X00)
#define NVIC_ISER1                                  *(volatile uint32*)(NVIC_BASE+0X04)
#define NVIC_ICER0                                  *(volatile uint32*)(NVIC_BASE+0X80)
#define NVIC_ICER1                                  *(volatile uint32*)(NVIC_BASE+0X84)
//================================================================================
//-----------------------------
//Base addresses for BUS AHB Peripherals
//-----------------------------
//RCC
#define RCC_BASE							0X40021000UL
//-----------------------------
//Base addresses for BUS APB1 Peripherals
//-----------------------------
//CAN
#define CAN_BASE							0X40006400UL
#define CAN_MCR                          *(volatile uint32*)(CAN_BASE+0X00)
#define CAN_MSR                          *(volatile uint32*)(CAN_BASE+0X04)
#define CAN_TSR                          *(volatile uint32*)(CAN_BASE+0X08)
#define CAN_RF0R                          *(volatile uint32*)(CAN_BASE+0X0C)
#define CAN_RF1R                          *(volatile uint32*)(CAN_BASE+0X10)
#define CAN_IER                          *(volatile uint32*)(CAN_BASE+0X14)
#define CAN_ESR                          *(volatile uint32*)(CAN_BASE+0X18)
#define CAN_BTR                          *(volatile uint32*)(CAN_BASE+0X1C)
#define CAN_TX_mailbox0_Base              (CAN_BASE+0X180)
#define CAN_TX_mailbox1_Base              (CAN_BASE+0X190)
#define CAN_TX_mailbox2_Base              (CAN_BASE+0X1A0)
#define CAN_TX_mailbox0_Base              (CAN_BASE+0X180)
#define CAN_TX_mailbox1_Base              (CAN_BASE+0X190)
#define CAN_RX_FIFO0_Base              	  (CAN_BASE+0X1B0)
#define CAN_RX_FIFO1_Base              	  (CAN_BASE+0X1C0)
#define CAN_FMR                          *(volatile uint32*)(CAN_BASE+0X200)
#define CAN_FM1R                          *(volatile uint32*)(CAN_BASE+0X204)
#define CAN_FS1R                          *(volatile uint32*)(CAN_BASE+0X20C)
#define CAN_FFA1R                          *(volatile uint32*)(CAN_BASE+0X214)
#define CAN_FA1R                          *(volatile uint32*)(CAN_BASE+0X21C)
#define CAN_Filter_Bank_0_Base               (CAN_BASE+0X240)
#define CAN_Filter_Bank_1_Base               (CAN_BASE+0X248)
#define CAN_Filter_Bank_2_Base               (CAN_BASE+0X250)
#define CAN_Filter_Bank_3_Base               (CAN_BASE+0X258)
#define CAN_Filter_Bank_4_Base               (CAN_BASE+0X260)
#define CAN_Filter_Bank_5_Base               (CAN_BASE+0X268)
#define CAN_Filter_Bank_6_Base               (CAN_BASE+0X270)
#define CAN_Filter_Bank_7_Base               (CAN_BASE+0X278)
#define CAN_Filter_Bank_8_Base               (CAN_BASE+0X280)
#define CAN_Filter_Bank_9_Base               (CAN_BASE+0X288)
#define CAN_Filter_Bank_10_Base               (CAN_BASE+0X290)
#define CAN_Filter_Bank_11_Base               (CAN_BASE+0X298)
#define CAN_Filter_Bank_12_Base               (CAN_BASE+0X2A0)
#define CAN_Filter_Bank_13_Base               (CAN_BASE+0X2A8)
//-----------------------------
//Base addresses for BUS APB2 Peripherals
//-----------------------------
//GPIO
//A,B Fully included in LQFP48 package
#define GPIOA_BASE							0X40010800UL
#define GPIOB_BASE							0X40010C00UL
//C,D Partial included in LQFP48 package
#define GPIOC_BASE							0X40011000UL
#define GPIOD_BASE							0X40011400UL
// E Not included in LQFP48 package
#define GPIOE_BASE							0X40011800UL
//TIMER2
#define TIM2_BASE							0x40000000UL
//=========================================================================================

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:
//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register:GPIO
typedef struct
{
	volatile uint32 CRL		;
	volatile uint32 CRH		;
	volatile uint32 IDR		;
	volatile uint32 ODR		;
	volatile uint32 BSRR		;
	volatile uint32 BRR		;
	volatile uint32 LCKR		;
}GPIO_TypeDef;
//Peripheral register:RCC
typedef struct
{
	volatile uint32 CR		;
	volatile uint32 CFGR		;
	volatile uint32 CIR		;
	volatile uint32 APB2RSTR	;
	volatile uint32 APB1RSTR	;
	volatile uint32 AHBENR	;
	volatile uint32 APB2ENR	;
	volatile uint32 APB1ENR	;
	volatile uint32 BDCR		;
	volatile uint32 CSR		;
}RCC_TypeDef;
//Peripheral register:TIMER
typedef struct
{
	volatile uint32 CR1		;
	volatile uint32 CR2		;
	volatile uint32 SMCR		;
	volatile uint32 DIER		;
	volatile uint32 SR		;
	volatile uint32 EGR		;
	volatile uint32 CCMR1		;//Output Compare mode and input Compare mode
	volatile uint32 CCMR2		;//input Compare mode and Output Compare mode
	volatile uint32 CCER		;
	volatile uint32 CNT		;
	volatile uint32 PSC		;
	volatile uint32 ARR		;
	uint32 RESERVED0          ;
	volatile uint32 CCR1		;
	volatile uint32 CCR2		;
	volatile uint32 CCR3		;
	volatile uint32 CCR4		;
	uint32 RESERVED1         	;
	volatile uint32 DCR		;
	volatile uint32 DMAR		;
}TIMx_TypeDef;
typedef struct
{
	volatile uint32 CAN_TIxR		;
	volatile uint32 CAN_TDTxR		;
	volatile uint32 CAN_TDLxR		;
	volatile uint32 CAN_TDHxR		;
}CAN_TX_mailbox_TypeDef;

typedef struct
{
	volatile uint32 CAN_RIxR		;
	volatile uint32 CAN_RDTxR		;
	volatile uint32 CAN_RDLxR		;
	volatile uint32 CAN_RDHxR		;
}CAN_RX_FIFO_TypeDef;

typedef struct
{
	volatile uint32 CAN_FiR1		;
	volatile uint32 CAN_FiR2		;
}CAN_Filter_Bank_TypeDef;
//=========================================================================================
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*
#define GPIOA		((GPIO_TypeDef*)GPIOA_BASE)
#define GPIOB		((GPIO_TypeDef*)GPIOB_BASE)
#define GPIOC		((GPIO_TypeDef*)GPIOC_BASE)
#define GPIOD		((GPIO_TypeDef*)GPIOD_BASE)
#define GPIOE		((GPIO_TypeDef*)GPIOE_BASE)
#define RCC			((RCC_TypeDef*)RCC_BASE)
#define TIM2		((TIMx_TypeDef*)TIM2_BASE)
//CAN_TX_mailbox
#define CAN_TX_mailbox_0		((CAN_TX_mailbox_TypeDef*)CAN_TX_mailbox0_Base)
#define CAN_TX_mailbox_1		((CAN_TX_mailbox_TypeDef*)CAN_TX_mailbox1_Base)
#define CAN_TX_mailbox_2		((CAN_TX_mailbox_TypeDef*)CAN_TX_mailbox2_Base)
//CAN_RX_FIFO
#define CAN_RX_FIFO_0			((CAN_RX_FIFO_TypeDef*)CAN_RX_FIFO0_Base)
#define CAN_RX_FIFO_1			((CAN_RX_FIFO_TypeDef*)CAN_RX_FIFO1_Base)
//Filter bank
#define CAN_FBank_0				((CAN_Filter_Bank_TypeDef*)CAN_Filter_Bank_0_Base)
#define CAN_FBank_1				((CAN_Filter_Bank_TypeDef*)CAN_Filter_Bank_1_Base)
#define CAN_FBank_2				((CAN_Filter_Bank_TypeDef*)CAN_Filter_Bank_2_Base)
#define CAN_FBank_3				((CAN_Filter_Bank_TypeDef*)CAN_Filter_Bank_3_Base)
#define CAN_FBank_4				((CAN_Filter_Bank_TypeDef*)CAN_Filter_Bank_4_Base)
#define CAN_FBank_5				((CAN_Filter_Bank_TypeDef*)CAN_Filter_Bank_5_Base)
#define CAN_FBank_6				((CAN_Filter_Bank_TypeDef*)CAN_Filter_Bank_6_Base)
#define CAN_FBank_7				((CAN_Filter_Bank_TypeDef*)CAN_Filter_Bank_7_Base)
#define CAN_FBank_8				((CAN_Filter_Bank_TypeDef*)CAN_Filter_Bank_8_Base)
#define CAN_FBank_9				((CAN_Filter_Bank_TypeDef*)CAN_Filter_Bank_9_Base)
#define CAN_FBank_10			((CAN_Filter_Bank_TypeDef*)CAN_Filter_Bank_10_Base)
#define CAN_FBank_11			((CAN_Filter_Bank_TypeDef*)CAN_Filter_Bank_11_Base)
#define CAN_FBank_12			((CAN_Filter_Bank_TypeDef*)CAN_Filter_Bank_12_Base)
#define CAN_FBank_13			((CAN_Filter_Bank_TypeDef*)CAN_Filter_Bank_13_Base)
//==========================================================================================
//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define RCC_GPIOA_CLK_Enable()	(RCC->APB2ENR |=1<<2)
#define RCC_GPIOB_CLK_Enable()	(RCC->APB2ENR |=1<<3)
#define RCC_GPIOC_CLK_Enable()	(RCC->APB2ENR |=1<<4)
#define RCC_GPIOD_CLK_Enable()	(RCC->APB2ENR |=1<<5)
#define RCC_GPIOE_CLK_Enable()	(RCC->APB2ENR |=1<<6)

#define RCC_GPIOA_CLK_Disable()	(RCC->APB2RSTR |=1<<2)
#define RCC_GPIOB_CLK_Disable()	(RCC->APB2RSTR |=1<<3)
#define RCC_GPIOC_CLK_Disable()	(RCC->APB2RSTR |=1<<4)
#define RCC_GPIOD_CLK_Disable()	(RCC->APB2RSTR |=1<<5)
#define RCC_GPIOE_CLK_Disable()	(RCC->APB2RSTR |=1<<6)
//TIMER2
#define RCC_TIM2_CLK_Enable()	(RCC->APB1ENR |=1<<0)
#define RCC_TIM2_CLK_Disable()	(RCC->APB1RSTR |=1<<0)
//CAN
#define RCC_CAN_CLK_Enable()	(RCC->APB1ENR |=1<<25)
#define RCC_CAN_CLK_Disable()	(RCC->APB1RSTR |=1<<25)
//=============================================================================================
 /**************************************************************
 *         					IVT
 **************************************************************/
#define CAN_TX_IRQ				(uint32)19
#define CAN_RX0_IRQ				(uint32)20
#define CAN_RX1_IRQ				(uint32)21
#define CAN_SCE_IRQ				(uint32)22
#define TIM2_ER_IRQ				(uint32)28//TIM2 global interrupt
//-*-*-*-*-*-*-*-*-*-*-*-
//NVIC Enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define NVIC_IRQ19_CAN_TX_Enable()							(NVIC_ISER0 |=1<<CAN_TX_IRQ)
#define NVIC_IRQ20_CAN_RX0_Enable()							(NVIC_ISER0 |=1<<CAN_RX0_IRQ)
#define NVIC_IRQ21_CAN_RX1_Enable()							(NVIC_ISER0 |=1<<CAN_RX1_IRQ)
#define NVIC_IRQ22_CAN_SCE_Enable()							(NVIC_ISER0 |=1<<CAN_SCE_IRQ)
#define NVIC_IRQ28_TIM2_Enable()							(NVIC_ISER0 |=1<<TIM2_ER_IRQ)
//-*-*-*-*-*-*-*-*-*-*-*-
//NVIC Disable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define NVIC_IRQ19_CAN_TX_Disable()							(NVIC_ICER0 |=1<<CAN_TX_IRQ)
#define NVIC_IRQ20_CAN_RX0_Disable()						(NVIC_ICER0 |=1<<CAN_RX0_IRQ)
#define NVIC_IRQ21_CAN_RX1_Disable()						(NVIC_ICER0 |=1<<CAN_RX1_IRQ)
#define NVIC_IRQ22_CAN_SCE_Disable()						(NVIC_ICER0 |=1<<CAN_SCE_IRQ)
#define NVIC_IRQ28_TIM2_Disable()							(NVIC_ICER0 |=1<<TIM2_ER_IRQ)
#endif /* INC_STM32F103X6_H_ */
