#pragma once

#include "SystemTypes.h"
#include "System.h"
#include "SystemConfiguration.h"

class SystemTimer
{

	///
	///	The system global timer counter.
	///
	static U64 _timerCounter;

	///
	///	This method configures the platform timer to work at @clock(in Hz), and to generate an interrupt
	///	every @interruptPeriod (in milis).
	///
	PORT_SPECIFIC void static Configure(U32 clock, U32 interruptPeriod);

	///
	///	Starts the timer.
	///
	PORT_SPECIFIC void static Enable();

	///
	///	Disables the timer.
	///
	PORT_SPECIFIC void static Disable();

	///
	///	Classes System and SystemConfiguration can access private members of this class.
	///
	friend class SystemConfiguration;
	friend class System;

public:

	///
	///	Adds to the counter @milis.
	///
	void static AddTimerCounter(U32 milis);

	///
	///	Returns the current ticks.
	///
	U64 static GetCurrentTicks(){ return _timerCounter; }
};
