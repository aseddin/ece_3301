#include <xc.inc>
    ;psect code

    NUM_A equ 0x40
    NUM_B equ 0x50
    NUM_CH equ 0x61
    NUM_CL equ 0x60
 
    ; A = 25
    movlw   25
    movwf   NUM_A, f, a
    
    ; B = 10
    movlw   10
    movwf   NUM_B, f, a
    
    ; Compute A^2
    movf    NUM_A, w, a
    mulwf   NUM_A, a
    movff PRODL, 0x41
    movff PRODH, 0x42
    
    ; Compute B^2
    movf    NUM_B, w, a
    mulwf   NUM_B, a
    
    ; sum of the low byte
    movf    0x41, w, a
    addwf   PRODL, w, a
    movwf   NUM_CL, f, a
    
    ; sum of the high byte
    movf    0x42, w, a
    addwfc  PRODH, w, a
    movwf   NUM_CH, f, a
        
end