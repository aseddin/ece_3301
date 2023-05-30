#include <xc.inc>
    ;psect code

    num_A equ 0x40
    num_B equ 0x50
    num_C equ 0x60
 
    ;A = 10
    movlw   10
    movwf   num_A, f, a
    
    ;B = 15
    movlw   15
    movwf   num_B, f, a
    
    ; WREG = A + B
    movf    num_A, w, a
    addwf   num_B, w, a
    
    ; Move WREG to C
    movwf   num_C, f, a
    
end
