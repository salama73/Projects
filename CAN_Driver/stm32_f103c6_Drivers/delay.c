/*
 * delay.c
 *
 *  Created on: 20/2/2023
 *  Author: Salama mohamed
 */

#include "delay.h"


void delay_ms(int ms)
{
	// timer2 work at 8 MHZ set psc 7999 ( each increment take 1ms )
	TIM4->PSC=7999;
	// timer count at ms-1
	TIM4->ARR=ms-1;
	// enable counter
	TIM4->CR1 |=1<<0;
	// wait until counter reached compared register
	while(!(TIM4->SR & 1<<0));
	// clear flag
	TIM4->SR=0;
	// disable counter
	TIM4->CR1 =0;
}

void delay_us(int us)
{
	// timer2 work at 8 MHZ set psc 7999 ( each increment take 1us )
	TIM4->PSC=7;
	// timer count at us-1
	TIM4->ARR=us-1;
	// enable counter
	TIM4->CR1 |=1<<0;
	// wait until counter reached compared register
	while(!(TIM4->SR & 1<<0));
	// clear flag
	TIM4->SR=0;
	// disable counter
	TIM4->CR1 |=0;
}
