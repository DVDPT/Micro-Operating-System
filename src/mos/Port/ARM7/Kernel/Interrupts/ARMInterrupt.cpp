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
	void arm_enable_interrupt();
	void arm_disable_interrupt();
	bool arm_is_intr_enable();
}

void InterruptController::EnableInterrupts()
{
	arm_enable_interrupt();
}

void InterruptController::DisableInterrupts()
{
	arm_disable_interrupt();
}

bool InterruptController::AreInterruptsEnable()
{
	return arm_is_intr_enable();
}


