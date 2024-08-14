/*
 * timer.c
 *
 *  Created on: Aug 13, 2024
 *      Author: Dell
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

void timer1_init(void)
{
    // Set Timer1 to CTC mode (WGM12 bit in TCCR1B)
    TCCR1B |= (1 << WGM12);

    // Set prescaler to 64 (CS11 and CS10 bits in TCCR1B)
    TCCR1B |= (1 << CS11) | (1 << CS10);

    // Set the compare value for 500ms delay: ( (8MHz * 0.5s)/64 ) - 1 = 62499
    OCR1A = 62499;

    // Enable Timer1 Compare Match A interrupt (OCIE1A bit in TIMSK)
    TIMSK |= (1 << OCIE1A);
}


void watchdog_init(void) {
	//Disable interrupts
    cli();

    //Activate watchdog
    WDTCR = (1 << WDE) | (1 << WDP0);

    //Enable interrupts
    sei();
}

