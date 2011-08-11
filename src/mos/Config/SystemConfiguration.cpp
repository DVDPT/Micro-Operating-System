/*
 * SystemConfiguration.cpp
 *
 *  Created on: Aug 10, 2011
 *      Author: DVD
 */

#include "SystemConfiguration.h"
#include "SystemTimer.h"
#include "SystemConfig.h"

SystemConfiguration* SystemConfiguration::_configuration = NULL;

void SystemConfiguration::Configure()
{
	DebugAssertNotNull(_timerIntrDesc);

	///
	///	Configure timer frequency and interrupt period.
	///
	SystemTimer::Configure(SYSTEM_TIMER_CLOCK_FREQUENCY, SYSTEM_TIMER_INTERRUPT_PERIOD);

	///
	///	Set its system isr as the scheduler timer isr.
	///
	_timerIntrDesc->SetSystemDefinedIsr((SystemIsr)&UScheduler::SystemTimerInterruptRoutine);

	///
	///	Enable timer interrupts.
	///
	InterruptController::UnmaskInterrupt(KERNEL_INTERRUPTS_TIMER);

	///
	///	Enable timer.
	///
	SystemTimer::Enable();

	_configuration = NULL;
}
