.data

.word 10

.text

.global main

main:
                             
lui x2 0x10000
lw x2 0(x2)
lw x3 0x10012
addi x1 x0 32
add x5 x0 x0 
sw x0 4(x3)
sw x1 8(x3)

On:
    addi x5 x0 0
    sw x1 12(x3)
    
    On_delay:
        beq x5 x2 Off
        addi x5 x5 1
        beq x0 x0 On_delay
    
Off:
    addi x5 x0 0
    sw x0 12(x3)
    
    Off_delay:
        beq x5 x2 On
        addi x5 x5 1
        beq x0 x0 Off_delay        
    