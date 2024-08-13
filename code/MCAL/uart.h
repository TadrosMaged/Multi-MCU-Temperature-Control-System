/*
 * uart.h
 *
 *  Created on: Aug 13, 2024
 *      Author: Dell
 */

#ifndef CODE_MCAL_UART_H_
#define CODE_MCAL_UART_H_

void uart_init(void);
void uart_transmit(uint8_t data);
unsigned char uart_receive(void);

#endif /* CODE_MCAL_UART_H_ */
