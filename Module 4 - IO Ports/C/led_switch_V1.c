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
int main() 
{
    // Turn off the ADC
    ADCON1 = 0xff;
    
    // PORTD is output (connected to LED)
    TRISD = 0x00;
    
    // PORTC is input (connected to switch))
    TRISC = 0xff;
    
    while (1)
    {
        // using bit variables
        RD0 = RC0;
    
        // using struct
        //PORTDbits.RD0 = PORTCbits.RC0;
    }

    
    return (EXIT_SUCCESS);
}

