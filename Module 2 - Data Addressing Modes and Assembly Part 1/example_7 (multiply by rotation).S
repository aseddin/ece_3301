#include <xc.inc>
    ;psect code
    
    num_a equ 0x50
 
    ; store the value 0xc2 in 0x50, a is only the c part
    movlw   0xc2
    movwf   num_a, f, a
    
    ; a x 16
    movlw   0xF0; clear out the lower bits
    andwf   num_a, f, a
    swapf   num_a, f, a; swapping nibbles to move the upper 4 bit value into the lower 4 bit value
    
    ; multiplication by 16 equate to 4 right shifts (no carry)
    rlncf   num_a, f, a
    rlncf   num_a, f, a
    rlncf   num_a, f, a
    rlncf   num_a, f, a
end