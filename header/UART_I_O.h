/*
 * UART_I_O.h
 *
 *  Created on: Sep 24, 2015
 *      Author: apowell
 */


#ifndef UART_I_O_H_
#define UART_I_O_H_

#include <stdint.h>

void uart_init(void);

void outChar(uint8_t u8_c);

uint8_t inChar(void);

void stringAuto_Complete(uint8_t string[],int size);

#endif

