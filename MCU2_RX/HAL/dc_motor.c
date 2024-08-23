/*
 * dc_motor.c
 *
 *  Created on: Aug 15, 2024
 *      Author: Dell
 */

#include "dc_motor.h"

void set_speed(float speed_ratio)
{
	motor_speed=speed_ratio * 255;
}
