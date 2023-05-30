#include <xc.inc>
    psect code
    
    num_a equ 0x50
 
    ; store the value 0xa2 in 0x50, a is only the c part
    movlw   0xa2
    movwf   num_a, f, a
    
    ; Logic right shift (ignores the sign bit)
    movf    num_a, w, a
    andlw   0xF0; mask to keep the upper bits only
    movwf   num_a, a
    rrncf   num_a, f, a; first roate
    rrncf   num_a, f, a; 2nd roate
    rrncf   num_a, f, a; 3rd roate
    rrncf   num_a, f, a; rth roate
    
    
    ; Arithmetic right shift (preserve the sing bit)
    ; test for the msb value (4th bit in this example)
    movf   num_a, w, a
    andlw   00001000B; if z ~= 0 it is the same as saying number is negative
    bnz negative
    sleep
    
negative: 
    movlw   0xf0
    iorwf   num_a, f, a
    sleep
end
