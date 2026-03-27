nkernel_start = 2M;
ENTRY(_start)
SECTIONS {
    . = nkernel_start;

    .text : {
        KEEP(*(.multiboot2))
        *(.text)
    }

    .rodata : {
        *(.rodata)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(COMMON)
        *(.bss)
    }
    
    nkernel_end = .;
}