#pragma once

#include "SystemTypes.h"

template <typename T>
class Bits
{
private:
	static U32 MultiplyDeBruijnBitPosition[32];

public:
	static Void ClearBit(T * position, T bitnumber)
	{
		*position = *position & (~(1 << bitnumber)); 
	}

	static Void SetBit(T *  position, T bitnumber)
	{
		*position = *position | (1 << bitnumber);
	}

	static U32 GetLowestBitSet(T value)
	{
		value  &= -int(value);
		value  *= 0x077CB531;
		value >>= 27;
		return MultiplyDeBruijnBitPosition[value]; 
	}

};
template <typename T>
U32 Bits<T>::MultiplyDeBruijnBitPosition[32] = {
		0,  1, 28,  2, 29, 14, 24,  3, 30, 22, 20, 15, 25, 17,  4,  8,
		31, 27, 13, 23, 21, 19, 16,  7, 26, 12, 18,  6, 11,  5, 10,  9
	};