.data

.dword 1000
.dword 1001
.dword 1002
.dword 1003
.dword 1004
.dword 1005
.dword 1006
.dword 1007
.dword 1008
.dword 1009
.dword 523
.dword 524
.dword 525
.dword 533
.dword 512

.text

lui x3, 0x10000
add x10, x0, x0
ld x1, 0(gp)
add x10, x0, x1
ld x1, 8(gp)
add x10, x10, x1
ld x1, 16(gp)
add x10, x10, x1
ld x1, 24(gp)
add x10, x10, x1
ld x1, 32(gp)
add x10, x10, x1
ld x1, 40(gp)
add x10, x10, x1
ld x1, 48(gp)
add x10, x10, x1
ld x1, 56(gp)
add x10, x10, x1
ld x1, 64(gp)
add x10, x10, x1
ld x1, 72(gp)
add x10, x10, x1
ld x1, 80(gp)
sub x10, x10, x1
ld x1, 88(gp)
sub x10, x10, x1
ld x1, 96(gp)
sub x10, x10, x1
ld x1, 104(gp)
sub x10, x10, x1
ld x1, 112(gp)
sub x10, x10, x1