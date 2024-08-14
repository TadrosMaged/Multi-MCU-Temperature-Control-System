/*
 * main.h
 *
 *  Created on: Aug 13, 2024
 *      Author: Dell
 */

#ifndef CODE_APP_MAIN_H_
#define CODE_APP_MAIN_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>

#include "../MCAL/adc.h"
#include "../MCAL/timer.h"
#include "../MCAL/dio.h"
#include "../MCAL/uart.h"

#define F_CPU 8000000UL

#define normal_state 	 0
#define emergency_state  1
#define abnormal_state 	 2
#define PWM_Fan_Pin		 PB3
#define Fan_speed		 OCR0


float read_temperature(void);

void normalState(void);
void emergencyState(void);
void abnormalState(void);

void setState(uint8_t temp);

#endif /* CODE_APP_MAIN_H_ */
