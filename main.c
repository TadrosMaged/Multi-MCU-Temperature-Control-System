/*
 * main.c
 *
 *  Created on: Aug 11, 2024
 *      Author: Tadros
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>

#define normal_state 	 0
#define emergency_state  1
#define abnormal_state 	 2
#define PWM_Fan_Pin		 PB3
#define Fan_speed		 OCR0
uint8_t current_state;
uint8_t prev_state;

float current_temp;
float prev_temp;

uint8_t init = 0;


void normalState(void);
void emergencyState(void);
void abnormalState(void);

void setState(uint8_t temp);

void timer1_init(void);
void watchdog_init(void);

int main(void)
{
	//Enable interrupts
	sei();

	//PWM init
	//Set pin as output
	DDRB |= (1<<PWM_Fan_Pin);
	//Set timer0 as fast PWM, OCR0 non-inverting and prescaler = 8
	TCCR0 |= (1<<WGM00) | (1<<WGM01) | (1 << COM01) | (1 << CS01);

	//EEPROM
	current_state=eeprom_read_byte((uint8_t*)0x00);
	if(current_state == abnormal_state)
	{
		abnormalState();
	}

	//current_temp=read ADC

	eeprom_write_byte((uint8_t*)0x00,normal_state);

	while(1)
	{
		//current_temp=read_ADC
		//send current_temp by uart
		if( (current_temp != prev_temp) || (init==0) )
		{
			init=1;
			if(current_temp <= 50)
				current_state=normal_state;

			else if(current_temp > 50)
				current_state=emergency_state;

			setState(current_temp);
		}



	}

	return 0;
}

void setState(uint8_t temp)
{
	if(current_state != prev_state)
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
}
void normalState(void)
{
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
	else if(current_temp > 50)
	{
		emergencyState();
	}
}

void emergencyState(void)
{
	eeprom_write_byte((uint8_t*)0x00,emergency_state);

	//Set fan speed to max
	Fan_speed=255;

	timer1_init();

	watchdog_init();

}

void abnormalState(void)
{
	eeprom_write_byte((uint8_t*)0x00,abnormal_state);
	Fan_speed=255;
}


void watchdog_init(void) {
	//Disable interrupts
    cli();

    //Activate the watchdog timer with the smallest time to reset MCU1
    WDTCR = (1 << WDE) | (1 << WDP0);

    //Enable interrupts
    sei();
}

void timer1_init(void)
{
		//Set timer to CTC mode and prescaler to 64
		TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);

		//Compare value= ( (8MHz * 500ms)/64 ) -1
		OCR2 = 62499;

		//Enable Timer2 compare interrupt
		TIMSK |= (1 << OCIE2);
}


void button_init(void) {
    //Set PB0 as input
    DDRB &= ~(1 << PB0);

     // The falling edge of INT0 generates an interrupt request
    MCUCR = (1 << ISC01);

     //Enable external interrupt on INT0
    GICR = (1 << INT0);
}

ISR(TIMER1_COMPA_vect) {
	//current_temp=ADC_read
	static uint8_t count=0;
	if(count == 14)
	{
		abnormalState();
	}
	else
		count++;
}

ISR(INT0_vect) {

    //current_temp = ADCread

    if (current_temp >= 40 && current_temp <= 50) {
        //send_shutdown_command();
    }
}


