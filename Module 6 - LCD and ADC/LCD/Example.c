#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "LiquidCrystal.h"

# define _XTAL_FREQ 1000000 

int main() 
{
    
    // ALL ANx input are digital
    ADCON1 = 0x0f;
    
    // Data pins connected to PORTA
    TRISA = 0x00; 
    
    // RS = RD0
    // RW = RD1
    // E  = RD2
    TRISD = 0x00;
    
    // connect the LCD pins to the appropriate PORT pins
    pin_setup(&PORTA, &PORTD);
    
    // initialize the LCD to be 16x2 (this is what I have, yours might be different)
    begin(16, 2, LCD_5x8DOTS);
    
    while (1)
    {
        clear();
        // Test all the display functions

        // The canonical Hello World!
        print("Hello World!");

        // display a single character
        write('*');

        // Use a code from Table 4 (I have the one with ROM Code A00 English + Japanese)
        write(0xDF); // degree symbol
        write(0xC8); // Some cool Japanese character that I cannot read

        // Cursor function
        cursor(); // turn on cursor
        //noCursor(); // turn off cursor
        blink(); // blinking on
        //noBlink(); // blinking off
        setCursor(8, 1); // move cursor to middle of second row
        print("@");
        home(); // move the cusor home (no deletion)

        // Display vs Clear
        displayOFF(); // turn off the display including cursor, light is still on
        displayON(); // turn on the display

        // blink blink 
        for (int j = 0; j < 5; j++)
        {
            displayOFF();
            __delay_ms(200);
            displayON();
            __delay_ms(200);
        }

        __delay_ms(1000);
        
        clear(); // delete everything

        // Let's see the effect of display shift (when the text is longer than the # of cols)
        print("This sentence is too long to fit on a single line, let's see where will it end");
        __delay_ms(1000);
        
        for(int i = 0; i < 20; i++)
        {
            scrollDisplayLeft();
            __delay_ms(300);
        }
        


        __delay_ms(2000);
        
    }
    return 0;

}

