.set MULTIBOOT2_MAGIC, 0xE85250D6
.set MULTIBOOT2_ARCH,  0

.section .multiboot2
.align 8
multiboot_header_start:
    .long MULTIBOOT2_MAGIC
    .long MULTIBOOT2_ARCH
    .long multiboot_header_end - multiboot_header_start
    .long 0x100000000 - (MULTIBOOT2_MAGIC + MULTIBOOT2_ARCH + (multiboot_header_end - multiboot_header_start))

    .short 0    # type
    .short 0    # flags
    .long 8     # size
multiboot_header_end:

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.type _start, @function
_start:
    lea rsp, [stack_top]
    call kernel_init_start
    cli
1:	hlt
	jmp 1b
