/*
 * adc.c
 *
 *  Created on: Aug 13, 2024
 *      Author: Dell
 */
#include <avr/io.h>
#include "adc.h"

void adc_init(void) {
    // Set ADC prescaler to 64
    ADCSRA = (1 << ADPS2) | (1 << ADPS1);

    // Set ADC reference voltage to AVcc
    ADMUX = (1 << REFS0);
}

uint16_t adc_read(uint8_t channel) {
    // Select the channel
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

    // Start the conversion
    ADCSRA |= (1 << ADSC);

    // Wait for conversion to complete
    while (ADCSRA & (1 << ADSC));

    return ADC;
}

