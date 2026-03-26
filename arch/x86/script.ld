nkernel_start = 2M;
ENTRY(_start)
SECTIONS {
    . = nkernel_start;

    .text : {
        KEEP(*(.multiboot2))
        *(.text)
    }

    .bss : {
        *(.bss)
    }

    .rodata : {
        *(.rodata)
    }

    .data : {
        *(.data)
    }
    
    nkernel_end = .;
}