#pragma once

#include "System.h"
template <typename T>
class Interlocked
{
public:
	static NOINLINE T CompareExchange(volatile T * location, T value, T comparand)
	{
		System::AcquireSystemLock();

		T locationValue = *location;

		if(locationValue == comparand)
			*location = value;
		
		System::ReleaseSystemLock();

		return locationValue;

		
	}
};