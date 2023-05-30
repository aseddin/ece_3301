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

# define LED RD0
# define SWITCH RC0

int main() 
{
    // Turn off the ADC
    ADCON1 = 0xff;
    
    // PORTD is output (connected to LED)
    TRISD = 0x00;
    
    // PORTC is input (connected to switch))
    TRISC = 0xff;
    
    // using bit variables
    //RD0 = RC0;
    
    // using struct
    //PORTDbits.RD0 = PORTCbits.RC0;
    
    while (1)
    {
        LED = SWITCH;
    }
    return (EXIT_SUCCESS);
}

