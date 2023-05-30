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
    
    // Initial LED states
    // LEDs are turn on with a 1 (anode connected to pin)
    GREEN_LED = 0;
    RED_LED = 0;
    
    while (1)
    {
        // toggle RED LED
        __delay_ms(2000);
        RED_LED = ~RED_LED;
        
        // Control Green LED with green switch
        GREEN_LED = SW;
    }
}

