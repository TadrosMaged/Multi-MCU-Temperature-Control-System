/*
 * main.h
 *
 *  Created on: Aug 13, 2024
 *      Author: Dell
 */

#ifndef CODE_APP_MAIN_H_
#define CODE_APP_MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>

#include "../MCAL/adc.h"
#include "../MCAL/timer.h"
#include "../MCAL/dio.h"
#include "../MCAL/uart.h"

#include "../HAL/servo_motor.h"
#include "../HAL/dc_motor.h"
#include "../HAL/pot.h"


#define normal_state 	 0
#define emergency_state  1
#define abnormal_state 	 2


void normalState(void);
void emergencyState(void);
void abnormalState(void);

void checkState();

void shutdown(void);

float custom_strtof(const char *str);
#endif /* CODE_APP_MAIN_H_ */
