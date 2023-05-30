/* 
 * File:   newmain.c
 * Author: Anas Salah Eddin
 *
 * Use ccp2 (compare mode) to toggle the CCP2 pin in 308 ms intervals
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"


#define LED PORTCbits.RC1 // LED is not yet connected to CCP2

void __interrupt() ccp_interrupt();

int main() 
{

        
    // Setup Timer 1
    T1CONbits.RD16 = 0; // Enable read/write in 8-bit 
    T1CONbits.T1RUN = 0; // timer1 one is NOT driven by its internal oscillator
    T1CONbits.T1CKPS = 3; // 1:8 prescaler value (slowest)
    T1CONbits.T1OSCEN = 0; // Timer1 oscillator is shut off
    T1CONbits.TMR1CS = 0; // use internal instruction clock
    T1CONbits.TMR1ON = 1; // Timer 1 is on
    TMR1 = 0; // initial value of Timer1

    // Select The timer that will be used with the CCP module
//    T3CONbits.T3CCP1 = 0; //Timer 1 is the capture/compare clock source for  CCP1
    T3CONbits.T3CCP2 = 0; //Timer 1 is the capture/compare clock source for  CCP2
    
    // Setup CCP2 in compare mode (output)
    // Using the default value CCP2MX = RC1
    TRISCbits.RC1 = 0; // RC1 is output for CCP2    
    CCP2CONbits.CCP2M = 0b0010; // compare mode, toggle output on match
    
    
    // Final timer value == period register value for timer1
    // The value of CCPR2 is computed in a similar way PR2 is computed for Timer2
    // Refer to the Timers slides for more info

    // Generate a delay of 308 ms (8 prescaler, 1/4 MHz instruction freq)
    CCPR2 = 9624; 
    
    // Setup CCP2 interrupt
    PIR2bits.CCP2IF = 0;
    IPR2bits.CCP2IP = 1; // high priority
    PIE2bits.CCP2IE = 1; // Enable interrupt
    RCONbits.IPEN = 0; // disable interrupt priorities
    INTCONbits.PEIE = 1; // enable all peripheral interrupts
    INTCONbits.GIE = 1; // enable all unmasked interrupts
    
    LED = 1; // initial led value
   
    
    while(1)
    {
        ;
    }
    
    return 0;

}

void __interrupt() ccp_interrupt()
{
    
    if (PIE2bits.CCP2IE && PIR2bits.CCP2IF)
    {
        PIR2bits.CCP2IF = 0;
        TMR1 = 0; // reset timer1
        // LED is not toggled explictly. the compare mode is toggling it
        
    }
}
