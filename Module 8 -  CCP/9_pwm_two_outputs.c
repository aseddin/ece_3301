/* 
 * File:   newmain.c
 * Author: Anas Salah Eddin
 *
 * Use the 2 ADC channels to control the duty cycle of 2 PWM signal
 * using CCP1 and CCP2
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"

#define LED PORTCbits.RC1

void __interrupt() ISR(void);

int main() 
{
    // PWM Frequency = 1 KHz
    // PWM Period = 1x10^-3 Second
    PR2 =  249;

    // setup timer 2
    // FOSC = 1 MHz
    T2CONbits.T2CKPS = 0b00; // Prescaler 1:1
    T2CONbits.TMR2ON = 1;
    

    // setup CCP1 in PWM mode
    TRISCbits.RC2 = 0;
    CCP1CONbits.CCP1M = 0b1100;
    
    // setup CCP2 in PWM mode
    TRISCbits.RC1 = 0;
    CCP2CONbits.CCP2M = 0b1100;
    
    // Setup the ADC
    // 1 - Configure the A/D Module

    // * Configure analog pins, voltage reference and digital I/O 
    ADCON1 = 0x0D;
    TRISAbits.RA0 = 1;
    TRISAbits.RA1 = 1;

    // * Select A/D acquisition time
    // * Select A/D conversion clock

    ADCON2bits.ADCS = 0; // FOSC/2
    ADCON2bits.ACQT = 1; // ACQT = 2 TAD
    ADCON2bits.ADFM = 0; // left justified
    
    // * Select A/D input channel
    ADCON0bits.CHS = 0; // Channel 0 (AN0)
    
    // * Turn on A/D module
    ADCON0bits.ADON = 1;
    
    // 2 - Configure A/D interrupt (if desired)
    // * Clear ADIF bit
    // * Set ADIE bit
    // * Select interrupt priority ADIP bit
    // * Set GIE bit
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;
    IPR1bits.ADIP = 1; 
    RCONbits.IPEN = 0; // disable priority levels
    INTCONbits.PEIE = 1; // enable peripheral interrupts
    INTCONbits.GIE = 1;

    // 3 - Wait the required acquisition time (if required)  

    while(1)
    {
        // 4 - Start conversion: Set GO/DONE(bar) bit
        ADCON0bits.GO = 1;


    }
    
    return 0;
}

void __interrupt() ISR(void)
{
    if (PIR1bits.ADIF && PIE1bits.ADIE)
    {
        // 5 Wait for A/D conversion to complete by either
        // * Polling for the GO/Done bit to be cleared
        // * Waiting for the A/D interrupt

        // 6 - Read A/D result registers (ADRESH:ADRESL); clear bit ADIF, if required

        // 7 - Go to Step 1 or Step 2 as required  
        PIR1bits.ADIF = 0;
        
        // PWM Duty Cycle
        
        
        if (ADCON0bits.CHS == 0) // channel AN0 (red LED)
        {
            CCPR2L = ADRESH;
            CCP2CONbits.DC2B = ((ADRESL >> 6) & 0x03);
            ADCON0bits.CHS = 1;
        }
        else if (ADCON0bits.CHS == 1) // channel AN1 (green LED))
        {
            CCPR1L = ADRESH;
            CCP1CONbits.DC1B = ((ADRESL >> 6) & 0x03);
            ADCON0bits.CHS = 0;
        }
    }
}

