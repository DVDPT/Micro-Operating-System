#pragma once

#include "SystemTypes.h"

template <typename T>
class Bits
{
private:
	static U32 const MultiplyDeBruijnBitPosition[32];

public:
	static void ClearBit(T * position, T bitnumber)
	{
		*position = *position & (~(1 << bitnumber)); 
	}

	static void SetBit(T *  position, T bitnumber)
	{
		*position = *position | (1 << bitnumber);
	}

	static T SetBits(T position,T size)
	{
		U32 ones = -1;
		return ((ones >>(32-size))<< position);
	}

	static T SetBits(T size)
	{
		U32 ones = -1;
		return ((ones >>(32-size)));
	}

	static U32 GetLowestBitSet(U32 value)
	{
		value  &= -int(value);
		value  *= 0x077CB531;
		value >>= 27;
		return MultiplyDeBruijnBitPosition[value]; 
	}

	static T ModifyBit(T x, T position, T newState)
	{
		T mask = 1 << position;
		T state = T(newState);
		return (x & ~mask) | (-state & mask);
	}

	static T ModifyBits(T position, T newValue, T oldValue, T numberOfBits)
	{
		T mask = (numberOfBits<<position);
		T value = (oldValue & ~mask) | ((newValue<<position) & mask);
		return value;


	}

};
template <typename T>
U32 const Bits<T>::MultiplyDeBruijnBitPosition[32] = {
		0,  1, 28,  2, 29, 14, 24,  3, 30, 22, 20, 15, 25, 17,  4,  8,
		31, 27, 13, 23, 21, 19, 16,  7, 26, 12, 18,  6, 11,  5, 10,  9
};
