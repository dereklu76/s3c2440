OUTPUT_ARCH(arm)
ENTRY(_start)

SECTIONS{
	. = 0x30008000;

	. = ALIGN(4);
	.text :
	{
		start.o(.text)
		*(.text)
	}

	. = ALIGN(4);
	.data :
	{
		*(.data)
	}

	. = ALIGN(4);
	_bss_start = .;
	.bss :
	{
		*(.bss)
	}

	. = ALIGN(4);
	_bss_end = .;
}
