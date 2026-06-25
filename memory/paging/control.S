.intel_syntax noprefix

.equ CR0_PAGING, 1 << 31

.section .text
.global paging_disable
.code32
paging_disable:
    mov eax, cr0
    and eax, ~CR0_PAGING
    mov cr0, eax
    ret

.global paging_enable
.code32
paging_enable:
    mov eax, cr0
    or eax, 0x80000001
    mov cr0, eax

    mov eax, cr4
    or eax, 0x00000010
    mov cr4, eax