config OSC = INTIO2
config BOR = OFF        ; Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
config STVREN = OFF     ; Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
config WDT = OFF        ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
config MCLRE = ON       ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
#include <xc.inc>
	
	goto start	
	
	; One LED one switch
	psect code


start:	
	setf	ADCON1, a   ; Turn off ADC inputs
	clrf	TRISD, a    ; PORTD is output
	setf	TRISC, b    ; PORTC is input
infloop:
	movff	PORTC, PORTD
	bra	infloop
;stop:	bra	stop	    ; if you included this jump instead of the infinite loop, the led won't update
end