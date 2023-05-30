	goto start	
	
	; Example of using TBLRD*, TBLRD*+, TBLRD*-, TBLRD+*
	
	psect data  ; no need to use ORG anymore,
		    ; this line tells the assembler to store data
		    ; in the appropriate sector
		    
	; DB and DW are assembler directives not instructions
	; The following 2 lines are equivalent
	DB  11001001B, 00110101B, 00010001B, 11010010B
	DW  0x35C9, 0xD211
	
	psect code
start:	nop
;---------------------------------------------------------------------
	goto start	
	
	; Example of using TBLRD*, TBLRD*+, TBLRD*-, TBLRD+*
	
	psect data  ; no need to use ORG anymore,
		    ; this line tells the assembler to store data
		    ; in the appropriate sector
		    
	; DB and DW are assembler directives not instructions
	; The following 2 lines are equivalent
lookup:	DB  11001001B, 00110101B, 00010001B, 11010010B
	;DW  0x35C9, 0xD211
	
	
	psect code
start:	; load TBLPTR with the address of lookup
	movlw	low lookup
	movwf	TBLPTRL, f, a
	movlw	high lookup
	movwf	TBLPTRH, f, a
	movlw	low highword lookup; in older assembler this was `upper lookup`
	movwf	TBLPTRU, f, a
	
	tblrd*	; read program memory and place it in TABLAT
	;tblrd*+; read and advance the table pointer
	movf	TABLAT, w, a ; move content of TABLAT to WREG
stop:	bra	stop
;---------------------------------------------------------------------
	goto start	
	
	; 7 Segment translator
	
	psect data  
lookup:	DB  0x81, 0xCF, 0x92, 0x86, 0xCC, 0xA4, 0xA0, 0x8F, 0x80, 0x84	
	
	psect code
SSEG	EQU 0x41    ; 7segment pattern table starting address in data memory
I	EQU 0x70    ; used as a counter index
start:	; load TBLPTR with the address of lookup
	movlw	low lookup
	movwf	TBLPTRL, f, a
	movlw	high lookup
	movwf	TBLPTRH, f, a
	movlw	low highword lookup
	movwf	TBLPTRU, f, a
	
	; move table from program to data memory
	lfsr	0, SSEG ; starting address in data memory
	movlw	10
	movwf	I, f, a ; initialize counter with 10
loop:	TBLRD*+    ; read 1B from program memory and advance TBLPTR by 1
	movff	TABLAT, POSTINC0 ;copy TABLAT into INDF0 them move FSR0 pointer forward
	decf	I, f, a;
	bnz	loop
	
	; translate the content of WREG from BCD into 7 seg
	movlw	4
	lfsr	0, SSEG; move fsr0 pointer back to origin
	movf	PLUSW0, w, a

stop:	bra	stop
