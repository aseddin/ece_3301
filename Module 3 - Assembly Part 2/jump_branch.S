    
	; goto examples
	goto	0x0004	;this instruction changes the program counter to 0x4
	
here:	goto	here 
    
	; the previous goto will not work properly
	; the assembler doesn't know that goto takes 2 words
	; you need to put these instruction in an appropriate psect
	

	;---------------------------------------------------------------
	psect code
	goto	0x0004	; this instruction moves the program counter to 0x4
here:	goto	here	; if we are inside psect code, this jump will work
 
	; The starting point is always 0x0000 because it is the reset vector
	; check figure 5-1 in page 53 of the datasheet
	
	;---------------------------------------------------------------

	goto start	; after a reset the program counter will be here
	
	psect code
start:			; This is the start of the main program
			; You can also use main: instead of start:
	goto	start		
 	;---------------------------------------------------------------
	goto start	; after a reset the program counter will be here
	
	psect code
	; BRA examples
start:	nop
	nop
	BRA $-4	;
	;---------------------------------------------------------------
	goto start	; after a reset the program counter will be here
	
	psect code
	; Conditional Branching Examples (bz, bnz)
start:	movlw	10
	sublw	13  ; subtract WREG from this literal
	bnz	cnd ; change this to bnz and see what happens
fin:	bra	fin
	nop
	nop
cnd:	nop
	;---------------------------------------------------------------
	goto start	; after a reset the program counter will be here
	
	psect code
	; Conditional Branching Examples (bov, bnov)
start:	movlw	100
	sublw	128  ; this will result in OV
	bov	cnd ; change this to bnov and see what happens
fin:	bra	fin
	nop
	nop
cnd:	nop
	;---------------------------------------------------------------
	goto start	
	
	psect code
	; Fill first 100 location with sequential data
COUNTER	EQU 0x70    ;location to store counter value in access RAM	
I	EQU 0x71    ;location to store address index
start:	movlw	100
	movwf	COUNTER, a ; COUNTER = 100
	clrf	I, a	; I = 0
	lfsr	0, 0x000 ; load FSR0 with the first address 0x00
loop:	movff	I, POSTINC0 ; move the value of I into INDF0 then increase FSR0
	incf 	I, f, a
	decf	COUNTER, f, a
	bnz	loop	; if the counter is not 0 repeat
stop: BRA	stop	; DONE!
	;---------------------------------------------------------------
 
	goto start	
	
	psect code
	; How much time does it take to go from start to stop? (USE STOPWATCH HERE!)
start:	movlw	100
	nop
stop:	sleep
	;---------------------------------------------------------------
	goto start	
	
	psect code
	; How much time does it take to go from start to stop? (USE STOPWATCH HERE!)
COUNT	EQU 2
start:	movlw	COUNT
loop:	decf	WREG, w, a
	bnz	loop
stop:	sleep
 
	;---------------------------------------------------------------
