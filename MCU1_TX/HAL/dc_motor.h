/*
 * dc_motor.h
 *
 *  Created on: Aug 14, 2024
 *      Author: Dell
 */

#ifndef CODE_HAL_DC_MOTOR_H_
#define CODE_HAL_DC_MOTOR_H_

#include <avr/io.h>

#define motor_speed OCR0

void set_speed(uint8_t speed);

#endif /* CODE_HAL_DC_MOTOR_H_ */
