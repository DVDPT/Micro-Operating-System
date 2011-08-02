/*
 * ARMInterrupt.cpp
 *
 *  Created on: Jun 20, 2011
 *      Author: DVD
 */


#include "SystemTypes.h"
#include "Interrupts.h"

extern "C"
{
	void arm_clear_interrupt();
	void arm_set_interrupt();
}

void Interrupts::EnableInterrupts()
{
	arm_set_interrupt();
}

void Interrupts::DisableInterrupts()
{
	arm_clear_interrupt();
}


