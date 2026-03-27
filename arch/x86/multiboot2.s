.set MULTIBOOT2_MAGIC, 0xE85250D6
.set MULTIBOOT2_ARCH,  0

.section .multiboot2
multiboot2_header:
    .long MULTIBOOT2_MAGIC
    .long MULTIBOOT2_ARCH
    .long multiboot2_header_end - multiboot2_header
    .long 0x100000000 - (MULTIBOOT2_MAGIC + MULTIBOOT2_ARCH + (multiboot2_header_end - multiboot2_header))

    .short 0
    .short 0
    .long 8
multiboot2_header_end:
