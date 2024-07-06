.data
.dword 10 # number of computations to be performed
.dword 14 35 35 34 16 8 16 17 19 361 7 11 15 15 0 12 0 0 1 5 # input pairs
.text

ld x18 0(gp) # getting the limit of iteration
addi x21 gp 0x100 # loading the address for output
add x19 x0 gp # loading the address to take inputs
add x20 x0 x0 # counter variable

L1: #main loop
    beq x18 x20 end
    ld x11 8(x19) # first argument 
    ld x12 16(x19) #second argument
    blt x12 x11 L2 #preprocessing
    add x13 x0 x11
    add x11 x0 x12
    add x12 x0 x13
    L2:
        jal x1 GCD # function call
        addi x20 x20 1
        addi x19 x19 16
        addi x21 x21 8
        beq x0 x0 L1
        
end: 
    beq x0 x0 end # program end
    
# gcd function
GCD: # no return value
    beq x12 x0 Return #edge case
    blt x11 x12 Check # repeated subtraction
    sub x11 x11 x12
    beq x0 x0 GCD
        
    Check:
        beq x11 x0 Return # if remainder is 0 return
        add x13 x0 x11 # updating arguments for repeated subtraction
        add x11 x0 x12
        add x12 x0 x13
        beq x0 x0 GCD
        
    Return:
        sd x12 0(x21) # storing result at output location
        jalr x0 x1 0 # returning to caller