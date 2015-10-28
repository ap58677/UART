#include <msp430.h> 
#include <stdint.h>
#include "led_toggle.h"
#include "UART_I_O.h"


uint8_t CHECK_AUTO_COMP = 0x01;  //arbitary value, used mainly for flag comparision
volatile uint8_t data =0;        //global variable used to record receive buffer input
volatile uint8_t FLAGS = 0x00;  //Flag set in place to instatiate auto_complete function.
/*
 * main.c
 */
//uint8_t *commands[]={"show","interface","gigabit-ethernet","real","configuration"};

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    /* Configure the clock module - MCLK = 1MHz SMCLK = 1MHz */
    DCOCTL = 0;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
    /*uint8_t testString[]="Hello World";
    int size= sizeof(testString)/sizeof(testString[0]); Test for auto_complete*/
    uart_init();
    while(1){
       /* if(FLAGS & CHECK_AUTO_COMP){
            stringAuto_Complete(testString,size);
            FLAGS &= ~CHECK_AUTO_COMP;*/
        }
    }

}

