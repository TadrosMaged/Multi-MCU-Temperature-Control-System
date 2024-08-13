/*
 * adc.h
 *
 *  Created on: Aug 13, 2024
 *      Author: Dell
 */

#ifndef CODE_MCAL_ADC_H_
#define CODE_MCAL_ADC_H_

#include <avr/io.h>
#include "adc.h"
uint16_t adc_read(uint8_t channel);
void adc_init(void);

#endif /* CODE_MCAL_ADC_H_ */
