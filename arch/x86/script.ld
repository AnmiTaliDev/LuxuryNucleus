ENTRY(_start)
SECTIONS
{
	pcore_page_size = 4K;
	pcore_start = pcore_page_size * 500;
	. = pcore_start;

	.text BLOCK(pcore_page_size) : ALIGN(pcore_page_size)
	{
		*(.multiboot)
		*(.text)
	}

	.bss BLOCK(pcore_page_size) : ALIGN(pcore_page_size)
	{
		*(.bss)
	}

	.rodata BLOCK(pcore_page_size) : ALIGN(pcore_page_size)
	{
		*(.rodata)
	}

	.data BLOCK(pcore_page_size) : ALIGN(pcore_page_size)
	{
		*(.data)
	}

	pcore_end = .;
}