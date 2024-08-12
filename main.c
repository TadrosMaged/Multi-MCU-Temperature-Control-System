/*
 * main.c
 *
 *  Created on: Aug 11, 2024
 *      Author: Tadros
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>

#define normal_state 	 0
#define emergency_state  1
#define abnormal_state 	 2

uint8_t current_state;

void normalState(void);
void emergencyState(void);
void abnormalState(void);
void motorSpeed(int temp);

int main(void)
{

	//EEPROM
	//current_state = eeprom_read_byte((uint8_t*)0x00);
	//eeprom_write_block((uint8_t*)0x00,normalState);

	//

	while(1)
	{

	}

	return 0;
}

void normal_state(void)
{
	//From 20C to 40C fan increase gradually by mcu1
	//mcu2 light yellow led
	//
	//Between 40C to 50C the fan is at max by mcu1
	//mcu2 lights red and shut down motor if button pressed
}

void emergency_state(void)
{
	//Above 50C
	//Begin counting time.
	//use timer with overflow to check temperature 14 times each 500ms
	//MCU1 moves the fan with max speed
	//MCU2 lightens red LED and runs buzzer.
	//if activated for 7sec
		//Write abnormal state in E2PROM
		//MCU1 activates the watchdog timer with the smallest time to reset MCU1
		//MCU2 follow the abnormal condition for 5 seconds
}

void abnormal_state(void)
{
	//set for 5 sec
	//MCU1 moves the fan with max speed
	//MCU2 lighten red LED, open servo with 90 degrees, stop the machine and run the buzzer
}
