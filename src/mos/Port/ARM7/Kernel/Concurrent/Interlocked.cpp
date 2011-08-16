
#include "SystemTypes.h"
#include "Interlocked.h"


extern "C"
{
	extern bool atomic_compare_exchange32(U32 volatile * addr, U32 value, U32 comparand);
	extern bool atomic_compare_exchange16(U16 volatile * addr, U16 value, U16 comparand);
	extern bool atomic_compare_exchange8(U8 volatile * addr, U8 value, U8 comparand);
}


bool Interlocked::CompareExchange(volatile U32* addr, U32 value, U32 comparand)
{
	return atomic_compare_exchange32(addr,value,comparand);
}

bool Interlocked::CompareExchange(volatile U16* addr, U16 value, U16 comparand)
{
	return atomic_compare_exchange16(addr,value,comparand);
}

bool Interlocked::CompareExchange(volatile U8* addr, U8 value, U8 comparand)
{
	return atomic_compare_exchange8(addr,value,comparand);
}


U32 Interlocked::Add(U32 * addr, U32 value)
{
	volatile U32 addrValue,sum;
	do
	{
		addrValue = *addr;

		sum = addrValue + value;

		if(CompareExchange(addr,sum,addrValue))
			return sum;

	}while(true);
}


