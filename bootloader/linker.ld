ENTRY(_start)

SECTIONS
{
    . = 0x60000;

	_stext = .;
	.text : AT(0x80000)
	{
		*(.text.boot)
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

      . = 0x70000;
  	_estack = .;

  	. = 0x80000;
  	_kernel = .;
}
bss_size = (_ebss - _sbss) >> 3;
code_size = (_edata - _stext) >> 3;