/* 
 * File:   newmain.c
 * Author: Anas Salah Eddin
 *
 * Created on June 29, 2020, 3:19 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config.h"
/*
 * 	Show the usage of KBIx level triggered interrupt
 */

# define _XTAL_FREQ 1000000 
# define LED0   PORTCbits.RC0
# define LED1   PORTCbits.RC1
# define LED2   PORTCbits.RC2
# define LED3   PORTCbits.RC3
# define TLED   PORTCbits.RC4

void __interrupt(high_priority) toggleLed(void);

int main() 
{
    
    // All AN inputs are digital
    ADCON1 = 0x0f;
    
    // PORTC is output (connected to all LEDs)
    TRISC = 0x00;
    
    // PORTB has several inputs as interrupts
    TRISB = 0xff;
    
    
    // Initialize all LEDs to off
    PORTC = 0xFF;
    
    // Setup all inerrupts
    INTCONbits.INT0E = 1; // Enable INT0
    INTCONbits.INT0IF = 0; // reset INT0 flag
    INTCON2bits.INTEDG0 = 0; // falling edge
    
    INTCONbits.RBIE = 1;    // Turn on KB interrupts
    INTCONbits.RBIF = 0;    // Turn off all flags
    
    // Setup interrupt priorities
    RCONbits.IPEN = 1; // enable priority
    INTCONbits.GIEH = 1; // enable all high priority
    INTCONbits.GIEL = 0; // enable all low priority
    INTCON2bits.RBIP = 1; // set it to high priority so it shares it with IND0
    while (1)
    {
        // There is a better way to write this, but it is written this way for simplicity
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

void __interrupt(high_priority) toggleLed(void)
{
    // test which interrupt called this Interrupt Service Routine
    
    // INT0
    if (INTCONbits.INT0IE && INTCONbits.INT0IF)
    {
        // Turn off the interrupt flag to avoid recursive interrupt calls
        INTCONbits.INT0IF = 0;
        
        // Do what needs to be done
        TLED = ~TLED;

    }
    else if (INTCONbits.RBIE && INTCONbits.RBIF)
    {
        // The following code is to fix a strange bug in RB Port CHange Interrupt where it is always triggered 
        // https://www.microchip.com/forums/m294169.aspx
        
        unsigned char LastKnownPORTB;
        LastKnownPORTB = PORTB;
        INTCONbits.RBIF = 0;
        LastKnownPORTB = PORTB;
        
        
        for(int i = 0; i < 10; i++)
        {
            TLED = ~TLED;
            __delay_ms(100);
        }
    }
    return;

}

