/* 
 * File:   newmain.c
 * Author: Anas Salah Eddin
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"


# define _XTAL_FREQ 1000000

# define GREEN_LED PORTBbits.RB2
# define RED_LED PORTBbits.RB1
# define SW PORTBbits.RB0

int main() 
{
    // All AN inputs are digital
    ADCON1 = 0x0F;
    
    // setup in/out pins
    // Outputs for LEDs
    TRISBbits.RB2 = 0;
    TRISBbits.RB1 = 0;
    
    // input for switch
    TRISBbits.RB0 = 1;
    
    
    // setup timer0 
    T0CONbits.PSA = 0; // Prescaler is assigned
    T0CONbits.T0PS = 0x05; // 1:64 prescale value
    T0CONbits.T0CS = 0; // clock source is internal instruction cycle
    T0CONbits.T08BIT = 0; // operate in 16 bit mode now
    T0CONbits.TMR0ON = 1; // Turn on timer
    TMR0 = 43076; // For 5.75 second delay (with 1:64 prescaler)
    
    // setting up timer0 as an interrupt
    INTCONbits.TMR0IE = 1;
    INTCONbits.TMR0IF = 0;
    INTCON2bits.TMR0IP = 1; // high priority 
    RCONbits.IPEN = 0; // turn off all priorities
    INTCONbits.PEIE = 1; // enable all unmasked peripheral interrupts
    INTCONbits.GIE = 1;// enable all interrupts
    
    // Initial LED states
    // LEDs are turn on with a 1 (anode connected to pin)
    GREEN_LED = 0;
    RED_LED = 0;
    
    while (1)
    {
        // Control Green LED with green switch
        GREEN_LED = SW;
    }
}


void __interrupt() timer0_interrupt()
{
    
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF)
    {
        INTCONbits.TMR0IF = 0;
        TMR0 = 43076; // For 5.75 second delay (with 1:64 prescaler)
        RED_LED = ~RED_LED;
    }
}