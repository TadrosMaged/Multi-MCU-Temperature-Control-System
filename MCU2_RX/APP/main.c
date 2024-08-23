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

float current_temp;

float pot = 0;

uint8 receivedMessage[15];

char state;



int main(void)
{
	//Enable interrupts
	sei();

	//Set PWM pin as output
	GPIO_setupPinDirection(PORTB_ID,PB3,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTD_ID,PD5,PIN_OUTPUT);

	//Set timer0 as fast PWM, OCR0 non-inverting and prescaler = 64
	timer0_init();

	//Set timer0 as fast PWM, OCR1A non-inverting and prescaler = 8
	timer1_init();



	//ADC init
	ADC_ConfigType config={
			ADC_VCC,ADC_PR64
	};

	ADC_init(&config);

	//UART init
	UART_init(9600);

	set_speed(0);

	//LED pins set to O/P
	GPIO_setupPinDirection(PORTC_ID,PC0,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTC_ID,PC1,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTC_ID,PC2,PIN_OUTPUT);

	GPIO_setupPinDirection(PORTC_ID,PC3,PIN_OUTPUT);

	//Buzzer pin set to O/P
	GPIO_setupPinDirection(PORTB_ID,PB0,PIN_OUTPUT);



	while(1)
	{

		pot=pot_read();
		set_speed(pot/pot_value);
	}
}

ISR(USART_RXC_vect) {

	cli();
	// Store the received data in a global variable
	UART_receiveString(receivedMessage);

	if(strcmp((char*)receivedMessage, "g") == 0)
	{
		state='g';
		normalState();
	}
	else if(strcmp((char*)receivedMessage, "y") == 0)
		{
			state='y';
			normalState();
		}
	else if(strcmp((char*)receivedMessage, "r") == 0)
		{
			state='r';
			normalState();
		}
	else if(strcmp((char*)receivedMessage, "e") == 0)
		{
			state='e';
			emergencyState();
		}
	else if(strcmp((char*)receivedMessage, "a") == 0)
			{
				state='a';
				abnormalState();
			}
	else if(strcmp((char*)receivedMessage, "s") == 0)
			{
				state='s';
				shutdown();
			}

sei();
}



/*****************************************************************************/



void normalState(void)
{
	if(state=='g')
	{
		//Lighten green led
		GPIO_writePin(PORTC_ID,PC0,LOGIC_HIGH);
		GPIO_writePin(PORTC_ID,PC1,LOGIC_LOW);
		GPIO_writePin(PORTC_ID,PC2,LOGIC_LOW);

		//Deactivate buzzer
		GPIO_writePin(PORTB_ID,PB0,LOGIC_LOW);
	}
	else if(state=='y')
	{
		//Lighten yellow led
		GPIO_writePin(PORTC_ID,PC0,LOGIC_LOW);
		GPIO_writePin(PORTC_ID,PC1,LOGIC_HIGH);
		GPIO_writePin(PORTC_ID,PC2,LOGIC_LOW);

		//Deactivate buzzer
		GPIO_writePin(PORTB_ID,PB0,LOGIC_LOW);
	}
	else if(state=='r')
	{
		//Lighten red led
		GPIO_writePin(PORTC_ID,PC0,LOGIC_LOW);
		GPIO_writePin(PORTC_ID,PC1,LOGIC_LOW);
		GPIO_writePin(PORTC_ID,PC2,LOGIC_HIGH);

		//Deactivate buzzer
		GPIO_writePin(PORTB_ID,PB0,LOGIC_LOW);
	}
}



void emergencyState(void)
{
	//Lighten red led
	GPIO_writePin(PORTC_ID,PC0,LOGIC_LOW);
	GPIO_writePin(PORTC_ID,PC1,LOGIC_LOW);
	GPIO_writePin(PORTC_ID,PC2,LOGIC_HIGH);

	//Activate buzzer
	GPIO_writePin(PORTB_ID,PB0,LOGIC_HIGH);


}



void abnormalState(void)
{
	//Lighten red led
	GPIO_writePin(PORTC_ID,PC0,LOGIC_LOW);
	GPIO_writePin(PORTC_ID,PC1,LOGIC_LOW);
	GPIO_writePin(PORTC_ID,PC2,LOGIC_HIGH);

	//Activate buzzer
	GPIO_writePin(PORTB_ID,PB0,LOGIC_HIGH);

	set_right_angle();

	shutdown();

}


void shutdown(void)
{
	set_right_angle();

	set_speed(0);
	_delay_ms(1000);
	/*function supposed to check if condition changed but time ran up*/
	/*
	while(state='r')
		{

		}
		*/

}







