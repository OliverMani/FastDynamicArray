.section .rodata
.globl POWs
POWs:
    .long 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648

.section .text

.extern floorlog2
.extern .__return_zero
.extern .__return_one
.extern intpow
# .extern POWs


# Input:
#  - uint32_t index => %edi
.globl calculate_root
.type calculate_root, @function
calculate_root:
    cmpl $0, %edi
#    test %edi, %edi     # if index is 0
    je .__return_zero   # return 0
    call floorlog2      # calculates the root index
    incl %eax           # adds 1 to the result
    ret                 # returns


.globl calculate_root_length
.type calculate_root_length, @function
# Input:
#  - uint32_t root_index => %edi
calculate_root_length:
    test %edi, %edi
    je .__return_one
    push %rsi
    push %rdi
    call intpow
    movl %eax, %esi
    pop %rdi
    movl (%esi, %edi, 4), %eax
    pop %rsi
    ret

# Input:
#  - uint32_t index => %edi
# .globl calculate_subindex
# calculate_subindex:
#    test %edi, %edi
#    je .__return_zero
#    call calculate_root



.__return_zero:
    xor %eax, %eax
    ret

.__return_one:
    movl $1, %eax
    ret

.section .note.GNU-stack,"",@progbits
