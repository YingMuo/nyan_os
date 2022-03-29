SECTIONS
{
    . = 0x80000;

	_stext = .;
	.text : 
	{
		*(.text.start)
		*(.text)
		*(.rodata)
	}
	. = ALIGN(0x1000);
	_etext = .;

	_sdata = .;
	.data : { *(.data) }
	. = ALIGN(0x1000);
	_edata = .;

	_sbss = .;
	.bss : { *(.bss*) } 
	. = ALIGN(0x1000);
	_ebss = .;

    . = 0x200000;
	_stack_top = .;
}
bss_size = (_ebss - _sbss) >> 3;