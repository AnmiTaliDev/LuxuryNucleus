ENTRY(_start)
SECTIONS {
    nkernel_start = 2M;
    . = nkernel_start;

    .text :
    {
        *(.multiboot2)
        *(.text)
        . = ALIGN(4096);
    }

    .rodata :
    {
        *(.rodata)
        . = ALIGN(4096);
    }

    .data :
    {
        *(.data)
        . = ALIGN(4096);
    }

    .bss :
    {
        *(.bss)
        . = ALIGN(4096);
    }

    /DISCARD/ :
    {
        *(.eh_frame)
    }

    nkernel_end = .;
}