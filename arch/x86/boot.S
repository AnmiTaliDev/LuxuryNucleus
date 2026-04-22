.section .text
.global kernel_init_boot
.code32
kernel_init_boot:
    call setup_stack_pointer
//  ...
    call kernel_init_general
    cli
    hlt