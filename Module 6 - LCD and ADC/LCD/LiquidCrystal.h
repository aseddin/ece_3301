/* 
 * File:   LiquidCrystal.h
 * Author: Anas Salah Eddin
 *
 * Created on July 8, 2020, 4:03 PM
 * 
 * This library/Driver is inspired by Arduino's LiquidCrystal library
 * It provides useful functions to setup and drive generic HD44780 compatible LCDs
 */

#ifndef LIQUIDCRYSTAL_H
#define	LIQUIDCRYSTAL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdio.h>
    
# define _XTAL_FREQ 1000000 // 100 MHz clock

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

    
    
    unsigned char _displaycontrol;
    unsigned char _displayfunction;
    unsigned char _displaymode;
    unsigned char _numlines;
    unsigned char _rowOffsets[4];

    // Generic PORT data type
    typedef union {
        struct {
            unsigned _data0 :1;
            unsigned _data1 :1;
            unsigned _data2 :1;
            unsigned _data3 :1;
            unsigned _data4 :1;
            unsigned _data5 :1;
            unsigned _data6 :1;
            unsigned _data7 :1;
        };
        
        unsigned char _data;
        
        struct {
            unsigned _rs        :1;
            unsigned _rw        :1;
            unsigned _enable    :1;
            unsigned            :5;
        };
    } PORTx_t;
    
    volatile PORTx_t *dataPORT, *signalPORT;
            
    
    
/*
     * Pin setup
     * -------
     * Maps the PIC18F4321 pins to the LCD pins
     * This function must be called before any other LCD functions (including begin)
     * 
     * The mapping assumes 8 bit data (dp) are all on a single pic PORT 
     * and arranged in order.
     * Example: 
     * Assuming PORTA is connected to the 8 bit LCD data pins
     * dp._data0 = PORTAbits.RA0 
     * dp._data1 = PORTAbits.RA1
     * .
     * .
     * .
     * dp._data7 = PORTAbits.RA7 
     * 
     * The whole 8 bit data port can also be accessed by dp._data
     * 
     * The 3 signal bits (sp) are the 3 lsb of a single pic PORT 
     * Example:
     * Assuming PORTD is connected to the 3 bit LCD signal pins 
     * ds._rs = PORTDbits.RD0
     * ds._rw = PORTDbits.RD1
     * ds._enable = PORTDbits.RD2
     * 
     * *dp: data port pointer to a data port (for example &PORTA)
     * 
     * *sp: signal port pointer to a signal port (for example &PORTD)
     */
    void pin_setup(volatile PORTx_t *dp, volatile PORTx_t *sp);
    
    /*
     * begin
     * ------
     * Initializes the LCD and specifies the dimensions (width and hight) of the display
     * This function must be called after pin_setup and before any other LCD function
     * 
     * cols: Number of columns (mine is 16)
     * 
     * line: Number of lines (mine is 2)
     * 
     * dotsize: can be either LCD_5x8DOTS or LCD_5x10DOTS (mine is 5x8)
     */
    void begin(unsigned char cols, unsigned char lines, unsigned char dotsize);
    
    /* write
     * -------
     * Write a character to the LCD
     */
    void write(unsigned char chr);

    
    /* print
     * ------
     * Print a string
     * 
     */
    void print(unsigned char *chr);

    /* displayON
     * ------------
     * Turn on the display 
     * 
     */
    void displayON();
    
    /* display
     * -----------
     * The same as displayON
     * This function is included here to match that found in the 
     * Arduino LiquidCrystal library
     * 
     */
    void display();
    
    
     /* displayOFF
     * ------------
     * Turn off the display 
     * 
     */
    void displayOFF();
    
    /* noDisplay
     * -----------
     * The same as displayOFF
     * This function is included here to match that found in the 
     * Arduino LiquidCrystal library
     * 
     */
    void noDisplay();
    
    /* clear
     * -------
     * Clears the screen and return cursor to home
     */
    void clear();
    
    /* home
     * --------
     * Return cursor position to home (upper left for left to right languages)
     * Doesn't clear the screen
     * 
     */
    void home();
    
    /*
     * setRowOffsets
     * ---------------
     * Split the 80x8 DDRAM memory into 4 rows and store the row offsets
     * 
     * Pages 10, 11 of the datasheet show some figures
     * A rows is not the same as a line, a row is contained within a line
     * For example, in a 16x2 LCD, you have 2 lines, each line can contain
     * two rows each is 16 characters.
     * 
     * row0: starting address of first row in the first line
     * row1: starting address of first row in the second line
     * row2: starting address of second row in the first line
     * row3: starting address of second row in the second line

     */
    void setRowOffsets(unsigned char row0, unsigned char row1, unsigned char row2, unsigned char row3);
    
    /*
     * setCursor
     * ----------
     * set cursor location
     * 
     * col: column number (in my case 0 to 31), the col after 15 are not visible (right of screen)
     * row: row number (in my case 0 to 3)
     */
    void setCursor(unsigned char col, unsigned row);
    
    /*cursor
     *----------
     * Display the cursor as an underline
     */
    void cursor();
    
    /*noCursor
     *----------
     * Display the cursor as an underline
     */
    void noCursor();
    
    /* blink
     *----------
     * blink on the blinking cursor
     */
    void blink();
    
    /*noBlink
     *----------
     * turn off the blinking cursor
     */
    void noBlink();
    
    /* scrollDisplayLeft
     * -------------------
     * Scrolls the contents of the display (text and cursor) one space to the left)
     */
    void scrollDisplayLeft();
    
    /* scrollDisplayRight
     * Scrolls the contents of the display (text and cursor) one space to the right
     */
    void scrollDisplayRight();

    /* leftToRight
     * -------------
     * Set the direction for text written to the LCD to left-to-right, 
     * the default. This means that subsequent characters written to the 
     * display will go from left to right, but does not affect previously-output 
     * text.
     */
    void leftToRight();

    /* rightToLeft
     * -------------
     * Set the direction for text written to the LCD to right-to-left 
     * (the default is left-to-right). This means that subsequent characters
     *  written to the display will go from right to left, but does not affect
     *  previously-output text.
     */
    void rightToLeft() ;

    /* autoscroll
     * ------------------
     * Turns on automatic scrolling of the LCD
     * 
     */
    void autoscroll(void);

    /* noAutoscroll
     * ------------------
     * Turns off automatic scrolling of the LCD
     */
    void noAutoscroll();
    
    //------------------------------------------------------------------
    //                    Lower level functions
    //------------------------------------------------------------------
    
    /*
     * send
     * -------------
     * send Data or command to the LCD
     * the function will take care of setting the correct values for rs and rw
     * 
     * value: the 8 bits data value to be sent to the LCD driver
     * mode: 0 = command, 1 = data
     */
    void send(unsigned char value, unsigned char mode);
    
    /*
     * sendData
     * -------------
     * send Data to the LCD
     * The function will take care of setting the correct values for rs and rw
     * 
     * value: the 8 bits data value to be sent to the LCD driver
     * 
     */
    void sendData(unsigned char value);
    
     /*
     * sendCommand
     * -------------
     * send Data to the LCD
     * The function will take care of setting the correct values for rs and rw
     * 
     * value: the 8 bits data value to be sent to the LCD driver
     * 
     */
    void sendCommand(unsigned char value);
    
    /* pulseEnable
     * ----------------
     * create a short tick (1 us) on the enable pin
     * 
     * This function is used to issue an enable tick whenever you need to write
     * or read the value on the data pins
     */
    void pulseEnable(void);
    
    /*
     * write8bits
     * --------------
     * Place the 8 bits of value on the corresponding data pins
     * This function assumes an 8 bit mode
     * 
     */
    void write8bits(unsigned char value);
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* LIQUIDCRYSTAL_H */


