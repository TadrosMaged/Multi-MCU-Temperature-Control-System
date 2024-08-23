/*
 * servo_motor.h
 *
 *  Created on: Aug 14, 2024
 *      Author: Tadros Maged
 */

#ifndef HAL_SERVO_MOTOR_H_
#define HAL_SERVO_MOTOR_H_

#include <avr/io.h>

#define motor_angle OCR1A
void set_right_angle(void);
void set_zero_angle(void);

void set_angle(uint8_t angle);

#endif /* HAL_SERVO_MOTOR_H_ */
