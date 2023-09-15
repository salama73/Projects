/*
 * IR_Sensor.h
 *  Created on: 5/7/2023
 *  Author: Salama mohamed
 */

#ifndef INC_IR_SENSOR_H_
#define INC_IR_SENSOR_H_

#include "stm32_f103c6_GPIO.h"

void IR_Sensor_Init(void);
uint8_t IR_Sensor_Read(void);

#endif /* INC_IR_SENSOR_H_ */
