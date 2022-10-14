/*
 * stm32_f103c6_RCC.c
 *
 *  Created on: ٠٤‏/٠٩‏/٢٠٢٢
 *  Author: Salama mohamed
 */

#include "stm32_f103c6_RCC.h"

const uint8_t HPRE_table [16] = {0,0,0,0,0,0,0,1,2,3,4,6,7,8,9};
/*
Bits 7:4 HPRE[3:0]: AHB prescaler
Set and cleared by software to control AHB clock division factor.
0xxx: SYSCLK not divided
1000: SYSCLK divided by 2
1001: SYSCLK divided by 4
1010: SYSCLK divided by 8
1011: SYSCLK divided by 16
1100: SYSCLK divided by 64
1101: SYSCLK divided by 128
1110: SYSCLK divided by 256
1111: SYSCLK divided by 512
*/

const uint8_t PPRE1_table [8] = {0,0,0,0,1,2,3,4};
/*
Bits 10:8 PPRE1[2:0]: APB Low-speed prescaler (APB1)
Set and cleared by software to control the division factor of the APB Low speed clock (PCLK1).
0xx: HCLK not divided
100: HCLK divided by 2
101: HCLK divided by 4
110: HCLK divided by 8
111: HCLK divided by 16
*/

uint32_t MCAL_Get_SYSCLC_FREQ(void)
{
	//Bits 3:2 SWS[1:0]: System clock switch status
	//Set and cleared by hardware to indicate which clock source is used as system clock.
	//00: HSI oscillator used as system clock
	//01: HSE oscillator used as system clock
	//10: PLL used as system clock
	//11: Not applicable

	switch(RCC->CFGR >> 2)
	{
	case 0:
		return HSI_oscillator_clock ;
		break;
	case 1:
		return HSE_oscillator_clock ;
		break;
	}
}
uint32_t MCAL_Get_HCLC_FREQ(void)
{
	//Bits 7:4 HPRE[3:0]: AHB prescaler
	return ( MCAL_Get_SYSCLC_FREQ() >> HPRE_table[ ( RCC->CFGR >> 4 ) & 0XF ] ) ;
}
uint32_t MCAL_Get_PCLC1_FREQ(void)
{
	//Bits 10:8 PPRE1[2:0]: APB Low-speed prescaler (APB1)
	return ( MCAL_Get_SYSCLC_FREQ() >> PPRE1_table[ ( RCC->CFGR >> 8 ) & 0X11 ] ) ;
}
uint32_t MCAL_Get_PCLC2_FREQ(void)
{
	//Bits 13:11 PPRE2[2:0]: APB high-speed prescaler (APB2)
	return ( MCAL_Get_SYSCLC_FREQ() >> PPRE1_table[ ( RCC->CFGR >> 11 ) & 0X11 ] ) ;
}
