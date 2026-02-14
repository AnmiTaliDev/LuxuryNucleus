/* [Changed] | Source: OSDev Wiki, Bare Bones */

.section .multiboot
.align 4
.long 0xE85250D6
.long 0
.long header_end - header_start  # header length
.long -(0xE85250D6 + (header_end - header_start))  # checksum

header_start:

    .short 0                 # tag type
    .short 0                 # flags
    .long 8                  # size

header_end:

.section .text
.global _start
_start:
	
	call kernel_init_start
	cli
1:	hlt
	jmp 1b
