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
	static Void AcquireSystemLock();
	
	///
	///	Release the multiple exclusion
	///
	static Void ReleaseSystemLock();
};