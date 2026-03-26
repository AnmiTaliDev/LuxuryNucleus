.section .text
.global _start
.type _start, @function
_start:
    call init_start
    cli
    hlt