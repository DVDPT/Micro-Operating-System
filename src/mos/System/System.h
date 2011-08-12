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
	///	Enables the system interrupts.
	///
	static void EnableInterrupts();
	
	///
	/// Disable system interrupts.
	///
	static void DisableInterrupts();

	///
	///	Returns the current system ticks.
	///
	static U32 GetTickCount();

	///
	///	Returns the system standard output.
	///
	static IOutputStream& GetStandardOutput(){return *_out;}
};
