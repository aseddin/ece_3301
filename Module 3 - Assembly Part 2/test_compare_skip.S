	goto start	
	
	psect code
	; Test if a number at 0x20 is odd or even
start:	movlw	10110011B ; dummy number to be tested
	movwf	0x20, a
	clrf	WREG, a
	
	; Method 1 using logic operations and masks
	movlw	00000001B
	andwf	0x20, w, a; you have tor lose the data in WREG (chosen) or 0x20
	bnz	odd	; since the lsb of 0x20 is 1 it is odd
	
	; Method 2 using bit test
	; no need change wreg
	btfsc	0x20, 0, a; if bit 0 is clear (==even) skip the next line
			  ; this can also be done with btfss to test for odd
	bra	odd
	bra	even
    
even:	movlw 10 ; instruction implemented when even
	bra stop
odd:	movlw 5 ; instruction implemented when odd
	bra stop
	nop
	
stop:	bra stop
;-----------------------------------------------------------------------------
	goto start	
	
	psect code
	; Fill first 100 location with sequential data 
	; copy original from branch examples
	; Pause and try to do it on your own before watching the solution
	; Use DECFSZ or DECFSNZ
	; Then use CPFSEQ
	
	; --------------USING DECFSZf---------------------------
COUNTER	EQU 0x70    ;location to store counter value in access RAM	
I	EQU 0x71    ;location to store address index
start:	movlw	100
	movwf	COUNTER, a ; COUNTER = 100
	clrf	I, a	; I = 0
	lfsr	0, 0x000 ; load FSR0 with the first address 0x00
loop:	movff	I, POSTINC0 ; move the value of I into INDF0 then increase FSR0
	incf 	I, f, a
	;--------REPLACED THESE-------
	;decf	COUNTER, f, a
	;bnz	loop	; if the counter is not 0 repeat
	;-----------------------------
	decfsz	COUNTER, f, a
	bra	loop	; this will be implemented as long as COUNTER is not 0
			; bra will be skipped when COUNTER is 0
			
stop: BRA	stop	; DONE!
;-----------------------------------------------------------------------------
	goto start	
	
	psect code
	; Fill first 100 location with sequential data 
	; copy original from branch examples
	; Pause and try to do it on your own before watching the solution
	; Use DECFSZ or DECFSNZ
	; Then use CPFSEQ
	
	; --------------USING DCFSNZ---------------------------
COUNTER	EQU 0x70    ;location to store counter value in access RAM	
I	EQU 0x71    ;location to store address index
start:	movlw	100
	movwf	COUNTER, a ; COUNTER = 100
	clrf	I, a	; I = 0
	lfsr	0, 0x000 ; load FSR0 with the first address 0x00
loop:	movff	I, POSTINC0 ; move the value of I into INDF0 then increase FSR0
	incf 	I, f, a
	;--------REPLACED THESE-------
	;decf	COUNTER, f, a
	;bnz	loop	; if the counter is not 0 repeat
	;-----------------------------
	dcfsnz	COUNTER, f, a
	bra	stop	; when counter == 0, this will not be skipped indicating the end
	bra	loop	; this will be implemented as long as COUNTER is not 0
			
stop: BRA	stop	; DONE!
;-----------------------------------------------------------------------------
	goto start	
	
	psect code
	; Fill first 100 location with sequential data 
	; copy original from branch examples
	; Pause and try to do it on your own before watching the solution
	; Use DECFSZ or DECFSNZ
	; Then use CPFSEQ
	
	; --------------USING CPFSEQ---------------------------
	; no need to use counter anymore :)
	
;COUNTER	EQU 0x70    ;location to store counter value in access RAM	
I	EQU 0x71    ;location to store address index
start:	movlw	100
	;movwf	COUNTER, a ; COUNTER = 100
	clrf	I, a	; I = 0
	lfsr	0, 0x000 ; load FSR0 with the first address 0x00
loop:	movff	I, POSTINC0 ; move the value of I into INDF0 then increase FSR0
	incf 	I, f, a
	;--------REPLACED THESE-------
	;decf	COUNTER, f, a
	;bnz	loop	; if the counter is not 0 repeat
	;-----------------------------
	CPFSEQ	I, a
	bra	loop	; This line will not be skipped untill I = [WREG] = 100
			
stop: BRA	stop	; DONE!

;-----------------------------------------------------------------------------
	goto start	
	
	psect code
	; Count how many numbers are above 31 
	; in the first 100 locations in data memory

COUNTER	EQU	0x70 
TALLY	EQU	0x75 ; will contain the tally of the numbers above 31
start:	movlw	100
	movwf	COUNTER, f, a ; COUNTER = 100
	movlw	31  ; WREG = 31, the number to be compared 
	clrf	TALLY, a    ; TALLY = 0 
	lfsr	0, 0x00	;FSR0 points to the first location in the mem array
loop:	cpfslt	POSTINC0, a
	incf	TALLY, f, a ; will only be implemented if INDF0 > WREG = 31
	decfsz	COUNTER, f, a
	bra	loop	; will be skipped after 100 loops
	
stop:	bra	stop	; DONE!