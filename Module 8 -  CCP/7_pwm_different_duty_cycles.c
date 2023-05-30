/* 
 * File:   newmain.c
 * Author: Anas Salah Eddin
 *
 * Simple PWM example with different duty cycles (manually computed and entered)
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"

#define LED PORTCbits.RC1

int main() 
{
    // PWM Frequency = 1 KHz
    // PWM Period = 1x10^-3 Second
    PR2 =  249;
    
    // PWM Duty Cycle (50%)
    CCPR2L = 0b1111101;
    CCP2CONbits.DC2B = 0b00;
    
    // PWM Duty Cycle (25%)
//    CCPR2L = 0b111110;
//    CCP2CONbits.DC2B = 0b10;
    
    // PWM Duty Cycle (0%)
//    CCPR2L = 0;
//    CCP2CONbits.DC2B = 0b00;
    
    // PWM Duty Cycle (100%)
//    CCPR2L = 0b11111010;
//    CCP2CONbits.DC2B = 0b00;    
    
    // setup timer 2
    // FOSC = 1 MHz
    T2CONbits.T2CKPS = 0b00; // Prescaler 1:1
    T2CONbits.TMR2ON = 1;
    

    // setup CCP2 in PWM mode
    TRISCbits.RC1 = 0;
    CCP2CONbits.CCP2M = 0b1100;
    
    // no need to use interrupts
    
    while(1)
    {
        ;
    }
    
    return 0;
}


