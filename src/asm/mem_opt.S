.set noreorder
    .text

    .globl mips_fast_memcpy
mips_fast_memcpy:
    move  $t0, $a0        # dest
    move  $t1, $a1        # src
    move  $t2, $a2        # n
1:
    beq   $t2, $zero, 2f
    nop
    lbu   $t3, 0($t1)
    sb    $t3, 0($t0)
    addiu $t1, $t1, 1
    addiu $t0, $t0, 1
    addiu $t2, $t2, -1
    b     1b
    nop
2:
    move  $v0, $a0        # return dest
    jr    $ra
    nop
