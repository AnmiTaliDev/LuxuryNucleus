/* Source: OSDev Wiki */
ENTRY(_start)
SECTIONS
{
    .multiboot : ALIGN(8)
    {
        KEEP(*(.multiboot))
    }

    .text :
    {
        *(.text)
    }

    .rodata :
    {
        *(.rodata)
    }

   .data :
   {
        *(.data)
   }

   .bss :
   {
       *(.bss)
   }
}