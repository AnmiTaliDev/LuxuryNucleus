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
    or al, 2
    out 0x92, al
#if __SIZEOF_POINTER__ == 4
    mov esp, offset stack_top
    call init_main
#elif __SIZEOF_POINTER__ == 8

#endif
    jmp halt