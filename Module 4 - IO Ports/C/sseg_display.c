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
    char sseg[10] = {0x81, 0xCF, 0x92, 0x86, 0xCC, 0xA4, 0xA0, 0x8F, 0x80, 0x84};
    
    // Turn off ADC
    ADCON1 = 0xff;
    
    // PORTA is output (connected to 7segment display)
    TRISA = 0x00;
    
    // PORTB is input (conntected to switches)
    TRISB = 0xff;
    
    while (1)
    {
        PORTA = sseg[PORTB & 0x0F];
    }
    return (EXIT_SUCCESS);
}

