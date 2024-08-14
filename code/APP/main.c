/*
 * main.c
 *
 *  Created on: Aug 11, 2024
 *      Author: Tadros
 *
 *      MCU1
 */

#include "main.h"

uint8_t current_state = normal_state;
float current_temp = 0;

uint8_t count = 1;


int main(void)
{
	//Enable interrupts
	sei();

	//Set PWM pin as output
	GPIO_setupPinDirection(PORTB_ID,PB3,PIN_OUTPUT);

	//Set timer0 as fast PWM, OCR0 non-inverting and prescaler = 64
	timer0_init();

	//ADC init
	ADC_ConfigType config={
			ADC_VCC,ADC_PR64
	};

	ADC_init(&config);

	Fan_speed=0;

	//Read state from EEPROM
	current_state=eeprom_read_byte((uint8_t*)0x00);

	GPIO_setupPinDirection(PORTC_ID,PC0,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTC_ID,PC1,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTC_ID,PC2,PIN_OUTPUT);

	for(int i=0;i<=2;i++)
	{
		GPIO_writePin(PORTC_ID,PC1,LOGIC_HIGH);
		_delay_ms(1000);
		GPIO_writePin(PORTC_ID,PC1,LOGIC_LOW);
		_delay_ms(1000);
	}





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

	GPIO_writePin(PORTC_ID,PC0,LOGIC_HIGH);
	timer1_init();

}



void abnormalState(void)
{
	eeprom_write_byte((uint8_t*)0x00,abnormal_state);
	Fan_speed=255;
}







ISR(TIMER1_COMPA_vect) {

	current_temp = read_temperature();

	if(current_temp > 50)
	{
		GPIO_writePin(PORTC_ID,PC2,LOGIC_HIGH);
		_delay_ms(500);
		GPIO_writePin(PORTC_ID,PC2,LOGIC_LOW);
		_delay_ms(500);

		if(count == 14)
		{
			eeprom_write_byte((uint8_t*)0x00,abnormal_state);
			GPIO_writePin(PORTC_ID,PC0,LOGIC_LOW);
			_delay_ms(2000);
			GPIO_writePin(PORTC_ID,PC0,LOGIC_HIGH);
			watchdog_init();
			abnormalState();
		}
		else
			count++;
	}
	else
	{
		GPIO_writePin(PORTC_ID,PC0,LOGIC_LOW);
		timer1_deactivate();
	}
}



ISR(INT0_vect) {

	current_temp = read_temperature();

	if (current_temp >= 40 && current_temp <= 50) {
		uart_transmit('T');
	}
}
