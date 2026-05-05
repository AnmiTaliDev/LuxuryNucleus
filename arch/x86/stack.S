.intel_syntax noprefix

.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:


.section .text
.global setup_stack_pointer
setup_stack_pointer:
    mov esp, offset stack_top