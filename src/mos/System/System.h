#pragma once

#include "SystemTypes.h"

///
///	The System class is a facade for some basic system operations
///
class System
{
	
public:

	///
	///	This function ensures multiple exclusion through out the entire system
	///
	static void AcquireSystemLock();
	
	///
	///	Release the multiple exclusion
	///
	static void ReleaseSystemLock();

	///
	///	Returns the current system ticks
	///
	static U32 GetTickCount();
};
