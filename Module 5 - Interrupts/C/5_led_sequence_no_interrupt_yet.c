/* 
 * File:   newmain.c
 * Author: Anas Salah Eddin
 *
 * Created on June 29, 2020, 3:19 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include <stdint.h>
/*
 * 	; Toggle the LEDs connected to RC0 to RC3 sequentially with some slow delay
	; Use interrupt to toggle the other led connected to RC4
 */

# define _XTAL_FREQ 1000000 
# define LED0   PORTCbits.RC0
# define LED1   PORTCbits.RC1
# define LED2   PORTCbits.RC2
# define LED3   PORTCbits.RC3
# define TLED   PORTCbits.RC4

int main() 
{
    
    // All AN inputs are digital
    ADCON1 = 0x0f;
    
    // PORTC is output (connected to all LEDs)
    TRISC = 0x00;
    
    // RB0 is input (connected to SW0)
    TRISB = 0xff;
    
    // Initialize all LEDs to off
    PORTC = 0xFF;
    
    
    while (1)
    {
	// Try to use polled I/O to implement the functionality of the toggle switch
        LED0 = 0;
        __delay_ms(500);
        LED0 = 1;
        __delay_ms(500);
        
        LED1 = 0;
        __delay_ms(500);
        LED1 = 1;
        __delay_ms(500);

        LED2 = 0;
        __delay_ms(500);
        LED2 = 1;
        __delay_ms(500);

        LED3 = 0;
        __delay_ms(500);
        LED3 = 1;
        __delay_ms(500);        
        
    }
    return (EXIT_SUCCESS);
}

