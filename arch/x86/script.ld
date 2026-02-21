ENTRY(_start)
pcore_start = 2M;
SECTIONS {
    . = pcore_start;

    .text : {
        *(.multiboot)
        *(.text*)
    }

    .data : {
        *(.data*)
    }

    .rodata : {
        *(.rodata*)
    }

    .bss : {
        *(.bss*)
    }
    
    pcore_end = .;

    /DISCARD/ :
    {
        *(.eh_frame*)
        *(.comment)
    }
}