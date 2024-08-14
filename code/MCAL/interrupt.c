/*
 * interrupt.c
 *
 *  Created on: Aug 14, 2024
 *      Author: Dell
 */

#include <avr/io.h>
#include <avr/interrupt.h>

void interrupt0_init(void)
{
    // Set the button pin (e.g., PD2) as input
    DDRD &= ~(1 << PD2);

    // Enable internal pull-up resistor on PD2
    //PORTD |= (1 << PD2);

    // Configure INT0 to trigger on the rising edge (button press connects to VCC)
        MCUCR |= (1 << ISC01) | (1 << ISC00);  // ISC01 = 1, ISC00 = 1 -> Rising edge

    // Enable INT0
    GICR |= (1 << INT0);

    // Enable global interrupts
    sei();
}

