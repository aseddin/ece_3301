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

// Specify the "crystal frequency" in Hz. This is necessary for __delay_ms(n) or __delay_us(n)
# define _XTAL_FREQ 1000000 
int main() 
{
    char sseg[10] = {0x81, 0xCF, 0x92, 0x86, 0xCC, 0xA4, 0xA0, 0x8F, 0x80, 0x84};
    
    // Turn off ADC
    ADCON1 = 0xff;
    
    // PORTA is output (connected to 7segment display)
    TRISA = 0x00;
    
    int counter1 = 0;
    while (1)
    {
        
        PORTA = sseg[counter1 & 0x0F];
        __delay_ms(1000); // request a delay in milliseconds 
        //__delay_us(1000000); // request a delay in microseconds 
        counter1 = (counter1 + 1) % 10;
    }
    return (EXIT_SUCCESS);
}

