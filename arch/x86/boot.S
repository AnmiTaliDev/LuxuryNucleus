.intel_syntax noprefix

.section .text
.global init_boot
.code32
init_boot:
    //call setup_stack_pointer
    call init_prepare
    cli
1:  hlt
    jmp 1b