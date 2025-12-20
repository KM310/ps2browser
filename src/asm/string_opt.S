    .set noreorder
    .text

    .globl mips_fast_strlen
mips_fast_strlen:
    move  $t0, $a0        # s
    move  $v0, $zero      # length = 0
1:
    lbu   $t1, 0($t0)
    beq   $t1, $zero, 2f
    addiu $t0, $t0, 1
    addiu $v0, $v0, 1
    b     1b
    nop
2:
    jr    $ra
    nop
