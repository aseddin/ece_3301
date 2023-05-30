#include <xc.inc>
    ;psect code
    
    ; set a certain bit
    movlw   0x25
    movwf   0x10, f, a
    movlw   00010000
    iorwf   0x10, f, a
    
    ; the same using bsf instruction
    ; no need for mask or OR
    ; only capable of setting a single bit
    ; makes the code a bit easier to read
    movlw   0x25
    movwf   0x10, f, a
    bsf	    0x10, 4, a; 4 represent bit num 4 
    
    
    ; clear a certain bit
    movlw   0x25
    movwf   0x10, f, a
    movlw   11101111
    andwf   0x10, f, a
    
    ; using bcf
    movlw   0x25
    movwf   0x10, f, a
    bcf	    0x10, 4, a
    
    ; toggle a certain bit
    movlw   0x25
    movwf   0x10, f, a
    movlw   00010000
    xorwf   0x10, f, a
    
    ; using btg
    movlw   0x25
    movwf   0x10, f, a
    btg	    0x10, 4, a
end