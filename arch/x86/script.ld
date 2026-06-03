SECTIONS {
    ENTRY(init_boot)
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

        mmio_addr_alloc_initservices_start = .;
        KEEP(*(.rodata.init_services))
        mmio_addr_alloc_initservices_end = .;

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