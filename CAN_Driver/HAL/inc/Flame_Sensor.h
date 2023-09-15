/*
 * Flame_Sensor.h
 *  Created on: 5/7/2023
 *  Author: Salama mohamed
 */

#ifndef INC_FLAME_SENSOR_H_
#define INC_FLAME_SENSOR_H_

#include "stm32_f103c6_ADC.h"
#include "stm32_f103c6_GPIO.h"

void Flame_Sensor_Init(void);
uint16_t Flame_Sensor_Read(void);

#endif /* INC_FLAME_SENSOR_H_ */
