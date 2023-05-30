#include <xc.inc>
    ;psect code

    movlw   0x0a
    movwf   0x20, f, a
    
    movlw   0x07
    movwf   0x21, f, a
    
    ; Method 1 (store the result in WREG)
    addwf   0x20, w, a
    
    sum	equ 0x32
    movwf   sum, f, a
    
    ; Method 2 (store the result in 0x20)
    addwf   0x20, f, a
    sum equ 0x32
    movff   0x20, sum, a 
    
end

