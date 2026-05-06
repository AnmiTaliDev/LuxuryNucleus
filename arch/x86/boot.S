.intel_syntax noprefix

.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:


.section .text
.global init_boot
.code32
init_boot:
    mov esp, offset stack_top
    call init_prepare
    hlt
