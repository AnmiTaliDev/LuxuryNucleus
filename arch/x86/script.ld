pcore_start = 2M;
ENTRY(_start)
SECTIONS {
    . = pcore_start;

    .text : {
        KEEP(*(.multiboot2))
        *(.text)
    }

    .data : {
        *(.data)
    }

    .rodata : {
        *(.rodata)
    }

    .bss : {
        *(.bss)
    }
    
    pcore_end = .;
}