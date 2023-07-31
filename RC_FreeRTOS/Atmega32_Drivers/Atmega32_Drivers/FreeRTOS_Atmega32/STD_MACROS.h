/*
 * STD_MACROS.h
 *
 * Created: 17/03/2022 11:39:34 ص
 *  Author: DELL
 */ 


#ifndef STD_MACROS_H_
#define STD_MACROS_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "STD_Types.h"
#define SET_BIT(VAR,BITNO) (VAR) |=(1<<(BITNO))
#define CLR_BIT(VAR,BITNO) (VAR) &=~(1<<(BITNO))
#define TOG_BIT(VAR,BITNO) (VAR) ^=(1<<(BITNO))
#define READ_BIT(VAR,BITNO) (((VAR) >>(BITNO))&1)




#endif /* STD_MACROS_H_ */