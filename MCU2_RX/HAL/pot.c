/*
 * temp_sensor.c
 *
 *  Created on: Aug 14, 2024
 *      Author: Dell
 */

#include <avr/io.h>

#include "../MCAL/adc.h"
#include "pot.h"

float pot_read(void) {

	//Read ADC value from
	uint16_t adc_value = ADC_readChannel(0);

	//Convert ADC value to temperature
	float voltage = adc_value * (5.0 / 1024.0);
	float pot = (voltage/5) * pot_value;
	return pot;
}
