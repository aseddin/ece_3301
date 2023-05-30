/* 
 * File:   newmain.c
 * Author: Anas Salah Eddin
 *
 * Compute and display the period of a square wave placed on CCP2
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "LiquidCrystal.h"

# define _XTAL_FREQ 1000000

void __interrupt() ccp_interrupt();

int main() 
{
    
    // Configure LCD Pins
    // Data pins connected to PORTB
    TRISB = 0x00; 
    
    // RS = RD0
    // RW = RD1
    // E  = RD2
    TRISD = 0x00;
    
    // connect the LCD pins to the appropriate PORT pins
    pin_setup(&PORTB, &PORTD);
    
    // initialize the LCD to be 16x2 (this is what I have, yours might be different)
    begin(16, 2, LCD_5x8DOTS);
    
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
    
    // Setup CCP2 in capture mode
    // Using the default value CCP2MX = RC1, the switch is connected to RC1/CCP2
    TRISCbits.RC1 = 1; // RC1 is input for CCP2    
    CCP2CONbits.CCP2M = 0b0101; // capture every rising edge

    // Setup CCP2 interrupt
    PIR2bits.CCP2IF = 0;
    IPR2bits.CCP2IP = 1; // high priority
    PIE2bits.CCP2IE = 1; // Enable interrupt
    RCONbits.IPEN = 0; // disable interrupt priorities
    INTCONbits.PEIE = 1; // enable all peripheral interrupts
    INTCONbits.GIE = 1; // enable all unmasked interrupts
    
    // strings for display
    char s_CCPR2[80];
    while(1)
    {
        home();
        

        print("Period: ");
        sprintf(s_CCPR2, "%u", CCPR2);
        print(s_CCPR2);
        print(" Cycle    ");
        
        setCursor(0, 1);
        
        print("Period: ");
        sprintf(s_CCPR2, "%u",  CCPR2 *4 * 8 );
        print(s_CCPR2);
        print(" uS    ");
    }
    
    return 0;

}

void __interrupt() ccp_interrupt()
{
    
    if (PIE2bits.CCP2IE && PIR2bits.CCP2IF)
    {
        PIR2bits.CCP2IF = 0;
//        TMR1 = 0; // zero out timer 1 register
        
        // it is necessary to shift by 2 because of the time needed 
        // for the if statement and calling the ISR
        TMR1 = 2; 

    }
}
