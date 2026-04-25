SECTIONS {
    ENTRY(kernel_init_boot)
    mmio_addr_alloc_kernel_start = 2M;
    . = mmio_addr_alloc_kernel_start;

    .text :
    {
        KEEP(*(.multiboot2))
        mmio_addr_alloc_text_start = ABSOLUTE(.);
        *(.text .text.*)
        mmio_addr_alloc_text_end = ABSOLUTE(.);
        . = ALIGN(4096);
    }

    .bss :
    {
        mmio_addr_alloc_bss_start = ABSOLUTE(.);
        *(.bss .bss.* COMMON)
        mmio_addr_alloc_bss_end = ABSOLUTE(.);
        . = ALIGN(4096);
    }

    .rodata :
    {
        mmio_addr_alloc_rodata_start = ABSOLUTE(.);
        *(.rodata .rodata.*)
        mmio_addr_alloc_rodata_end = ABSOLUTE(.);
        . = ALIGN(4096);
    }

    .data :
    {
        mmio_addr_alloc_data_start = ABSOLUTE(.);
        *(.data .data.*)
        mmio_addr_alloc_data_end = ABSOLUTE(.);
        . = ALIGN(4096);
    }

    mmio_addr_alloc_kernel_end = ABSOLUTE(.);
}