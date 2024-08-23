
/*
 * main.c
 *
 *  Created on: Aug 11, 2024
 *      Author: Tadros
 *
 *      MCU1
 */

#include "main.h"

uint8 current_state = normal_state;

float current_temp = 0;

uint8 count = 1;

char str[5];


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

	//UART init
	UART_init(9600);

	//Configure button pin
	GPIO_setupPinDirection(PORTD_ID,PD2,PIN_INPUT);
	PORTD |= (1 << PD2);

	//INT0 init
	INT0_Init();


	//Set initial fan speed to 0
	set_speed(0);

	//Read state from EEPROM
	current_state=eeprom_read_byte((uint8_t*)0x00);



	if(current_state == abnormal_state)
	{
		abnormalState();
	}

	current_state=normal_state;

	//Initial delay for proteus software to read temperature sensor correctly
	_delay_ms(250);

	while(1)
	{
		current_temp = read_temperature();

		if(current_temp <= 50)
			current_state=normal_state;

		else if(current_temp > 50)
			current_state=emergency_state;

		setState(current_temp);

	}
}

/******************************************************************************/
ISR(INT0_vect) {

	if (current_temp >= 40.0 && current_temp <= 50.0) {

		GPIO_writePin(PORTC_ID,PC0,LOGIC_HIGH);

		UART_sendString("s#");
	}

}


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
		UART_sendString("g#");
		set_speed(0);
	}
	else if(current_temp >= 20 && current_temp < 40)
	{
		UART_sendString("y#");
		//Set fan speed corresponding to temp
		uint8_t Fan_speed = ((current_temp-20)/20) * 255;
		//set_speed(Fan_speed);
		OCR0=Fan_speed;
	}
	else if(current_temp >= 40 && current_temp <= 50)
	{
		UART_sendString("r#");
		//Set fan speed to max
		set_speed(255);
	}
}



void emergencyState(void)
{
	eeprom_write_byte((uint8_t*)0x00,emergency_state);

	UART_sendString("e#");

	//Set fan speed to max
	set_speed(255);

	GPIO_writePin(PORTC_ID,PC0,LOGIC_HIGH);

	timer1_init();

}



void abnormalState(void)
{
	eeprom_write_byte((uint8_t*)0x00,abnormal_state);

	UART_sendString("a#");

	set_speed(255);
}







ISR(TIMER1_COMPA_vect) {

	current_temp = read_temperature();

	if(current_temp > 50)
	{

		if(count == 14)
		{
			eeprom_write_byte((uint8_t*)0x00,abnormal_state);


			watchdog_init();
			abnormalState();
		}
		else
			count++;
	}
	else
	{
		timer1_deactivate();
	}

}




