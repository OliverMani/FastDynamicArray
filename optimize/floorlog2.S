.section .text
.globl floorlog2
floorlog2:         # %edi is the only parameter, %eax is the return
    xorl %eax, %eax # Set return register to zero
    cmpl $65535, %edi # compare 65535, %edi
    jbe .__fl2_skip1   # if 65535 <= %edi then skip
    shrl $16, %edi  # Right shift 16 bits
    orl $16, %eax   # Flip bit in the result
.__fl2_skip1:       # we can jump here
    cmpl $255, %edi
    jb .__fl2_skip2
    shrl $8, %edi
    orl $8, %eax
.__fl2_skip2:
    cmpl $15, %edi
    jbe .__fl2_skip3
    shrl $4, %edi
    orl $4, %eax
.__fl2_skip3:
    cmpl $7, %edi
    jbe .__fl2_skip4
    shrl $2, %edi
    orl $2, %eax
.__fl2_skip4:
    cmpl $3, %edi
    jbe .__fl2_skip5
    shrl $1, %edi
    orl $1, %eax
.__fl2_skip5:
    cmpl $1, %edi
    jbe .__fl2_end
    incl %eax
.__fl2_end:
    ret # returns

.section .note.GNU-stack,"",@progbits