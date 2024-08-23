/*
 * interrupt.c
 *
 *  Created on: Aug 15, 2024
 *      Author: Dell
 */

#include <avr/io.h>

// Function to initialize external interrupt INT0
void INT0_Init(void) {
    MCUCR |= (1 << ISC01);  // Trigger INT0 on falling edge
    GICR |= (1 << INT0);    // Enable external interrupt INT0
}
