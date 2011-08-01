/*
 * ARMInterrupt.cpp
 *
 *  Created on: Jun 20, 2011
 *      Author: DVD
 */


#include "SystemTypes.h"
#include "Interrupts.h"

#define IRQ (1<<7)
NAKED void Interrupts::EnableInterrupts()
{
	ASM_VOLATILE
	(
		"MRS     r1, CPSR\n"
		"BIC     r1, r1, #0x80\n"
		"MSR     CPSR, r1\n"
	);
}

NAKED void Interrupts::DisableInterrupts()
{
	ASM_VOLATILE
	(
		"MRS     r1, CPSR\n"
		"ORR     r1, r1, #0x80\n"
		"MSR     CPSR_c, r1\n"
	);
}


