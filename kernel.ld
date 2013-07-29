/******************************************************************************
*	kernel.ld
*    by Matthias Simons based on the kernel.ld
*	 by Alex Chadwick
*
*	A linker script for generation of raspberry pi kernel images.
******************************************************************************/

SECTIONS {
	/* Vor allem anderen: Interruptvektoren */
	.init 0x8000 : {
		*(.init)
	}
	
	/**/

	/*
	* First and formost we need the .init section, containing the code to 
        * be run first. We allow room for the ATAGs and stack and conform to 
        * the bootloader's expectation by putting this code at 0x8000.
	*/
	.reset 0x8040 : {
		*(.reset)
	}
	
	/* 
	* Next we put the rest of the code.
	*/
	.text : {
		*(.text)
	}

	/* 
	* Next we put the data.
	*/
	.data : {
		*(.data)
	}
	/* 
	* and the bss
	*/
	.bss : {
		*(.bss)
	}

	/* 
	* Next we put the rodata.
	*/
	.rodata : {
		*(.rodata)
	}

	/* 
	* Next we put the COMMON
	*/
	COMMON : {
		*(COMMON)
	}
	
	/*
	* Finally comes everything else. A fun trick here is to put all other 
	* sections into this section, which will be discarded by default.
	*/
	/DISCARD/ : {
		*(*)
	}
}
