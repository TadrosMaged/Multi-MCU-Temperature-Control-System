/*
 * dio.c
 *
 *  Created on: Aug 13, 2024
 *      Author: Dell
 */
#include <avr/io.h>
#include "dio.h"


void button_init(void) {
    //Set PB0 as input
    DDRB &= ~(1 << PB0);

     // The falling edge of INT0 generates an interrupt request
    MCUCR = (1 << ISC01);

     //Enable external interrupt on INT0
    GICR = (1 << INT0);
}
