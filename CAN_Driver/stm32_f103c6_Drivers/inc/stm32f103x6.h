/*
 * stm32f103x6.h
 *
 *  Created on: Aug 26, 2022
 *      Author: Salama Mohamed
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_

//-----------------------------
//Includes
//-----------------------------
#include <stdint.h>
#include <stdlib.h>

//-----------------------------
//Base addresses for Memories
//-----------------------------
#define FLASH_MEMORY_BAES							0X08000000UL
#define SYSTEM_MEMORY_BAES							0X1FFFF000UL
#define SRAM_MEMORY_BAES							0X20000000UL
#define PERIPHERALS_BAES	  						0X40000000UL

#define CORTEX_M3_INTERNAL_PERIPHERALS_BAES			0XE0000000UL
#define NVIC_BASE									0xE000E100UL
#define NVIC_ISER0                                  *(volatile uint32_t*)(NVIC_BASE+0X00)
#define NVIC_ISER1                                  *(volatile uint32_t*)(NVIC_BASE+0X04)
#define NVIC_ICER0                                  *(volatile uint32_t*)(NVIC_BASE+0X80)
#define NVIC_ICER1                                  *(volatile uint32_t*)(NVIC_BASE+0X84)

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
#define CAN_MCR                          *(volatile uint32_t*)(CAN_BASE+0X00)
#define CAN_MSR                          *(volatile uint32_t*)(CAN_BASE+0X04)
#define CAN_TSR                          *(volatile uint32_t*)(CAN_BASE+0X08)
#define CAN_RF0R                          *(volatile uint32_t*)(CAN_BASE+0X0C)
#define CAN_RF1R                          *(volatile uint32_t*)(CAN_BASE+0X10)
#define CAN_IER                          *(volatile uint32_t*)(CAN_BASE+0X14)
#define CAN_ESR                          *(volatile uint32_t*)(CAN_BASE+0X18)
#define CAN_BTR                          *(volatile uint32_t*)(CAN_BASE+0X1C)
#define CAN_TX_mailbox0_Base              (CAN_BASE+0X180)
#define CAN_TX_mailbox1_Base              (CAN_BASE+0X190)
#define CAN_TX_mailbox2_Base              (CAN_BASE+0X1A0)
#define CAN_TX_mailbox0_Base              (CAN_BASE+0X180)
#define CAN_TX_mailbox1_Base              (CAN_BASE+0X190)
#define CAN_RX_FIFO0_Base              	  (CAN_BASE+0X1B0)
#define CAN_RX_FIFO1_Base              	  (CAN_BASE+0X1C0)
/*
#define CAN_TI0R                          *(volatile uint32_t*)(CAN_BASE+0X180)
#define CAN_TDT0R                          *(volatile uint32_t*)(CAN_BASE+0X184)
#define CAN_TDL0R                          *(volatile uint32_t*)(CAN_BASE+0X188)
#define CAN_TDH0R                          *(volatile uint32_t*)(CAN_BASE+0X18C)
#define CAN_TI1R                          *(volatile uint32_t*)(CAN_BASE+0X190)
#define CAN_TDT1R                          *(volatile uint32_t*)(CAN_BASE+0X194)
#define CAN_TDL1R                          *(volatile uint32_t*)(CAN_BASE+0X198)
#define CAN_TDH1R                          *(volatile uint32_t*)(CAN_BASE+0X19C)
#define CAN_TI2R                          *(volatile uint32_t*)(CAN_BASE+0X1A0)
#define CAN_TDT2R                          *(volatile uint32_t*)(CAN_BASE+0X1A4)
#define CAN_TDL2R                          *(volatile uint32_t*)(CAN_BASE+0X1A8)
#define CAN_TDH2R                          *(volatile uint32_t*)(CAN_BASE+0X1AC)

#define CAN_RI0R                          *(volatile uint32_t*)(CAN_BASE+0X1B0)
#define CAN_RDT0R                          *(volatile uint32_t*)(CAN_BASE+0X1B4)
#define CAN_RDL0R                          *(volatile uint32_t*)(CAN_BASE+0X1B8)
#define CAN_RDH0R                          *(volatile uint32_t*)(CAN_BASE+0X1BC)
#define CAN_RI1R                          *(volatile uint32_t*)(CAN_BASE+0X1C0)
#define CAN_RDT1R                          *(volatile uint32_t*)(CAN_BASE+0X1C4)
#define CAN_RDL1R                          *(volatile uint32_t*)(CAN_BASE+0X1C8)
#define CAN_RDH1R                          *(volatile uint32_t*)(CAN_BASE+0X1CC)
*/
#define CAN_FMR                          *(volatile uint32_t*)(CAN_BASE+0X200)
#define CAN_FM1R                          *(volatile uint32_t*)(CAN_BASE+0X204)
#define CAN_FS1R                          *(volatile uint32_t*)(CAN_BASE+0X20C)
#define CAN_FFA1R                          *(volatile uint32_t*)(CAN_BASE+0X214)
#define CAN_FA1R                          *(volatile uint32_t*)(CAN_BASE+0X21C)
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
/*
#define CAN_F0R1                          *(volatile uint32_t*)(CAN_BASE+0X240)
#define CAN_F0R2                          *(volatile uint32_t*)(CAN_BASE+0X244)
#define CAN_F1R1                          *(volatile uint32_t*)(CAN_BASE+0X248)
#define CAN_F1R2                          *(volatile uint32_t*)(CAN_BASE+0X24C)
#define CAN_F2R1                          *(volatile uint32_t*)(CAN_BASE+0X250)
#define CAN_F2R2                          *(volatile uint32_t*)(CAN_BASE+0X254)
#define CAN_F3R1                          *(volatile uint32_t*)(CAN_BASE+0X258)
#define CAN_F3R2                          *(volatile uint32_t*)(CAN_BASE+0X25C)
#define CAN_F4R1                          *(volatile uint32_t*)(CAN_BASE+0X260)
#define CAN_F4R2                          *(volatile uint32_t*)(CAN_BASE+0X264)
#define CAN_F5R1                          *(volatile uint32_t*)(CAN_BASE+0X268)
#define CAN_F5R2                          *(volatile uint32_t*)(CAN_BASE+0X26C)
#define CAN_F6R1                          *(volatile uint32_t*)(CAN_BASE+0X270)
#define CAN_F6R2                          *(volatile uint32_t*)(CAN_BASE+0X274)
#define CAN_F7R1                          *(volatile uint32_t*)(CAN_BASE+0X278)
#define CAN_F7R2                          *(volatile uint32_t*)(CAN_BASE+0X27C)
#define CAN_F8R1                          *(volatile uint32_t*)(CAN_BASE+0X280)
#define CAN_F8R2                          *(volatile uint32_t*)(CAN_BASE+0X284)
#define CAN_F9R1                          *(volatile uint32_t*)(CAN_BASE+0X288)
#define CAN_F9R2                          *(volatile uint32_t*)(CAN_BASE+0X28C)
#define CAN_F10R1                          *(volatile uint32_t*)(CAN_BASE+0X290)
#define CAN_F10R2                          *(volatile uint32_t*)(CAN_BASE+0X294)
#define CAN_F11R1                          *(volatile uint32_t*)(CAN_BASE+0X298)
#define CAN_F11R2                          *(volatile uint32_t*)(CAN_BASE+0X29C)
#define CAN_F12R1                          *(volatile uint32_t*)(CAN_BASE+0X2A0)
#define CAN_F12R2                          *(volatile uint32_t*)(CAN_BASE+0X2A4)
#define CAN_F13R1                          *(volatile uint32_t*)(CAN_BASE+0X2A8)
#define CAN_F13R2                          *(volatile uint32_t*)(CAN_BASE+0X2AC)
*/
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

// EXTI
#define EXTI_BASE							0X40010400UL

// AFIO
#define AFIO_BASE							0X40010000UL

// USART1
#define USART1_BASE							0X40013800UL

//SPI1
#define SPI1_BASE 							0x40013000UL

//ADC
#define ADC1_BASE 							0x40012400UL
#define ADC2_BASE 							0x40012800UL

//Base addresses for BUS APB1 Peripherals
// USART2
#define USART2_BASE							0X40004400UL
// USART3
#define USART3_BASE							0X40004800UL
//SPI2
#define SPI2_BASE							0x40003800UL

#define I2C1_BASE							0x40005400UL

#define I2C2_BASE							0x40005800UL

//TIMER2-5
#define TIM2_BASE							0x40000000UL
#define TIM3_BASE							0x40000400UL
#define TIM4_BASE							0x40000800UL
#define TIM5_BASE							0x40000C00UL

//flash memory
#define Flash_BASE							0X40022000UL
//=========================================================================================

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:
//-*-*-*-*-*-*-*-*-*-*-*

//Peripheral register:GPIO
typedef struct
{
	volatile uint32_t CRL		;
	volatile uint32_t CRH		;
	volatile uint32_t IDR		;
	volatile uint32_t ODR		;
	volatile uint32_t BSRR		;
	volatile uint32_t BRR		;
	volatile uint32_t LCKR		;
}GPIO_TypeDef;

//Peripheral register:AFIO
typedef struct
{
	volatile uint32_t EVCR      ;
	volatile uint32_t MAPR      ;
	volatile uint32_t EXTICR[4] ;
	uint32_t RESERVED0          ;
	volatile uint32_t MAPR2     ;

}AFIO_TypeDef;

//Peripheral register:EXTI
typedef struct
{
	volatile uint32_t IMR		;
	volatile uint32_t EMR		;
	volatile uint32_t RTSR		;
	volatile uint32_t FTSR		;
	volatile uint32_t SWIER		;
	volatile uint32_t PR		;
}EXTI_TypeDef;

//Peripheral register:RCC
typedef struct
{
	volatile uint32_t CR		;
	volatile uint32_t CFGR		;
	volatile uint32_t CIR		;
	volatile uint32_t APB2RSTR	;
	volatile uint32_t APB1RSTR	;
	volatile uint32_t AHBENR	;
	volatile uint32_t APB2ENR	;
	volatile uint32_t APB1ENR	;
	volatile uint32_t BDCR		;
	volatile uint32_t CSR		;
}RCC_TypeDef;

typedef struct
{
	volatile uint32_t SR		;
	volatile uint32_t DR		;
	volatile uint32_t BRR		;
	volatile uint32_t CR1		;
	volatile uint32_t CR2		;
	volatile uint32_t CR3		;
	volatile uint32_t GTPR		;
}USART_TypeDef;

typedef struct
{
	volatile uint32_t CR1		;
	volatile uint32_t CR2		;
	volatile uint32_t SR		;
	volatile uint32_t DR		;
	volatile uint32_t CRCPR		;
	volatile uint32_t RXCRCR	;
	volatile uint32_t TXCRCR	;
	volatile uint32_t I2SCFGR	;
	volatile uint32_t I2SPR		;
}SPI_TypeDef;

typedef struct
{
	volatile uint32_t CR1		;
	volatile uint32_t CR2		;
	volatile uint32_t OAR1		;
	volatile uint32_t OAR2		;
	volatile uint32_t DR		;
	volatile uint32_t SR1		;
	volatile uint32_t SR2		;
	volatile uint32_t CCR		;
	volatile uint32_t TRISE		;
}I2C_TypeDef;

typedef struct
{
	volatile uint32_t CR1		;
	volatile uint32_t CR2		;
	volatile uint32_t SMCR		;
	volatile uint32_t DIER		;
	volatile uint32_t SR		;
	volatile uint32_t EGR		;
	volatile uint32_t CCMR1		;//Output Compare mode and input Compare mode
	volatile uint32_t CCMR2		;//input Compare mode and Output Compare mode
	volatile uint32_t CCER		;
	volatile uint32_t CNT		;
	volatile uint32_t PSC		;
	volatile uint32_t ARR		;
	uint32_t RESERVED0          ;
	volatile uint32_t CCR1		;
	volatile uint32_t CCR2		;
	volatile uint32_t CCR3		;
	volatile uint32_t CCR4		;
	uint32_t RESERVED1         	;
	volatile uint32_t DCR		;
	volatile uint32_t DMAR		;
}TIMx_TypeDef;

typedef struct
{
	volatile uint32_t SR		;
	volatile uint32_t CR1		;
	volatile uint32_t CR2		;
	volatile uint32_t SMPR1		;
	volatile uint32_t SMPR2		;
	volatile uint32_t JOFR1		;
	volatile uint32_t JOFR2		;
	volatile uint32_t JOFR3		;
	volatile uint32_t JOFR4		;
	volatile uint32_t HTR		;
	volatile uint32_t LTR		;
	volatile uint32_t SQR1		;
	volatile uint32_t SQR2		;
	volatile uint32_t SQR3		;
	volatile uint32_t JSQR		;
	volatile uint32_t GDR1		;
	volatile uint32_t GDR2		;
	volatile uint32_t GDR3		;
	volatile uint32_t GDR4		;
	volatile uint32_t DR		;
}ADCx_TypeDef;

typedef struct
{
	volatile uint32_t ACR;
	volatile uint32_t KEYR;
	volatile uint32_t OPTKEYR;
	volatile uint32_t SR;
	volatile uint32_t CR;
	volatile uint32_t AR;
	volatile uint32_t RESERVED;
	volatile uint32_t OBR;
	volatile uint32_t WRPR;
} FLASH_TypeDef;

typedef struct
{
	volatile uint32_t CAN_TIxR		;
	volatile uint32_t CAN_TDTxR		;
	volatile uint32_t CAN_TDLxR		;
	volatile uint32_t CAN_TDHxR		;
}CAN_TX_mailbox_TypeDef;

typedef struct
{
	volatile uint32_t CAN_RIxR		;
	volatile uint32_t CAN_RDTxR		;
	volatile uint32_t CAN_RDLxR		;
	volatile uint32_t CAN_RDHxR		;
}CAN_RX_FIFO_TypeDef;

typedef struct
{
	volatile uint32_t CAN_FiR1		;
	volatile uint32_t CAN_FiR2		;
}CAN_Filter_Bank_TypeDef;
//=========================================================================================

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*
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

#define GPIOA		((GPIO_TypeDef*)GPIOA_BASE)
#define GPIOB		((GPIO_TypeDef*)GPIOB_BASE)
#define GPIOC		((GPIO_TypeDef*)GPIOC_BASE)
#define GPIOD		((GPIO_TypeDef*)GPIOD_BASE)
#define GPIOE		((GPIO_TypeDef*)GPIOE_BASE)
#define RCC			((RCC_TypeDef*)RCC_BASE)

#define AFIO		((AFIO_TypeDef*)AFIO_BASE)

#define EXTI		((EXTI_TypeDef*)EXTI_BASE)

#define USART1		((USART_TypeDef*)USART1_BASE)
#define USART2		((USART_TypeDef*)USART2_BASE)
#define USART3		((USART_TypeDef*)USART3_BASE)

#define SPI1		((SPI_TypeDef*)SPI1_BASE)
#define SPI2		((SPI_TypeDef*)SPI2_BASE)

#define I2C1		((I2C_TypeDef*)I2C1_BASE)
#define I2C2		((I2C_TypeDef*)I2C2_BASE)

#define TIM2		((TIMx_TypeDef*)TIM2_BASE)
#define TIM3		((TIMx_TypeDef*)TIM3_BASE)
#define TIM4		((TIMx_TypeDef*)TIM4_BASE)
#define TIM5		((TIMx_TypeDef*)TIM5_BASE)

#define ADC1		((ADCx_TypeDef*)ADC1_BASE)
#define ADC2		((ADCx_TypeDef*)ADC2_BASE)

#define FLASH		((FLASH_TypeDef*)Flash_BASE)
//==========================================================================================

//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define RCC_GPIOA_CLK_EN()	(RCC->APB2ENR |=1<<2)
#define RCC_GPIOB_CLK_EN()	(RCC->APB2ENR |=1<<3)
#define RCC_GPIOC_CLK_EN()	(RCC->APB2ENR |=1<<4)
#define RCC_GPIOD_CLK_EN()	(RCC->APB2ENR |=1<<5)
#define RCC_GPIOE_CLK_EN()	(RCC->APB2ENR |=1<<6)
#define RCC_AFIO_CLK_EN()	(RCC->APB2ENR |=1<<0)

// USART
#define RCC_USART1_CLK_Enable()	(RCC->APB2ENR |=1<<14)
#define RCC_USART2_CLK_Enable()	(RCC->APB1ENR |=1<<17)
#define RCC_USART3_CLK_Enable()	(RCC->APB1ENR |=1<<18)

#define RCC_USART1_CLK_Disable()	(RCC->APB2RSTR |=1<<14)
#define RCC_USART2_CLK_Disable()	(RCC->APB1RSTR |=1<<17)
#define RCC_USART3_CLK_Disable()	(RCC->APB1RSTR |=1<<18)

//SPI
#define RCC_SPI1_CLK_Enable()	(RCC->APB2ENR |=1<<12)
#define RCC_SPI2_CLK_Enable()	(RCC->APB1ENR |=1<<14)

#define RCC_SPI1_CLK_Disable()	(RCC->APB2RSTR |=1<<12)
#define RCC_SPI2_CLK_Disable()	(RCC->APB1RSTR |=1<<14)

//I2C
#define RCC_I2C1_CLK_Enable()	(RCC->APB1ENR |=1<<21)
#define RCC_I2C2_CLK_Enable()	(RCC->APB1ENR |=1<<22)

#define RCC_I2C1_CLK_Disable()	(RCC->APB1RSTR |=1<<21)
#define RCC_I2C2_CLK_Disable()	(RCC->APB1RSTR |=1<<22)

//TIMER2
#define RCC_TIM2_CLK_Enable()	(RCC->APB1ENR |=1<<0)
#define RCC_TIM3_CLK_Enable()	(RCC->APB1ENR |=1<<1)
#define RCC_TIM4_CLK_Enable()	(RCC->APB1ENR |=1<<2)
#define RCC_TIM5_CLK_Enable()	(RCC->APB1ENR |=1<<3)

#define RCC_TIM2_CLK_Disable()	(RCC->APB1RSTR |=1<<0)
#define RCC_TIM3_CLK_Disable()	(RCC->APB1RSTR |=1<<1)
#define RCC_TIM4_CLK_Disable()	(RCC->APB1RSTR |=1<<2)
#define RCC_TIM5_CLK_Disable()	(RCC->APB1RSTR |=1<<3)

//ADC
#define RCC_ADC1_CLK_Enable()	(RCC->APB2ENR |=1<<9)
#define RCC_ADC2_CLK_Enable()	(RCC->APB2ENR |=1<<10)

#define RCC_ADC1_CLK_Disable()	(RCC->APB2RSTR |=1<<9)
#define RCC_ADC2_CLK_Disable()	(RCC->APB2RSTR |=1<<10)

//CAN
#define RCC_CAN_CLK_Enable()	(RCC->APB1ENR |=1<<25)
#define RCC_CAN_CLK_Disable()	(RCC->APB1RSTR |=1<<25)
//=============================================================================================

/*
 * *************************************************************
 *         IVT
 * *************************************************************
 *        EXTI
 * *************************************************************
 */
#define EXTI0_IRQ				6
#define EXTI1_IRQ				7
#define EXTI2_IRQ				8
#define EXTI3_IRQ				9
#define EXTI4_IRQ				10
#define EXTI5_IRQ				23
#define EXTI6_IRQ				23
#define EXTI7_IRQ				23
#define EXTI8_TRQ				23
#define EXTI9_IRQ				23
#define EXTI10_IRQ				40
#define EXTI11_IRQ				40
#define EXTI12_IRQ				40
#define EXTI13_IRQ				40
#define EXTI14_IRQ				40
#define EXTI15_IRQ				40
#define USART1_IRQ				37
#define USART2_IRQ				38
#define USART3_IRQ				39
#define SPI1_IRQ				35
#define SPI2_IRQ				36
#define I2C1_EV_IRQ				31
#define I2C1_ER_IRQ				32
#define I2C2_EV_IRQ				33
#define I2C2_ER_IRQ				34
#define TIM2_ER_IRQ				28//TIM2 global interrupt
#define TIM3_ER_IRQ				29//TIM3 global interrupt
#define TIM4_ER_IRQ				30//TIM4 global interrupt
#define TIM5_ER_IRQ				50//TIM5 global interrupt
#define ADC_IRQ					18//ADC global interrupt
#define CAN_TX_IRQ				(uint32_t)19
#define CAN_RX0_IRQ				(uint32_t)20
#define CAN_RX1_IRQ				(uint32_t)21
#define CAN_SCE_IRQ				(uint32_t)22
//=====================================================================================================
//-*-*-*-*-*-*-*-*-*-*-*-
//NVIC Enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define NVIC_IRQ6_EXTI0_Enable()							(NVIC_ISER0 |=1<<EXTI0_IRQ)
#define NVIC_IRQ7_EXTI1_Enable()							(NVIC_ISER0 |=1<<EXTI1_IRQ)
#define NVIC_IRQ8_EXTI2_Enable()							(NVIC_ISER0 |=1<<EXTI2_IRQ)
#define NVIC_IRQ9_EXTI3_Enable()							(NVIC_ISER0 |=1<<EXTI3_IRQ)
#define NVIC_IRQ10_EXTI4_Enable()							(NVIC_ISER0 |=1<<EXTI4_IRQ)
#define NVIC_IRQ23_EXTI5_to_EXTI9_Enable()					(NVIC_ISER0 |=1<<EXTI5_IRQ)
#define NVIC_IRQ40_EXTI10_to_EXTI15_Enable()				(NVIC_ISER1 |=1<<8) //40-32=8 bit number 8

//usart
#define NVIC_IRQ37_USART1_Enable()							(NVIC_ISER1 |=1<< ( USART1_IRQ - 32) )
#define NVIC_IRQ38_USART2_Enable()							(NVIC_ISER1 |=1<< ( USART2_IRQ - 32) )
#define NVIC_IRQ39_USART3_Enable()							(NVIC_ISER1 |=1<< ( USART3_IRQ - 32) )

//SPI
#define NVIC_IRQ35_SPI1_Enable()							(NVIC_ISER1 |=1<< ( SPI1_IRQ - 32) )
#define NVIC_IRQ36_SPI2_Enable()							(NVIC_ISER1 |=1<< ( SPI2_IRQ - 32) )

//I2C
#define NVIC_IRQ31_I2C1_EV_Enable()							(NVIC_ISER0 |=1<< ( I2C1_EV_IRQ ) )
#define NVIC_IRQ32_I2C1_ER_Enable()							(NVIC_ISER1 |=1<< ( I2C1_ER_IRQ - 32) )
#define NVIC_IRQ33_I2C2_EV_Enable()							(NVIC_ISER1 |=1<< ( I2C2_EV_IRQ - 32) )
#define NVIC_IRQ34_I2C2_ER_Enable()							(NVIC_ISER1 |=1<< ( I2C2_ER_IRQ - 32) )
//CAN
#define NVIC_IRQ19_CAN_TX_Enable()							(NVIC_ISER0 |=1<<CAN_TX_IRQ)
#define NVIC_IRQ20_CAN_RX0_Enable()							(NVIC_ISER0 |=1<<CAN_RX0_IRQ)
#define NVIC_IRQ21_CAN_RX1_Enable()							(NVIC_ISER0 |=1<<CAN_RX1_IRQ)
#define NVIC_IRQ22_CAN_SCE_Enable()							(NVIC_ISER0 |=1<<CAN_SCE_IRQ)

#define NVIC_IRQ28_TIM2_Enable()							(NVIC_ISER0 |=1<<TIM2_ER_IRQ)
#define NVIC_IRQ29_TIM3_Enable()							(NVIC_ISER0 |=1<<TIM3_ER_IRQ)
#define NVIC_IRQ30_TIM4_Enable()							(NVIC_ISER0 |=1<<TIM4_ER_IRQ)
#define NVIC_IRQ50_TIM5_Enable()							(NVIC_ISER1 |=1<< (TIM5_ER_IRQ - 32))

//ADC
#define NVIC_IRQ18_ADC_Enable()								(NVIC_ISER0 |=1<<ADC_IRQ)

//=====================================================================================================
//-*-*-*-*-*-*-*-*-*-*-*-
//NVIC Disable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define NVIC_IRQ6_EXTI0_Disable()						(NVIC_ICER0 |=1<<EXTI0_IRQ)
#define NVIC_IRQ7_EXTI1_Disable()						(NVIC_ICER0 |=1<<EXTI1_IRQ)
#define NVIC_IRQ8_EXTI2_Disable()						(NVIC_ICER0 |=1<<EXTI2_IRQ)
#define NVIC_IRQ9_EXTI3_Disable()						(NVIC_ICER0 |=1<<EXTI3_IRQ)
#define NVIC_IRQ10_EXTI4_Disable()						(NVIC_ICER0 |=1<<EXTI4_IRQ)
#define NVIC_IRQ23_EXTI5_to_EXTI9_Disable()				(NVIC_ICER0 |=1<<EXTI5_IRQ)
#define NVIC_IRQ40_EXTI10_to_EXTI15_Disable()			(NVIC_ICER1 |=1<<8) //40-32=8 bit number 8

//usart
#define NVIC_IRQ37_USART1_Disable()						(NVIC_ICER1 |=1<< ( USART1_IRQ - 32) )
#define NVIC_IRQ38_USART2_Disable()						(NVIC_ICER1 |=1<< ( USART2_IRQ - 32) )
#define NVIC_IRQ39_USART3_Disable()						(NVIC_ICER1 |=1<< ( USART3_IRQ - 32) )

//SPI
#define NVIC_IRQ35_SPI1_Disable()						(NVIC_ICER1 |=1<< ( SPI1_IRQ - 32) )
#define NVIC_IRQ36_SPI2_Disable()						(NVIC_ICER1 |=1<< ( SPI2_IRQ - 32) )

//I2C
#define NVIC_IRQ31_I2C1_EV_Disable()					(NVIC_ICER0 |=1<< ( I2C1_EV_IRQ ) )
#define NVIC_IRQ32_I2C1_ER_Disable()					(NVIC_ICER1 |=1<< ( I2C1_ER_IRQ - 32) )
#define NVIC_IRQ33_I2C2_EV_Disable()					(NVIC_ICER1 |=1<< ( I2C2_EV_IRQ - 32) )
#define NVIC_IRQ34_I2C2_ER_Disable()					(NVIC_ICER1 |=1<< ( I2C2_ER_IRQ - 32) )

#define NVIC_IRQ28_TIM2_Disable()						(NVIC_ICER0 |=1<<TIM2_ER_IRQ)
#define NVIC_IRQ29_TIM3_Disable()						(NVIC_ICER0 |=1<<TIM3_ER_IRQ)
#define NVIC_IRQ30_TIM4_Disable()						(NVIC_ICER0 |=1<<TIM4_ER_IRQ)
#define NVIC_IRQ50_TIM5_Disable()						(NVIC_ICER1 |=1<< ( TIM5_ER_IRQ - 32) )

//ADC
#define NVIC_IRQ18_ADC_Disable()						(NVIC_ICER0 |=1<<ADC_IRQ)
//CAN
#define NVIC_IRQ19_CAN_TX_Disable()							(NVIC_ICER0 |=1<<CAN_TX_IRQ)
#define NVIC_IRQ20_CAN_RX0_Disable()						(NVIC_ICER0 |=1<<CAN_RX0_IRQ)
#define NVIC_IRQ21_CAN_RX1_Disable()						(NVIC_ICER0 |=1<<CAN_RX1_IRQ)
#define NVIC_IRQ22_CAN_SCE_Disable()						(NVIC_ICER0 |=1<<CAN_SCE_IRQ)
//=====================================================================================================



/********************************************************/
/********************************************************/
/********************************************************/
/*******************  Bit definition  ********************/
/********************************************************/
/********************************************************/



/*******************  Bit definition for I2C_CR1 register  ********************/
#define I2C_CR1_PE_Pos                      (0U)
#define I2C_CR1_PE_Msk                      (0x1UL << I2C_CR1_PE_Pos)           /*!< 0x00000001 */
#define I2C_CR1_PE                          I2C_CR1_PE_Msk                     /*!< Peripheral Enable */
#define I2C_CR1_SMBUS_Pos                   (1U)
#define I2C_CR1_SMBUS_Msk                   (0x1UL << I2C_CR1_SMBUS_Pos)        /*!< 0x00000002 */
#define I2C_CR1_SMBUS                       I2C_CR1_SMBUS_Msk                  /*!< SMBus Mode */
#define I2C_CR1_SMBTYPE_Pos                 (3U)
#define I2C_CR1_SMBTYPE_Msk                 (0x1UL << I2C_CR1_SMBTYPE_Pos)      /*!< 0x00000008 */
#define I2C_CR1_SMBTYPE                     I2C_CR1_SMBTYPE_Msk                /*!< SMBus Type */
#define I2C_CR1_ENARP_Pos                   (4U)
#define I2C_CR1_ENARP_Msk                   (0x1UL << I2C_CR1_ENARP_Pos)        /*!< 0x00000010 */
#define I2C_CR1_ENARP                       I2C_CR1_ENARP_Msk                  /*!< ARP Enable */
#define I2C_CR1_ENPEC_Pos                   (5U)
#define I2C_CR1_ENPEC_Msk                   (0x1UL << I2C_CR1_ENPEC_Pos)        /*!< 0x00000020 */
#define I2C_CR1_ENPEC                       I2C_CR1_ENPEC_Msk                  /*!< PEC Enable */
#define I2C_CR1_ENGC_Pos                    (6U)
#define I2C_CR1_ENGC_Msk                    (0x1UL << I2C_CR1_ENGC_Pos)         /*!< 0x00000040 */
#define I2C_CR1_ENGC                        I2C_CR1_ENGC_Msk                   /*!< General Call Enable */
#define I2C_CR1_NOSTRETCH_Pos               (7U)
#define I2C_CR1_NOSTRETCH_Msk               (0x1UL << I2C_CR1_NOSTRETCH_Pos)    /*!< 0x00000080 */
#define I2C_CR1_NOSTRETCH                   I2C_CR1_NOSTRETCH_Msk              /*!< Clock Stretching Disable (Slave mode) */
#define I2C_CR1_START_Pos                   (8U)
#define I2C_CR1_START_Msk                   (0x1UL << I2C_CR1_START_Pos)        /*!< 0x00000100 */
#define I2C_CR1_START                       I2C_CR1_START_Msk                  /*!< Start Generation */
#define I2C_CR1_STOP_Pos                    (9U)
#define I2C_CR1_STOP_Msk                    (0x1UL << I2C_CR1_STOP_Pos)         /*!< 0x00000200 */
#define I2C_CR1_STOP                        I2C_CR1_STOP_Msk                   /*!< Stop Generation */
#define I2C_CR1_ACK_Pos                     (10U)
#define I2C_CR1_ACK_Msk                     (0x1UL << I2C_CR1_ACK_Pos)          /*!< 0x00000400 */
#define I2C_CR1_ACK                         I2C_CR1_ACK_Msk                    /*!< Acknowledge Enable */
#define I2C_CR1_POS_Pos                     (11U)
#define I2C_CR1_POS_Msk                     (0x1UL << I2C_CR1_POS_Pos)          /*!< 0x00000800 */
#define I2C_CR1_POS                         I2C_CR1_POS_Msk                    /*!< Acknowledge/PEC Position (for data reception) */
#define I2C_CR1_PEC_Pos                     (12U)
#define I2C_CR1_PEC_Msk                     (0x1UL << I2C_CR1_PEC_Pos)          /*!< 0x00001000 */
#define I2C_CR1_PEC                         I2C_CR1_PEC_Msk                    /*!< Packet Error Checking */
#define I2C_CR1_ALERT_Pos                   (13U)
#define I2C_CR1_ALERT_Msk                   (0x1UL << I2C_CR1_ALERT_Pos)        /*!< 0x00002000 */
#define I2C_CR1_ALERT                       I2C_CR1_ALERT_Msk                  /*!< SMBus Alert */
#define I2C_CR1_SWRST_Pos                   (15U)
#define I2C_CR1_SWRST_Msk                   (0x1UL << I2C_CR1_SWRST_Pos)        /*!< 0x00008000 */
#define I2C_CR1_SWRST                       I2C_CR1_SWRST_Msk                  /*!< Software Reset */
/*******************  Bit definition for I2C_CR2 register  ********************/
#define I2C_CR2_FREQ_Pos                    (0U)
#define I2C_CR2_FREQ_Msk                    (0x3FUL << I2C_CR2_FREQ_Pos)        /*!< 0x0000003F */
#define I2C_CR2_FREQ                        I2C_CR2_FREQ_Msk                   /*!< FREQ[5:0] bits (Peripheral Clock Frequency) */
#define I2C_CR2_ITERREN_Pos                 (8U)
#define I2C_CR2_ITERREN_Msk                 (0x1UL << I2C_CR2_ITERREN_Pos)      /*!< 0x00000100 */
#define I2C_CR2_ITERREN                     I2C_CR2_ITERREN_Msk                /*!< Error Interrupt Enable */
#define I2C_CR2_ITEVTEN_Pos                 (9U)
#define I2C_CR2_ITEVTEN_Msk                 (0x1UL << I2C_CR2_ITEVTEN_Pos)      /*!< 0x00000200 */
#define I2C_CR2_ITEVTEN                     I2C_CR2_ITEVTEN_Msk                /*!< Event Interrupt Enable */
#define I2C_CR2_ITBUFEN_Pos                 (10U)
#define I2C_CR2_ITBUFEN_Msk                 (0x1UL << I2C_CR2_ITBUFEN_Pos)      /*!< 0x00000400 */
#define I2C_CR2_ITBUFEN                     I2C_CR2_ITBUFEN_Msk                /*!< Buffer Interrupt Enable */
#define I2C_CR2_DMAEN_Pos                   (11U)
#define I2C_CR2_DMAEN_Msk                   (0x1UL << I2C_CR2_DMAEN_Pos)        /*!< 0x00000800 */
#define I2C_CR2_DMAEN                       I2C_CR2_DMAEN_Msk                  /*!< DMA Requests Enable */
#define I2C_CR2_LAST_Pos                    (12U)
#define I2C_CR2_LAST_Msk                    (0x1UL << I2C_CR2_LAST_Pos)         /*!< 0x00001000 */
#define I2C_CR2_LAST                        I2C_CR2_LAST_Msk                   /*!< DMA Last Transfer */
/*******************  Bit definition for I2C_OAR2 register  *******************/
#define I2C_OAR2_ENDUAL_Pos                 (0U)
#define I2C_OAR2_ENDUAL_Msk                 (0x1UL << I2C_OAR2_ENDUAL_Pos)      /*!< 0x00000001 */
#define I2C_OAR2_ENDUAL                     I2C_OAR2_ENDUAL_Msk                /*!< Dual addressing mode enable */
#define I2C_OAR2_ADD2_Pos                   (1U)
/*******************  Bit definition for I2C_SR1 register  ********************/
#define I2C_SR1_SB_Pos                      (0U)
#define I2C_SR1_SB_Msk                      (0x1UL << I2C_SR1_SB_Pos)           /*!< 0x00000001 */
#define I2C_SR1_SB                          I2C_SR1_SB_Msk                     /*!< Start Bit (Master mode) */
#define I2C_SR1_ADDR_Pos                    (1U)
#define I2C_SR1_ADDR_Msk                    (0x1UL << I2C_SR1_ADDR_Pos)         /*!< 0x00000002 */
#define I2C_SR1_ADDR                        I2C_SR1_ADDR_Msk                   /*!< Address sent (master mode)/matched (slave mode) */
#define I2C_SR1_BTF_Pos                     (2U)
#define I2C_SR1_BTF_Msk                     (0x1UL << I2C_SR1_BTF_Pos)          /*!< 0x00000004 */
#define I2C_SR1_BTF                         I2C_SR1_BTF_Msk                    /*!< Byte Transfer Finished */
#define I2C_SR1_ADD10_Pos                   (3U)
#define I2C_SR1_ADD10_Msk                   (0x1UL << I2C_SR1_ADD10_Pos)        /*!< 0x00000008 */
#define I2C_SR1_ADD10                       I2C_SR1_ADD10_Msk                  /*!< 10-bit header sent (Master mode) */
#define I2C_SR1_STOPF_Pos                   (4U)
#define I2C_SR1_STOPF_Msk                   (0x1UL << I2C_SR1_STOPF_Pos)        /*!< 0x00000010 */
#define I2C_SR1_STOPF                       I2C_SR1_STOPF_Msk                  /*!< Stop detection (Slave mode) */
#define I2C_SR1_RXNE_Pos                    (6U)
#define I2C_SR1_RXNE_Msk                    (0x1UL << I2C_SR1_RXNE_Pos)         /*!< 0x00000040 */
#define I2C_SR1_RXNE                        I2C_SR1_RXNE_Msk                   /*!< Data Register not Empty (receivers) */
#define I2C_SR1_TXE_Pos                     (7U)
#define I2C_SR1_TXE_Msk                     (0x1UL << I2C_SR1_TXE_Pos)          /*!< 0x00000080 */
#define I2C_SR1_TXE                         I2C_SR1_TXE_Msk                    /*!< Data Register Empty (transmitters) */
#define I2C_SR1_BERR_Pos                    (8U)
#define I2C_SR1_BERR_Msk                    (0x1UL << I2C_SR1_BERR_Pos)         /*!< 0x00000100 */
#define I2C_SR1_BERR                        I2C_SR1_BERR_Msk                   /*!< Bus Error */
#define I2C_SR1_ARLO_Pos                    (9U)
#define I2C_SR1_ARLO_Msk                    (0x1UL << I2C_SR1_ARLO_Pos)         /*!< 0x00000200 */
#define I2C_SR1_ARLO                        I2C_SR1_ARLO_Msk                   /*!< Arbitration Lost (master mode) */
#define I2C_SR1_AF_Pos                      (10U)
#define I2C_SR1_AF_Msk                      (0x1UL << I2C_SR1_AF_Pos)           /*!< 0x00000400 */
#define I2C_SR1_AF                          I2C_SR1_AF_Msk                     /*!< Acknowledge Failure */
#define I2C_SR1_OVR_Pos                     (11U)
#define I2C_SR1_OVR_Msk                     (0x1UL << I2C_SR1_OVR_Pos)          /*!< 0x00000800 */
#define I2C_SR1_OVR                         I2C_SR1_OVR_Msk                    /*!< Overrun/Underrun */
#define I2C_SR1_PECERR_Pos                  (12U)
#define I2C_SR1_PECERR_Msk                  (0x1UL << I2C_SR1_PECERR_Pos)       /*!< 0x00001000 */
#define I2C_SR1_PECERR                      I2C_SR1_PECERR_Msk                 /*!< PEC Error in reception */
#define I2C_SR1_TIMEOUT_Pos                 (14U)
#define I2C_SR1_TIMEOUT_Msk                 (0x1UL << I2C_SR1_TIMEOUT_Pos)      /*!< 0x00004000 */
#define I2C_SR1_TIMEOUT                     I2C_SR1_TIMEOUT_Msk                /*!< Timeout or Tlow Error */
#define I2C_SR1_SMBALERT_Pos                (15U)
#define I2C_SR1_SMBALERT_Msk                (0x1UL << I2C_SR1_SMBALERT_Pos)     /*!< 0x00008000 */
#define I2C_SR1_SMBALERT                    I2C_SR1_SMBALERT_Msk               /*!< SMBus Alert */

/*******************  Bit definition for I2C_SR2 register  ********************/
#define I2C_SR2_MSL_Pos                     (0U)
#define I2C_SR2_MSL_Msk                     (0x1UL << I2C_SR2_MSL_Pos)          /*!< 0x00000001 */
#define I2C_SR2_MSL                         I2C_SR2_MSL_Msk                    /*!< Master/Slave */
#define I2C_SR2_BUSY_Pos                    (1U)
#define I2C_SR2_BUSY_Msk                    (0x1UL << I2C_SR2_BUSY_Pos)         /*!< 0x00000002 */
#define I2C_SR2_BUSY                        I2C_SR2_BUSY_Msk                   /*!< Bus Busy */
#define I2C_SR2_TRA_Pos                     (2U)
#define I2C_SR2_TRA_Msk                     (0x1UL << I2C_SR2_TRA_Pos)          /*!< 0x00000004 */
#define I2C_SR2_TRA                         I2C_SR2_TRA_Msk                    /*!< Transmitter/Receiver */
#define I2C_SR2_GENCALL_Pos                 (4U)
#define I2C_SR2_GENCALL_Msk                 (0x1UL << I2C_SR2_GENCALL_Pos)      /*!< 0x00000010 */
#define I2C_SR2_GENCALL                     I2C_SR2_GENCALL_Msk                /*!< General Call Address (Slave mode) */
#define I2C_SR2_SMBDEFAULT_Pos              (5U)
#define I2C_SR2_SMBDEFAULT_Msk              (0x1UL << I2C_SR2_SMBDEFAULT_Pos)   /*!< 0x00000020 */
#define I2C_SR2_SMBDEFAULT                  I2C_SR2_SMBDEFAULT_Msk             /*!< SMBus Device Default Address (Slave mode) */
#define I2C_SR2_SMBHOST_Pos                 (6U)
#define I2C_SR2_SMBHOST_Msk                 (0x1UL << I2C_SR2_SMBHOST_Pos)      /*!< 0x00000040 */
#define I2C_SR2_SMBHOST                     I2C_SR2_SMBHOST_Msk                /*!< SMBus Host Header (Slave mode) */
#define I2C_SR2_DUALF_Pos                   (7U)
#define I2C_SR2_DUALF_Msk                   (0x1UL << I2C_SR2_DUALF_Pos)        /*!< 0x00000080 */
#define I2C_SR2_DUALF                       I2C_SR2_DUALF_Msk                  /*!< Dual Flag (Slave mode) */
#define I2C_SR2_PEC_Pos                     (8U)
#define I2C_SR2_PEC_Msk                     (0xFFUL << I2C_SR2_PEC_Pos)         /*!< 0x0000FF00 */
#define I2C_SR2_PEC                         I2C_SR2_PEC_Msk



#endif /* INC_STM32F103X6_H_ */
