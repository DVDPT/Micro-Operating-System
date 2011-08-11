#pragma once

#include "SystemTypes.h"
#include "System.h"
#include "SystemConfiguration.h"

class SystemTimer
{

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
	///	Returns the current ticks.
	///
	PORT_SPECIFIC U32 static GetCurrentTicks();

	///
	///	Classes System and SystemConfiguration can access private members of this class.
	///
	friend class SystemConfiguration;
	friend class System;
};
