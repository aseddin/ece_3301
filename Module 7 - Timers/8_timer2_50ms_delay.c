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
    T2CONbits.T2CKPS = 0x03; // 1:16 prescale value
    T2CONbits.T2OUTPS0 = 1; // 1:16 postscaler value
    T2CONbits.T2OUTPS1 = 1;
    T2CONbits.T2OUTPS2 = 1;
    T2CONbits.T2OUTPS3 = 1;
    
    // Load PR2 with the final value (PR2 is only 8 bits)
    // 50 ms delay
    PR2 = 48;
    
    // Turn on the timer
    T2CONbits.TMR2ON = 1; 
    
    // setting up timer2 as an interrupt
    PIR1bits.TMR2IF = 0;
    IPR1bits.TMR2IP = 1; // highpriority
    PIE1bits.TMR2IE = 1;
    
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


void __interrupt() timer2_interrupt()
{
    if (PIE1bits.TMR2IE && PIR1bits.TMR2IF)
    {
        PIR1bits.TMR2IF = 0;
        RED_LED = ~RED_LED;
        
    }
}