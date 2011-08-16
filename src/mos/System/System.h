#pragma once

#include "SystemTypes.h"
#include "SystemConfiguration.h"
#include "IOutputStream.h"


///
///	The System class is a facade for some basic system operations
///


class System
{
	friend class SystemConfiguration;
	
	///
	///	The system outputstream.
	///
	static IOutputStream* _out;

	///
	///	Sets the standard output to @out.
	///
	static void SetStandardOutput(IOutputStream* out){_out = out;}
public:


	///
	///	Disable interrupts, return true if the interrupts were enable.
	///
	static bool AcquireSystemLock();

	///
	///	Enables interrupts if @previousState is true.
	///
	static void ReleaseSystemLock(bool previousState);
	///
	///	Enables the system interrupts.
	///
	static void EnableInterrupts();
	
	///
	/// Disable system interrupts.
	///
	static void DisableInterrupts();

	///
	///	Returns the current system ticks 32bits.
	///
	static U64 GetTickCount();


	///
	///	Returns the system standard output.
	///
	static IOutputStream& GetStandardOutput(){return *_out;}
};
