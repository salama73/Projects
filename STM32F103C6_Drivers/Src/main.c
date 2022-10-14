/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include"stm32_f103c6_GPIO.h"
#include"stm32_f103c6_EXTI.h"
#include "stm32f103x6.h"
#include"stm32_f103c6_USART.h"
#include"stm32_f103c6_SPI.h"
#include "stm32_f103c6_I2C.h"
#include "LCD.h"
#include "Keypad.h"
#include "EEPROM.h"

uint8_t DATA;

void Clock_INIT(void)
{
	//set on the clock for PORTA
	RCC_GPIOA_CLK_EN();
	//set on the clock for PORTB
	RCC_GPIOB_CLK_EN();
	//set on the clock for AFIO
	RCC_AFIO_CLK_EN();
}


void I2C1_IRQ_Call ( Slave_State state)
{
	switch(state)
	{
	case I2C_EV_STOP:
		I2C1->SR1 &=~(I2C_SR1_AF) ;
		break ;
	case I2C_EV_ADDR_Matched:
		break ;
	case I2C_EV_DATA_REQ:
		MCAL_I2C_Slave_TX(I2C1, DATA) ;
		break ;
	case I2C_EV_DATA_RCV:
		DATA=MCAL_I2C_Slave_RX(I2C1) ;
		break ;
	}
}


int main(void)
{
	Clock_INIT();
	uint8_t Data1[] = {0x1,0x2,0x3,0x4,0x5,0x6,0x7};
	uint8_t Data2[7]= {0};

	EEPROM_Init();
	EEPROM_Write_Data(0xAF, Data1, 7);
	EEPROM_Read_Data(0xAF, Data2, 7);

	Data1[0] = 0xA;
	Data1[1] = 0xB;
	Data1[2] = 0xC;
	Data1[3] = 0xD;

	EEPROM_Write_Data(0xFFF, Data1, 4);
	EEPROM_Read_Data(0xFFF, Data2, 4);

	while (1)
	{
	}

}

