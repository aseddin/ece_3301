#include <xc.inc>
    ;psect code
    
    ; Rotations
    
    ; left::
    ; rlcf: rotate left f through carry 
    movlw   10101101B
    movwf   0x10, f, a
    rlcf    0x10, w, a; check the value of C flag
    
    ; rlncf: rotate left f (no carry)
    movlw   10101101B
    movwf   0x10, f, a
    rlncf   0x10, w, a; check the value of C flag
    
    ; rlncf can be used to multiply by 2 (assuming no 1 is pushed out of f)
    movlw   00101101B
    movwf   0x10, f, a
    rlncf   0x10, w, a; answer should be double of that in 0x10
    
    ; right::
    ; rrcf: rotate right f through carry 
    movlw   10101101B
    movwf   0x10, f, a
    rrcf    0x10, w, a; check the value of C flag
    
    ; rrncf: rotate right f (no carry)
    movlw   10101101B
    movwf   0x10, f, a
    rrncf   0x10, w, a; check the value of C flag
    
    ; rrncf can be used to divide by 2 (assuming no 1 is pushed out of f)
    movlw   10101100B
    movwf   0x10, f, a
    rrncf   0x10, w, a; answer should be half of that in 0x10
    

end