config OSC = INTIO2
config BOR = OFF        ; Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
config STVREN = OFF     ; Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
config WDT = OFF        ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
config MCLRE = ON       ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
#include <xc.inc>
	goto main	
	
	; Toggle the LED connected to RC4 using a switch connected to RB0 (INT0)
	; This program fixes the bug by toggling on a falling edge press and debouncing
	
psect code
PREV_STATUS equ 0x50
main: 

    ; set the I/O port directions
    setf    ADCON1, a   ; AN inputs are now digital inputs
    bcf	    TRISC, 4, a ; RC4 is output (connected to LED)
    bsf	    TRISB, 0, a ; RB0 is input (connected to switch)
	
    ; poll the switch and toggle LED when pressed (or cleared)
    setf    PREV_STATUS; start with  the switch not pressed
loop:
    btfsc   PORTB, 0, a	 
    bra	    loop	    ; button is not pressed
    btfsc   PREV_STATUS, 0, a ; button is now pressed, check the previous status
    call    toggle	    ; previous sw status is not pressed, now it is pressed, toggle LED
    call    delay2550us	    ; debounce time 2550 us to reduce noise
    movff   PORTB, PREV_STATUS
    bra	    loop
    
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
end