#include <xc.inc>
	goto start	
	
	; Compute X^2 using a subroutine
	; Check what is happening  to the stak pointer and the TOS
	; In MPLAB X IDE, click Window, Target Memory Views, Hardware Stack
	psect code
X    equ    0x50
X2L  equ    0x51 ;X^2 low byte
X2H  equ    0x52 ;X^2 high byte
  
start:	movlw	5
	movwf	X, a
	clrf	WREG, a
	;call	sqr ; after this line 0x51 and 0x52 will have X^2, WREG will be changed
	call	sqr, 1; WREG will not have been changed

	
stop:	bra stop
    
sqr:	movf	X, w, a	; move X into WREG
	mulwf	X, a	; multiply X by itself to get X^2
	movff	PRODL, X2L
	movff	PRODH, X2H
	;return	; WREG would be changed upon return
	return 1; WREG will be restored to its original value before the call
		; because WREG was stored in the shadow register SWREG (also for SSTATUS and SBSR)
end
;---------------------------------------------------------------------------------------
#include <xc.inc>
	goto start	
	
	; Compute X^2 using a subroutine, call it 2 times
	; Check what is happening  to the stak pointer and the TOS
	; In MPLAB X IDE, click Window, Target Memory Views, Hardware Stack
	psect code
X    equ    0x50
X2L  equ    0x51 ;X^2 low byte
X2H  equ    0x52 ;X^2 high byte
  
start:	movlw	5
	movwf	X, a
	clrf	WREG, a
	;call	sqr ; after this line 0x51 and 0x52 will have X^2, WREG will be changed
	call	sqr, 1; WREG will not have been changed

	movlw	10 ; second number to be squared
	movwf	X, a
	clrf	WREG, a
	call	sqr, 1; X2L and X2H will be overwritten
	
stop:	bra stop
    
sqr:	movf	X, w, a	; move X into WREG
	mulwf	X, a	; multiply X by itself to get X^2
	movff	PRODL, X2L
	movff	PRODH, X2H
	;return	; WREG would be changed upon return
	return 1; WREG will be restored to its original value before the call
		; because WREG was stored in the shadow register SWREG (also for SSTATUS and SBSR)
end
;---------------------------------------------------------------------------------------
#include <xc.inc>
	goto start	
	
	; Compute the sum of squares
	; Use Memory Fill to fill addresses 0x50 to 0x55 (first try with 0, 1, 2, 3, 4, 5)
	psect code
N	equ    0x00
TBL	equ    0x50 ; starting point for table of numbers
YL	equ    0x60 ;Y low byte
YH	equ    0x61 ;Y high byte
X	equ    0x70 ;temp location for X
X2L	equ    0x71 ;temp location fo X^2 low byte
X2H	equ    0x72 ;temp location for X^2 high byte
	
start:	movlw	5 ; N numbers
	movwf	N, a
	
	clrf	YL, a	; clear Y
	clrf	YH, a
	bcf	STATUS, 0, a ; clear carry bit in status register
	
	lfsr	0, TBL	; FSR0 points to start of table

loop:	movff	POSTINC0, X
	call	sqr, 1
	call	sum16, 1	
	;decf	N, f, a ; This will change the carry!! We need a different decrement instruction
	;bnz	loop
	
	decfsz	N, f, a ; This way we don't change the carry
	bra	loop
	
stop:	bra stop
    
	; Compute the square of a number X
sqr:	movf	X, w, a	; move X into WREG
	mulwf	X, a	; multiply X by itself to get X^2
	movff	PRODL, X2L
	movff	PRODH, X2H
	return 1; WREG will be restored to its original value before the call

	; Sum two 16 bit numbers
sum16:	movwf	X2L, w, a
	addwfc	YL, f, a
	
	movwf	X2H, w, a
	addwfc	YH, f, a
	return 1
	
end
;---------------------------------------------------------------------------------------
#include <xc.inc>
	goto start	
	
	goto start	
	
	; Convert ASCII into 7 Segment pattern
	; Start by copying the program from tblrd
	
	psect data  
lookup:	DB  0x81, 0xCF, 0x92, 0x86, 0xCC, 0xA4, 0xA0, 0x8F, 0x80, 0x84	
	
	psect code
SSEG	EQU 0x41    ; 7segment pattern table starting address in data memory
I	EQU 0x70    ; used as a counter index
start:	
	; Move the 7seg pattern from program memory into data memory
	movlw	low lookup
	movwf	TBLPTRL, f, a
	movlw	high lookup
	movwf	TBLPTRH, f, a
	movlw	low highword lookup
	movwf	TBLPTRU, f, a
	
	lfsr	0, SSEG ; starting address in data memory
	movlw	10
	movwf	I, f, a ; initialize counter with 10
loop:	TBLRD*+    ; read 1B from program memory and advance TBLPTR by 1
	movff	TABLAT, POSTINC0 ;copy TABLAT into INDF0 them move FSR0 pointer forward
	decf	I, f, a;
	bnz	loop
	
	
	; translate the content of WREG from ASCII into 7Seg
	movlw	0x39 ; test value
	call ascii2sseg, 0

stop:	bra	stop
	
	; convert ASCII digit stored in WREG into BCD and store in 4 lsb of WREG
ascii2bcd:
	andlw	0x0F; mask to keep low 4 of WREG only
	return 0   ; WREG will have the proper BCD
	
    
	; convert a BCD pattern stored in 4 lsb of WREG into 7Seg
bcd2sseg: 
	lfsr	0, SSEG; move fsr0 pointer back to start of table
	movf	PLUSW0, w, a
	return 0; WREG will have the sseg pattern upon return
	
	; convert ASCII 2 7Seg using the 2 subroutines above
ascii2sseg:
	call ascii2bcd, 0
	call bcd2sseg, 0
	return 0
    
end