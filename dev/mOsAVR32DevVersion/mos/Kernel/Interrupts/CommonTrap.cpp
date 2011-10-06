/*
 * CommonTrap.cpp
 *
 *  Created on: Aug 4, 2011
 *      Author: DVD
 */
#include "Threading.h"
#include "InterruptController.h"
#include "System.h"

extern "C" void system_common_trap(Context ** runningThread)
{

	InterruptArgs irqArgs(runningThread);

	InterruptController::HandleInterrupt(&irqArgs);
}
