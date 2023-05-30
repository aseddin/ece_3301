#include <xc.inc>
    ;psect code
    
    num_a equ 0x50
 
    ; store the value 0xc2 in 0x50, a is only the lower 6 bits
    movlw   0xc2
    andlw   00111111B
    movwf   num_a, f, a
    
    
    ; multiplication by 4 equate to 2 right shifts (no carry)
    rlncf   num_a, f, a
    rlncf   num_a, f, a
    
    ; set bit 0 and 2
    bsf	    num_a, 0, a
    bsf	    num_a, 2, a
    
    ; clear bit 5 to 0
    movf    num_a, w, a
    andlw   11000000B
    movwf   num_a, f, a
    
    ; toggle bit 7
    btg     num_a, 7, a
end
