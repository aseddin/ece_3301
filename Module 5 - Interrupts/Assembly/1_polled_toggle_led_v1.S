config OSC = INTIO2
config BOR = OFF        ; Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
config STVREN = OFF     ; Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
config WDT = OFF        ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
config MCLRE = ON       ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
#include <xc.inc>
	goto main	
	
	; Toggle the LED connected to RC4 using a switch connected to RB0 (INT0)
	; This program is buggy, to fix we need to store the status of the switch
	
psect code
main: 

    ; set the I/O port directions
    setf    ADCON1, a   ; AN inputs are now digital inputs
    bcf	    TRISC, 4, a ; RC4 is output (connected to LED)
    bsf	    TRISB, 0, a ; RB0 is input (connected to switch)
	
    ; poll the switch and toggle LED when pressed (or cleared)
p:  btfss   PORTB, 0, a
    call    toggle
    bra	    p
;--------------------------------------------------------------------------
    ; SUBROUTINES
toggle:
    btg	    PORTC, 4, a
    return
	
end