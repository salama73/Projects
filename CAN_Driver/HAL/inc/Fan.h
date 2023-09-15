/*
 * Fan.h
 *  Created on: 5/7/2023
 *  Author: Salama mohamed
 */

#ifndef INC_FAN_H_
#define INC_FAN_H_

#include <stm32_f103c6_TIM2_3.h>
#include "stm32_f103c6_RCC.h"

void Fan_Init(void);
void Fan_Speed(uint8_t speed);


#endif /* INC_FAN_H_ */
