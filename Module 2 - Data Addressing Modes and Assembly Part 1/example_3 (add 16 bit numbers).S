#include <xc.inc>
    ;psect code

    ;A = 0x1401
    num_AH equ 0x41
    num_AL equ 0x40
    
    movlw   0x14
    movwf   num_AH, f, a
    movlw   0x01
    movwf   num_AL, f, a
    
    ;B = 0x012A
    num_BH equ 0x51
    num_BL equ 0x50
    
    movlw   0x01
    movwf   num_BH, f, a
    movlw   0x2A
    movwf   num_BL, f, a
    
    ; C
    num_CH equ 0x61
    num_CL equ 0x60
 
    ; sum the low bytes first
    movwf   num_AL, w, a
    addwf   num_BL, w, a
    movwf   num_CL, f, a
    
    ; sum the high bytes
    movwf   num_AH, w, a
    addwfc  num_BH, w, a; add with carry
    movwf   num_CH, f, a
    
    
end


