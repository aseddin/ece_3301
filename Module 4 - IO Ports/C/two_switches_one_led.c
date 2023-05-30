/* 
 * File:   newmain.c
 * Author: Anas Salah Eddin
 *
 * Created on June 29, 2020, 3:19 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
/*
 * 
 */

# define LED PORTCbits.RC7
# define SWITCH1 PORTDbits.RD6
# define SWITCH2 PORTDbits.RD7
int main() 
{
    // Turn off the ADC
    ADCON1 = 0xff;
    
    // PORTC is output (connected to LED)
    TRISC = 0x00;
    
    // PORTD is input (connected to switches)
    TRISD = 0xff;
    
    while (1)
    {
        if (SWITCH1 == SWITCH2)
            LED = 0; // Turn on LED (cathod connected to pin)
        else
            LED = 1;

        return (EXIT_SUCCESS);
    }
}

