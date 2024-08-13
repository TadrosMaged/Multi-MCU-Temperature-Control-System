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
		//Set timer to CTC mode and prescaler to 64
		TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);

		//Compare value= ( (8MHz * 500ms)/64 ) -1
		OCR2 = 62499;

		//Enable Timer2 compare interrupt
		TIMSK |= (1 << OCIE2);
}

void watchdog_init(void) {
	//Disable interrupts
    cli();

    //Activate watchdog
    WDTCR = (1 << WDE) | (1 << WDP0);

    //Enable interrupts
    sei();
}

