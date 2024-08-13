/*
 * uart.c
 *
 *  Created on: Aug 13, 2024
 *      Author: Dell
 */
#include <avr/io.h>
#include "uart.h"

void uart_init(void) {
    //Set baud rate to 9600 with 8 MHz clock
    uint16_t ubrr = 51; // Calculated value for 9600 baud rate
    UBRRH = (uint8_t)(ubrr >> 8);
    UBRRL = (uint8_t)ubrr;

    //Enable transmitter
    UCSRB = (1 << TXEN);

    //Set frame format: 8 data bits, 1 stop bit
    UCSRC = (1 << UCSZ1) | (1 << UCSZ0);
}

void uart_transmit(uint8_t data) {
    // Wait for empty transmit buffer
    while (!(UCSRA & (1 << UDRE)));
    // Put data into buffer, sends the data
    UDR = data;
}

unsigned char uart_receive(void) {
    // Wait for data to be received
    while (!(UCSRA & (1 << RXC)));
    // Get and return received data from the buffer
    return UDR;
}

