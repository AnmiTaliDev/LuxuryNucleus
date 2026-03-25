nkernel_start = 2M;
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