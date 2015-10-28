/*
 * outChar.c
 *
 *  Created on: Sep 24, 2015
 *      Author: apowell
 */
#include <stdint.h>
/*#include <msp430.h> uncomment both lines
/#include "led_toggle.h"*/

extern volatile uint8_t data;
extern volatile uint8_t FLAGS;
extern uint8_t CHECK_AUTO_COMP;
//#define UCA0TXIE 1

void uart_init(void){
    /* Configure P1.1 and P1.2 for UART (USC_A0) */
    /* (0bxxxxx11x xxxxxxxx) = 0x60 for both in order to specify P1.1(BIT1) and P1.2(BIT2)*/
    P1SEL |= 0x6; //ports P1.1 and P1.2 are now
    P1SEL2 |= 0x6;// selected to secondary peripheral use due to SEL and SEL2 set high.

/*sets software reset*/

    UCA0CTL1 |= UCSWRST;
    UCA0CTL1 |= UCSSEL_2;
    UCA0CTL0 = 0x00;     //  UCMODE_3 + UCSYNC //UCA0_CTL0_CONFIG
/* N = CLK/Baudrate -> 16MHz/9600 = ~104 = 0x0068 */

    UCA0BR0 = 104;  // 0x68 = 104 Least significant byte
    UCA0BR1 = 0;    // 0x00 = 0 Most significant byte
    UCA0MCTL = UCBRS0; // basically combines the MSB and LSB by controlling select registers

    UCA0CTL1 &= ~UCSWRST; //SWRST_clear
    IE2 |= UCA0RXIE; //UCA0RXIE
    IFG2 &= ~UCA0RXIFG; //toggles received flag
    __bis_SR_register(GIE); //sets the selected bits of SR(status register). GIE is general input enable
}                           // which enables any interrupt used in ISRs in the future.


void outChar(uint8_t u8_c){
    while(!(IFG2 & UCA0TXIFG)); //Transmit flag is not set, continue in loop.
    UCA0TXBUF= u8_c;            //Transmit flag is set, buffer is ready to accept data.



}

uint8_t inChar(void){
    while(UCRXEIE== 0 && (UCFE==1 || UCPE ==1)){
        toggle();
    }
    return (UCA0RXBUF);
}

void stringAuto_Complete(uint8_t string[],int size){
    int i;
    if(data =='H' || 'h'){
        if(data == 0x09){

         /*For loop allows transmitting buffer to give acknowledgement that it is ready to accept data.
          * The for loop then iterates through each letterin string
          * and waits for transmit buffer to be ready to accept data agian.*/
                for(i=0; i<size; i++){
                    UCA0TXBUF= string[i];
                    while(!(IFG2 & UCA0TXIFG));
                }

        }

    }


}

/* UART RX Interrupt Routine */

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    data = UCA0RXBUF;
    while(!(IFG2 & UCA0TXIFG));
    UCA0TXBUF= data;

    FLAGS |= CHECK_AUTO_COMP;  //Sets FLAGS to be equivalent to CHECK_AUTO_COMPLETE.
                               //Thereby enabling stringAuto_complete in main.

} 
