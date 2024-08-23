/*
 * servo_motor.c
 *
 *  Created on: Aug 14, 2024
 *      Author: Tadros Maged
 */
#include "servo_motor.h"

void set_right_angle(void)
{
	motor_angle= 1470;
}

void set_zero_angle(void)
{
	motor_angle= 1000;
}


void set_angle(uint8_t angle)
{

    switch(angle)
    {
    case 0:
    	motor_angle = 1500;
    	break;

    case 90:
    	motor_angle = 2500;
    	break;

    	default: motor_angle = 1500;
    }

}

