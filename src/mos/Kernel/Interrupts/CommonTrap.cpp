/*
 * CommonTrap.cpp
 *
 *  Created on: Aug 4, 2011
 *      Author: DVD
 */
#include "Threading.h"
#include "InterruptController.h"

extern "C" void system_common_trap(Context ** runningThread)
{

	InterruptController::HandleInterrupt();

}
