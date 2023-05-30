#include <xc.inc>
    ;psect code

    ; first stacked BCD
    movlw   0x42
    movwf   0x20, f, a
    
    ; second stacked BCD
    movlw   0x29
    movwf   0x21, f, a
    
    ; add the numbers
    movf    0x20, w, a
    addwf   0x21, w, a
    
    ; correct the packed BCD number
    DAW
end