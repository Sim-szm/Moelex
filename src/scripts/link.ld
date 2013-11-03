/*
* name : link.ld
* description : linker script for the kernel ,and based the we start everything running in the correct place !
* thanks for the original writter - Bran's kernel development
* Care : all data align with 4096 
*/
ENTRY(start)
SECTIONS
{
	.text 0x100000 :
	{
		code = .; _code = .; __code = .;
		*(.text)
		. = ALIGN(4096);
	}
	.data :
	{
		data = .; _data = .; __data = .;
		*(data)
		*(.rodata)
		. = ALIGN(4096);
	}
	.bss :
	{
		bss = .; _bss = .; __bss = .;
		*(.bss)
		. = ALIGN(4096);
	}
	.stab :
	{
		stab = .; _stab = .; __stab = .;
		*(.stab)
		. = ALIGN(4096);
	}
	.stabstr :
	{
		stabstr = .; _stabstr = .; __stabstr = .;
		*(.stabstr)
		. = ALIGN(4096);
	}
	end = .; _end = .; __end = .;

}
