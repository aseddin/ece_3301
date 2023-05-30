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
 * 	; Toggle the LEDs connected to RC0 to RC3 sequentially with some slow delay
	; Use interrupt (INT0) to toggle the other led connected to RC4
 *  ; Use interrupt (INT1) to 
 */

# define _XTAL_FREQ 1000000 
# define LED0   PORTCbits.RC0
# define LED1   PORTCbits.RC1
# define LED2   PORTCbits.RC2
# define LED3   PORTCbits.RC3
# define TLED   PORTCbits.RC4

void __interrupt(high_priority) toggleLed(void);
void __interrupt(low_priority) flashLed(void);

int main() 
{
    
    // All AN inputs are digital
    ADCON1 = 0x0f;
    
    // PORTC is output (connected to all LEDs)
    TRISC = 0x00;
    
    // RB0 (INT0) and RB1 (INT1) are inputs
    TRISB = 0xff;
    
    
    // Initialize all LEDs to off
    PORTC = 0xFF;
    
    // Setup all inerrupts
    INTCONbits.GIE = 1; // Globabl interrupt enable
    INTCONbits.INT0E = 1; // Enable INT0
    INTCONbits.INT0IF = 0; // reset INT0 flag
    INTCON2bits.INTEDG0 = 0; // falling edge
    // INTCON2bits.INTEDG0 = 1; // rising edge
    INTCON3bits.INT1IE = 1; // Enable INT1
    INTCON3bits.INT1IF = 0; // reset INT1 flag
    
    // Setup interrupt priorities
    RCONbits.IPEN = 1; // enable priority
    INTCONbits.GIEH = 1; // enable all high priority
    INTCONbits.GIEL = 1; // enable all low priority
    INTCON3bits.INT1IP = 0; // Set INT1 to low priority 
    
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
        for(int i = 0; i < 100; i++)
        {
            TLED = ~TLED;
            __delay_ms(200);
        }
    }
    return;

}

void __interrupt(low_priority) flashLed(void)
{
     // test which interrupt called this Interrupt Service Routine
    
    // INT1 is in INTCON3
    if (INTCON3bits.INT1IE && INTCON3bits.INT1IF)
    {
        // Turn off the interrupt flag to avoid recursive interrupt calls
        INTCON3bits.INT1IF = 0;
        
        // Do what needs to be done
        TLED = ~TLED;
        
    }
    return;

}