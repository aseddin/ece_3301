config OSC = INTIO2
config BOR = OFF        ; Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
config STVREN = OFF     ; Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
config WDT = OFF        ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
config MCLRE = ON       ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
#include <xc.inc>
	goto start	
	
	; If 2 switches match, turn on LED
	psect code

start:	
	setf	ADCON1, a   ; Turn off ADC inputs
	clrf	TRISC, a    ; PORTC is output
	setf	TRISD, a    ; PORTD is input
infloop:
	movf	PORTD, w, a
	andlw	11000000B ; keep the values of bits 6 and 7
	bz	ledon	    ; if bits 6 and 7 are both low, turn led on
	sublw	11000000B
	bz	ledon	    ; if bits 6 and 7 are both high, turn led on
	bsf	PORTC, 7, a ; turn off led (cathode connected to port)
	bra	infloop
ledon:	bcf	PORTC, 7, a ; turn on led (cathode connected to port)
	bra	infloop
		
end