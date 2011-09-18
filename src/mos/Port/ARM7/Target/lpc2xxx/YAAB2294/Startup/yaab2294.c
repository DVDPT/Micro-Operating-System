#include "SystemTypes.h"

SECTION(".targetconfig") NAKED void  target_config()
{
	ASM_VOLATILE
		(
			    "ldr r0,=0xFFE00004\n"
			    "ldr r1,=0xFFE00000\n"
			    //"ldr r2,=0x20000c40\n"
				"ldr r2,=0x20000CEF\n"

				"ldr r3,=0x1000348F\n"
			    "str r2,[r0]\n"
			    "str r3,[r1]\n"
				"ldr r0, =0xe01fc040\n"
				"mov r1,#2\n"
				"str r1,[r0]\n"
				"mov pc ,lr\n"

		);
}

