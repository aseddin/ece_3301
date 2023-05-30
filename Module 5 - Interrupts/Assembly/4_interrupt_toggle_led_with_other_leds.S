config OSC = INTIO2
config BOR = OFF        ; Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
config STVREN = OFF     ; Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
config WDT = OFF        ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
config MCLRE = ON       ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
#include <xc.inc>
	goto main	
	
	; Toggle the LEDs connected to RC0 to RC3 sequentially with some slow delay
	; Use interrupt to toggle the other led connected to RC4

psect intCodeHi, class = CODE, reloc = 2
    bcf	    INTCON, 1, a
    call    toggle
    ;call    delay2550us
    retfie  0
	
psect code
PREV_STATUS equ 0x50
main: 

    ; set the I/O port directions
    setf    ADCON1, a   ; AN inputs are now digital inputs
    clrf    TRISC, a	; RC0 to RC4 are outputs (connected to LEDs)
    bsf	    TRISB, 0, a ; RB0 is input (connected to switch)
	
    ; initial output value
    setf    PORTC, a	; Start with all LEDs off
    
    ; Setup interrupts
    movlw   10010000B	
    movwf   INTCON, f, a    ; Enable global interrupt, enable INT0, reset INT0 Flag
    bcf	    INTCON2, 6, a   ; Interrupt on falling edge (default)
    ;bsf	    INTCON2, 6, a   ; Interrupt on rising edge 
    
    setf    PREV_STATUS	; start with  the switch not pressed
loop:
    ; 4 LED sequenced toggle
    bcf	    PORTC, 0, a ; Turn on RC0
    call    delay500ms
    bsf	    PORTC, 0, a ; Turn off RC0
    call    delay500ms

    bcf	    PORTC, 1, a ; Turn on RC1
    call    delay500ms
    bsf	    PORTC, 1, a ; Turn off RC1
    call    delay500ms
    
    bcf	    PORTC, 2, a ; Turn on RC2
    call    delay500ms
    bsf	    PORTC, 2, a ; Turn off RC2
    call    delay500ms
    
    bcf	    PORTC, 3, a ; Turn on RC3
    call    delay500ms
    bsf	    PORTC, 3, a ; Turn off RC3
    call    delay500ms
    
    
;--------------------------------------------------------------------------
    ; SUBROUTINES
toggle:
    btg	    PORTC, 4, a
    return

delay2550us:			    ; 2550 us delay
	movlw	255
l1:	decf	WREG, w, a
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	bnz	l1
	return 1

delay500ms:			    
	movlw	100		    
	movwf	0x10, a
l2:	call	delay2550us
	decf	0x10, f, a
	bnz	l2
	return 1
end