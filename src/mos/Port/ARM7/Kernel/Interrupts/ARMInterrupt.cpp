/*
 * ARMInterrupt.cpp
 *
 *  Created on: Jun 20, 2011
 *      Author: DVD
 */


#include "SystemTypes.h"
#include "InterruptController.h"

extern "C"
{
	void arm_clear_interrupt();
	void arm_set_interrupt();
	bool arm_is_intr_enable();
}

void InterruptController::EnableInterrupts()
{
	arm_set_interrupt();
}

void InterruptController::DisableInterrupts()
{
	arm_clear_interrupt();
}

bool InterruptController::AreInterruptsEnable()
{
	return arm_is_intr_enable();
}


