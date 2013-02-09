/* Adapted for CortexM3 LPC1768, originally based on LPC21xx and LPC22xx User 
 * Manual UM10114, pg. 15. */

OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_startup)

MEMORY
{
	flash (rx)  : ORIGIN = 0x00000000, LENGTH = 512K
	sram (rwx) : ORIGIN = 0x10000000, LENGTH =  32K
}

/* Define the top our stack at the end of SRAM */
_end_stack = 0x10008000;

EXTERN(__interrupt_vector_table);

SECTIONS
{
	.text :
	{
		/* Insert the interrupt vector table first */
		__interrupt_vector_table = .;
		*(.interrupt_vector_table)
		/* Startup assembly */
		*(.startup)

		/* Rest of the code (C) */
		*(.text)
		*(.rodata)
		*(.rodata*)
		*(.glue_7)
		*(.glue_7t)
		_end_text = .;
	} >flash

	.data :
	{
		_start_data = .;
		*(.data)
		_end_data = .;
	} >sram

	.bss :
	{
		_start_bss = .;
		*(.bss)
	} >sram

	. = ALIGN(4);
	_end_bss = .;

	. = ALIGN(256);

	/* Stack can grow down to here, right after data and bss sections in 
	 * SRAM */
	_start_stack = .;

	/* Linker wants .eh_frame section defined because of gcc 4.4.X bug,
	 * just discard it here. */
	/DISCARD/ :
	{
		*(.eh_*)
	}
}

_end = .;
PROVIDE(end = .);

