/*
 * timer.c
 *
 *  Created on: Aug 13, 2024
 *      Author: Dell
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

void timer0_init(void)
{
	TCCR0 |= (1<<WGM00) | (1<<WGM01) | (1 << COM01) | (1 << CS01);
}

void timer1_init(void)
{
    // Set fast PWM mode with ICR1 as top
    TCCR1A |= (1<<WGM11);
    TCCR1B |= (1<<WGM12) | (1<<WGM13);

    // Set non-inverting mode on OC1A (PD5)
    TCCR1A |= (1<<COM1A1);

    // Set prescaler to 8 and starts PWM
    TCCR1B |= (1<<CS11);

    // Set ICR1 value to define PWM frequency
    ICR1 = 19999; // for 50Hz PWM frequency

}



void timer1_deactivate(void)
{
    // Disable Timer1 interrupts by clearing OCIE1A and OCIE1B (Compare Match A and B) and TOIE1 (Overflow Interrupt)
    TIMSK &= ~( (1 << OCIE1A) | (1 << OCIE1B) | (1 << TOIE1) );

    // Stop Timer1 by clearing the clock source bits in TCCR1B (CS12, CS11, and CS10)
    TCCR1B &= ~( (1 << CS12) | (1 << CS11) | (1 << CS10) );

    // Optionally reset Timer1 counter
    TCNT1 = 0;
}



void watchdog_init(void) {
	//Disable interrupts
    cli();

    //Activate watchdog
    WDTCR = (1 << WDE) | (1 << WDP0);

    //Enable interrupts
    sei();
}

