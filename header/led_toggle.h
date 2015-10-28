#include <msp430.h>
#include <stdint.h>
#include "led_toggle.h"

/*
 * led_toggle.c
 *
 *  Created on: Sep 24, 2015
 *      Author: apowell
 */

void toggle(void)
{
    P1DIR|=0x01;
    volatile unsigned int i = 1;

    P1OUT^=0x01;
    //delay();
    while(i<=10000)
    {
        i++;
    }
}

