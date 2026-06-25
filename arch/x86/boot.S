.intel_syntax noprefix

.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:


.section .text
.global halt
halt:
    cli
1:  hlt
    jmp 1b

.global init_boot
.code32
init_boot:
    in al, 0x92
    test al, 2
    jnz after
    or al, 2
    and al, 0xFE
    out 0x92, al
    after:
#if ARCH_CAP == 32
    mov esp, offset stack_top
    call init_main
#elif ARCH_CAP == 64

#endif