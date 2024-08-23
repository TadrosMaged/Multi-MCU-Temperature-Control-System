/*
 * main.h
 *
 *  Created on: Aug 13, 2024
 *      Author: Dell
 */

#ifndef CODE_APP_MAIN_H_
#define CODE_APP_MAIN_H_

#include <stdlib.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>

#include  "../LIB/std_types.h"
#include  "../LIB/common_macros.h"

#include "../MCAL/adc.h"
#include "../MCAL/timer.h"
#include "../MCAL/dio.h"
#include "../MCAL/uart.h"
#include "../MCAL/interrupt.h"

#include "../HAL/dc_motor.h"
#include "../HAL/temp_sensor.h"


#define normal_state 	 0
#define emergency_state  1
#define abnormal_state 	 2
#define PWM_Fan_Pin		 PB3


float read_temperature(void);

void normalState(void);
void emergencyState(void);
void abnormalState(void);

void setState(uint8_t temp);

#endif /* CODE_APP_MAIN_H_ */
