#include <xc.inc>
    ;psect code
    
    ; test the value of a specific bit (check Z)
    movlw   10110111B
    andlw   00000100B
    
    ; test for even or odd
    movlw   10110111B
    andlw   00000001B; if Z = 1 === even number
    
    ; mask the certain bits (zero them out)
    movlw   0x25
    movwf   0x10, f, a
    movlw   00001111 ;MASK= 0x0F
    andwf   0x10, f, a
    
    ; set certain bits
    movlw   0x25
    movwf   0x10, f, a
    movlw   00001111;MASK = 0x0F
    iorwf   0x10, f, a
    
    ; toggle certain bits
    movlw   0x25
    movwf   0x10, f, a
    movlw   0xff; MASK = 0xFF; toggle all bits
    xorwf   0x10, f, a 
    
    ; set a certain bit
    movlw   0x25
    movwf   0x10, f, a
    movlw   00010000
    iorwf   0x10, f, a
    
    ; clear a certain bit
    movlw   0x25
    movwf   0x10, f, a
    movlw   11101111
    andwf   0x10, f, a
    
    ; toggle a certain bit
    movlw   0x25
    movwf   0x10, f, a
    movlw   00010000
    xorwf   0x10, f, a
    
    
end