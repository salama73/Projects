/*
 * UltraSonic.c
 *
 * Created: 12/5/2022 12:54:55 AM
 *  Author: Salama Mohammed
 */ 

#include "UltraSonic.h"

long count1=0,count2=0;
double distance;
int TimerOverflow = 0;
void __vector_9 (void) __attribute__((signal));
void __vector_9 (void)
{
	TimerOverflow++;
}

void UltraSonic_Init(void)
{
	GPIO_Pinconfig_t GPIO_Conf ;
	GPIO_Conf.pinNumber = GPIO_PIN_0 ;
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	//MCAL_GPIO_Init(GPIOB , &GPIO_Conf ) ;
	
	GPIO_Conf.pinNumber = GPIO_PIN_6 ;
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_INPUT_PU ;
	MCAL_GPIO_Init(GPIOD , &GPIO_Conf ) ;
	
	EXTI_GLOBAL_Enable();
	TIMSK = (1 << 2);
	TIMER1->TCCR1A=0;
}


double UltraSonic_Get_Distance(void)
{
	hear:
	MCAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_SET);
	_delay_us(10);
	MCAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_RESET);
	TIMER1->TCNT1H=0;
	TIMER1->TCNT1L=0;
	TIFR = 1<<5;
	TIFR = 1<<2;
	TIMER1->TCCR1B=0X41; //rising
	while ((TIFR & (1 << 5)) == 0);
	count1=TIMER1->ICR1L ;
	count1 |=(TIMER1->ICR1H<<8);
	TIMER1->TCCR1B = 0x01;	/* Capture on falling edge*/
	TIFR = 1<<5;	/* Clear ICP flag (Input Capture flag) */
	TIFR = 1<<1;	/* Clear Timer Overflow flag */
	TimerOverflow = 0;/* Clear Timer overflow count */
	while ((TIFR & (1 << 5)) == 0);/* Wait for falling edge */
	count2=TIMER1->ICR1L ;
	count2 |=(TIMER1->ICR1H<<8);
	if (count2>count1)
	{
		count2 =  count2-count1-1+(TimerOverflow*65335);	/* Take count */
		TIMER1->TCCR1B = 0x00;
	} 
	else
	{
		TIMER1->TCCR1B = 0x00;
		goto hear ;
	}

	/* 1MHz Timer freq, sound speed =343 m/s */
	distance = (double)count2 /  58.30;
	return distance ;
}