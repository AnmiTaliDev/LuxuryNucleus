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
#if ARCH_CAP == 32
    mov esp, offset stack_top
#elif ARCH_CAP == 64
    mov rsp, offset stack_top
#endif
    call init_prepare
    hlt
