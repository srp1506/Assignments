.data

.dword 0x000000000001300217
# Replace the value of this register with the value you would like x4 to have 

.text

lui x4 0x10000
ld x3 0(x4)
addi x1 x0 -1
srli x1 x1 57
and x2 x3 x1
add x10 x0 x0

addi x5 x0 51
beq x2 x5 R

addi x5 x0 19
beq x2 x5 I
addi x5 x0 3
beq x2 x5 I
addi x5 x0 115
beq x2 x5 I
addi x5 x0 103
beq x2 x5 I

addi x5 x0 99
beq x2 x5 B

addi x5 x0 35
beq x2 x5 S

addi x5 x0 111
beq x2 x5 J

addi x5 x0 55
beq x2 x5 U
addi x5 x0 23
beq x2 x5 U

beq x0 x0 end

R:
    addi x10 x0 1
    beq x0 x0 end
I:
    addi x10 x0 2
    beq x0 x0 end
B:
    addi x10 x0 3
    beq x0 x0 end
S:
    addi x10 x0 4
    beq x0 x0 end
J:
    addi x10 x0 5
    beq x0 x0 end
U:
    addi x10 x0 6
    beq x0 x0 end
end:
    add x10 x10 x0
