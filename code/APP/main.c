/*
 * main.c
 *
 *  Created on: Aug 11, 2024
 *      Author: Tadros
 *
 *      MCU1
 */

#include "main.h"

uint8_t current_state;
float current_temp;

uint8_t init = 0;


int main(void)
{
	//Enable interrupts
	sei();

	//Set PWM pin as output
	DDRB |= (1<<PWM_Fan_Pin);

	//Set timer0 as fast PWM, OCR0 non-inverting and prescaler = 8
	TCCR0 |= (1<<WGM00) | (1<<WGM01) | (1 << COM01) | (1 << CS01);

	//ADC init
	ADC_ConfigType config={
			ADC_VCC,ADC_PR64
	};

	ADC_init(&config);

	Fan_speed=0;
	current_temp=0;

	//Read state from EEPROM
	current_state=eeprom_read_byte((uint8_t*)0x00);

	if(current_state == abnormal_state)
	{
		abnormalState();
	}


	while(1)
	{
		current_temp = read_temperature();

		uart_transmit(current_temp);

		if(current_temp <= 50)
			current_state=normal_state;

		else if(current_temp > 50)
			current_state=emergency_state;

		setState(current_temp);
	}
}

/******************************************************************************/

void setState(uint8_t temp)
{

		switch (current_state)
		{
		case normal_state: normalState();
		break;
		case emergency_state: emergencyState();
		break;
		case abnormal_state: abnormalState();
		break;
		default: return;
		}
}



void normalState(void)
{
	eeprom_write_byte((uint8_t*)0x00,normal_state);

	if(current_temp < 20)
	{
		//Stop fan
		Fan_speed=0;
	}
	else if(current_temp >= 20 && current_temp < 40)
	{
		//Set fan speed corresponding to temp
		Fan_speed=((current_temp-20)/20)*255;
	}
	else if(current_temp >= 40 && current_temp <= 50)
	{
		//Set fan speed to max
		Fan_speed=255;
	}

}



void emergencyState(void)
{
	eeprom_write_byte((uint8_t*)0x00,emergency_state);

	//Set fan speed to max
	Fan_speed=255;

	timer1_init();

}



void abnormalState(void)
{
	eeprom_write_byte((uint8_t*)0x00,abnormal_state);
	Fan_speed=255;
}



float read_temperature(void) {

	//Read ADC value from
	uint16_t adc_value = ADC_readChannel(0);

	//Convert ADC value to temperature
	float voltage = adc_value * (5.0 / 1024.0);
	float temperature = voltage*100;
	return temperature;
}



ISR(TIMER1_COMPA_vect) {
	//current_temp=ADC_read
	static uint8_t count=1;
	if(count == 14)
	{
		eeprom_write_byte((uint8_t*)0x00,abnormal_state);
		watchdog_init();
		abnormalState();
	}
	else
		count++;
}



ISR(INT0_vect) {

	current_temp = read_temperature();

	if (current_temp >= 40 && current_temp <= 50) {
		uart_transmit('T');
	}
}


