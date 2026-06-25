ENTRY(init_boot)
SECTIONS {
    mmio_addr_alloc_kernel_start = 2M;
    . = mmio_addr_alloc_kernel_start;

    .text :
    {
        KEEP(*(.multiboot2))
        mmio_addr_alloc_text_start = .;
        *(.text)
        mmio_addr_alloc_text_end = .;
    }

    .bss :
    {
        mmio_addr_alloc_bss_start = .;
        *(.bss)
        mmio_addr_alloc_bss_end = .;
    }

    .rodata :
    {
        mmio_addr_alloc_rodata_start = .;
        *(.rodata)

        providers_graphics_start = .;
        *(.providers_graphics)
        providers_graphics_end = .;

        mmio_addr_alloc_rodata_end = .;
    }

    .data :
    {
        mmio_addr_alloc_data_start = .;
        *(.data)
        mmio_addr_alloc_data_end = .;
    }

    mmio_addr_alloc_kernel_end = .;
}