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
	///
	///	Sets the standard output.
	///
	System::SetStandardOutput(_systemOutStream);

	///
	///	The system can't work without at least one timer.
	///
	DebugAssertNotNull(_timerIntrDesc);

	///
	///	Configure timer frequency and interrupt period.
	///
	SystemTimer::Configure(SYSTEM_TIMER_CLOCK_FREQUENCY, SYSTEM_TIMER_INTERRUPT_PERIOD);

	///
	///	Set the system isr as the scheduler timer isr.
	///
	_timerIntrDesc->SetSystemDefinedIsr((SystemIsr)&UScheduler::SystemTimerInterruptRoutine);

	///
	///	Set the system pisr for the timer.
	///
	_timerIntrDesc->SetSystemDefinedPisr((SystemPisr)&UScheduler::SystemTimerPostInterruptRoutine);

	///
	///	Enable timer interrupts.
	///
	InterruptController::UnmaskInterrupt(KERNEL_INTERRUPTS_TIMER);

	///
	///	Enable timer.
	///
	SystemTimer::Enable();

	///
	///	Reset the configuration pointer so that is no longer possible to configure the system.
	///
	_configuration = NULL;
}
