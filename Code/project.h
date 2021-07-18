/*
 * project.h
 *
 *  Created on: Nov 5, 2020
 *      Author: kassem
 */

#ifndef PROJECT_H_
#define PROJECT_H_


#include "adc.h"
#include "lcd.h"


#ifdef TIMER_0
#define MAX_TIMER_TICKS 256
#endif


#define ADC_CHANNEL_NUMBER (uint8)0

#define MOTOR_DDR DDRB
#define MOTOR_PORT PORTB
#define MOTOR_ENABLE PB3
#define MOTOR_INPUT1 PB0
#define MOTOR_INPUT2 PB1


#endif /* PROJECT_H_ */
