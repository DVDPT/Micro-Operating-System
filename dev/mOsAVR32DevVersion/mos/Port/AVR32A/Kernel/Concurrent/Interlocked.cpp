
#include "SystemTypes.h"
#include "Interlocked.h"
#include "System.h"

///
///
///
///	TODO: MAKE THIS CODE IN ASSEMBLY !!!!
///
///
///
///
///

extern "C"
{
	extern bool atomic_compare_exchange32(U32 volatile * addr, U32 value, U32 comparand);
	extern bool atomic_compare_exchange16(U16 volatile * addr, U16 value, U16 comparand);
	extern bool atomic_compare_exchange8(U8 volatile * addr, U8 value, U8 comparand);
}


U32 Interlocked::CompareExchange(volatile U32* addr, U32 value, U32 comparand)
{
	bool prevState = System::AcquireSystemLock();
	U32 ret;
	if((ret = *addr) == comparand)
		*addr = value;
	System::ReleaseSystemLock(prevState);
	return ret;
}

U16 Interlocked::CompareExchange(volatile U16* addr, U16 value, U16 comparand)
{
	bool prevState = System::AcquireSystemLock();
	U16 ret;
	if((ret = *addr) == comparand)
		*addr = value;
	System::ReleaseSystemLock(prevState);
	return ret;
}

U8 Interlocked::CompareExchange(volatile U8* addr, U8 value, U8 comparand)
{
	bool prevState = System::AcquireSystemLock();
	U8 ret;
	if((ret = *addr) == comparand)
		*addr = value;
	System::ReleaseSystemLock(prevState);
	return ret;
}


U32 Interlocked::Add(U32 * addr, U32 value)
{
	volatile U32 addrValue,sum;
	do
	{
		addrValue = *addr;

		sum = addrValue + value;

		if(CompareExchange(addr,sum,addrValue) == addrValue)
			return sum;

	}while(true);
}


