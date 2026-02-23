OUTPUT_FORMAT(elf64-x86-64)
OUTPUT_ARCH(i386:x86-64)
pcore_start = 2M;
ENTRY(_start)
SECTIONS {
    . = pcore_start;

    .text : {
        KEEP(*(.multiboot))
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