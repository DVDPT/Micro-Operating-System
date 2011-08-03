#pragma once

#include "SystemTypes.h"
#include "KernelConfig.h"





class Interlocked
{

public:

	static bool CompareExchange(volatile U8 * location, U8 value, U8 comparand);
	static bool CompareExchange(volatile U16 * location, U16 value, U16 comparand);
	static bool CompareExchange(volatile U32 * location, U32 value, U32 comparand);

	template <typename T>
	static bool CompareExchange(T* location, T value, T comparand)
	{

		return CompareExchange((volatile U32*)location,(U32)value,(U32)comparand);
	}

	static U32 Add(U32* location, U32 value);


	static U32 Subtract(U32* location, U32 value)
	{
		return Add(location,-value);
	}

	static U32 Increment(U32* location)
	{
		return Add(location,1);
	}

	static U32 Decrement(U32*location)
	{
		return Add(location,-1);
	}

};
