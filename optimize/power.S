.section .text

.globl intpow
# Input:
# %edi => base as int32
# %esi => exp  as int32
intpow:
    test %esi, %esi
    jne .__ipskip1
    movl $1, %eax
    ret
.__ipskip1:
    push %rbx
    movl $1, %eax
.__iploop1:
    cmpl $1, %esi
    jb .__ipfinish
    movl %esi, %ebx
    andl $1, %ebx
    test %ebx, %ebx
    je .__iploop_skip1
    mul %edi
.__iploop_skip1:
    imul %edi, %edi
    shrl $1, %esi
    jmp .__iploop1
.__ipfinish:
    pop %rbx
    ret

.section .note.GNU-stack,"",@progbits