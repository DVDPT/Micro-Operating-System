/* ----------------------------------------------------------------------------
*         Diogo Cardoso & Ana Correia PS 2010/2011 DEETC - ISEL
* ----------------------------------------------------------------------------
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted.
*
* DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
* DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
* ----------------------------------------------------------------------------
*/
ENTRY(_start)

MEMORY
{
	
	  eram : ORIGIN = 0x81000000, LENGTH = 8192k
      ram : ORIGIN = 0x40000000, LENGTH = 16k
      rom : ORIGIN = 0x00000000, LENGTH = 256k
      erom : ORIGIN = 0x80000000, LENGTH = 8192k
	  
}

SECTIONS
{
	.debug_aranges  0 : { *(.debug_aranges) }
	.debug_pubnames 0 : { *(.debug_pubnames) }
	.debug_info     0 : { *(.debug_info) }
	.debug_abbrev   0 : { *(.debug_abbrev) }
	.debug_line     0 : { *(.debug_line) }
	.debug_frame    0 : { *(.debug_frame) }
	.debug_str      0 : { *(.debug_str) }
	.debug_loc      0 : { *(.debug_loc) }
	.debug_macinfo  0 : { *(.debug_macinfo) }
	

	.startup : {
		__startup_start__ = ABSOLUTE(.);
		*(.startup*);
		
		. = ALIGN(4);
		__startup_end__ = ABSOLUTE(.);
	} > ram

	.targetconfig : {
	__targetconfig__ = ABSOLUTE(.);
	*(.targetconfig*);
	
	. = ALIGN(4);
	__targetconfig__ = ABSOLUTE(.);
	} > ram
	
	.text  : {
		__text_start__ = ABSOLUTE(.);
		*(.text*)
		*(.gnu.warning)
		*(.gnu.linkonce*)
		*(.init)
		*(.glue_7)
		*(.glue_7t);
		__text_end__ = ABSOLUTE(.);
	} > eram

	.rodata ALIGN(4) : {
		__rodata_start__ = ABSOLUTE(.);
		*(.rodata*);
		. = ALIGN(4);
		__rodata_end__ = ABSOLUTE(.);
	} > eram

	.data ALIGN(4) : {
		__data_start__ = ABSOLUTE(.);
		*(.data*);
		*(.eh_frame);
		. = ALIGN(4);
		__data_end__ = ABSOLUTE(.) ;
	} > eram

	.bss ALIGN(4) : {
		__bss_start__ = ABSOLUTE(.);
		*(.bss*) *(COMMON);
		. = ALIGN(4);
		__bss_end__ = ABSOLUTE(.);
	} > eram

	.stack ALIGN(4) : {
		__stack_start__ = ABSOLUTE(.);
		*(.stack);
		. = ALIGN(4);
		__stack_end__ = ABSOLUTE(.);
	} > eram
	
	.init_array ALIGN(4) : {
		__ctors_init__ = ABSOLUTE(.);
		*(.init_array);
		__ctors_end__ = ABSOLUTE(.);
	} > eram

	__stack_top__ = __stack_end__;

	end = ABSOLUTE(.);

}
