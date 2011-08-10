/*
 * SystemConfiguration.cpp
 *
 *  Created on: Aug 10, 2011
 *      Author: DVD
 */

#include "SystemConfiguration.h"

SystemConfiguration* SystemConfiguration::_configuration = NULL;

void SystemConfiguration::Configure()
{
	DebugAssertNotNull(_timerIntrDesc);

	//_timerIntrDesc->SetSystemDefinedIsr((SystemIsr)&UScheduler::SystemTimerInterruptRoutine);
	InterruptController::UnmaskInterrupt(KERNEL_INTERRUPTS_TIMER);

	_configuration = NULL;
}
