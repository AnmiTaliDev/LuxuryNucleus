.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.type _start, @function
_start:
    
    call kernel_init_start
    cli
1:	hlt
	jmp 1b
