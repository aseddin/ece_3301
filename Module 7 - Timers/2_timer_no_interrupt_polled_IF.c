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
    T0CONbits.PSA = 1; // no prescaler (T0PS2:T0PS0 value doesn't matter)
    T0CONbits.T0CS = 0; // clock source is internal instruction cycle
    T0CONbits.T08BIT = 1; // let's start as an 8 bit timer
    T0CONbits.TMR0ON = 1; // Turn on timer
    
    // Initial LED states
    // LEDs are turn on with a 1 (anode connected to pin)
    GREEN_LED = 0;
    RED_LED = 0;
    
    while (1)
    {
        // toggle RED LED
        
        // Polling the value of TMR0L doesn't work well and is not really 
        // what you should be doing
        // The maximum delay that can be achieved with 8 bits is 1.024 mS
        // Instruction cycle = 1/4 MHz or 0.25 MHz or 250 KHz
        // Cycle period = 1/250 which is 4 uS
        // TMR0 is 8 bits ==> 4 * 256 = 1024 uS or 1.024 mS
        
        // So we cannot get to the 2 S yet, but let's test it with this value anyway
        // You won't be able to see the changes in the LED because it is too fast
        // You will have to see it on a scope
        
        // Interrupt flag is raised regardless if it is enabled or not
        if (INTCONbits.TMR0IF) 
        {
            INTCONbits.TMR0IF = 0;
            RED_LED = ~RED_LED; 
        }

        // Control Green LED with green switch
        GREEN_LED = SW;
    }
}

