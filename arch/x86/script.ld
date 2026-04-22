ENTRY(kernel_init_boot)
mmio_addr_alloc_kernel_start = 2M;
SECTIONS {
    . = mmio_addr_alloc_kernel_start;

    .text :
    {
        KEEP(*(.multiboot2))
        mmio_addr_alloc_text_start = .;
        *(.text)
        mmio_addr_alloc_text_end = .;
        . = ALIGN(4096);
    }

    .bss :
    {
        mmio_addr_alloc_bss_start = .;
        *(.bss)
        mmio_addr_alloc_bss_end = .;
        . = ALIGN(4096);
    }

    .rodata :
    {
        mmio_addr_alloc_rodata_start = .;
        *(.rodata)
        mmio_addr_alloc_rodata_end = .;
        . = ALIGN(4096);
    }

    .data :
    {
        mmio_addr_alloc_data_start = .;
        *(.data)
        mmio_addr_alloc_data_end = .;
        . = ALIGN(4096);
    }

    mmio_addr_alloc_kernel_end = .;
}