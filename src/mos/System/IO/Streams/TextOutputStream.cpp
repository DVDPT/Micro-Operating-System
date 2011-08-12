/*
 * BaseOutputStream.cpp
 *
 *  Created on: Aug 12, 2011
 *      Author: DVD
 */

#include "TextOutputStream.h"

#define MAX_U32_NUMBERS (10)
#define ZERO_CHARACTER ('0')
#define MINUS_CHARACTER ('-')

#define SHORT_SIGNAL_BIT (15)
#define INT_SIGNAL_BIT (31)

#define CONVERT_TO_UNSIGNED(value) ((-1 - (value)) +1)
#define CHECK_IF_IS_NEGATIVE(value) \
if(value == 0)	\
	{ \
		((IOutputStream*)this)->Write(ZERO_CHARACTER); \
		value = CONVERT_TO_UNSIGNED(value); \
		return; \
	} \



void TextOutputStream::Write(U16 data)
{
	Write((U32)data);
}

void TextOutputStream::Write(U32 data)
{
	CHECK_IF_IS_NEGATIVE(data);

	U8 buf[MAX_U32_NUMBERS];

	int i = 0;
	for(int number = 0; data!=0; ++i)
	{
			number = data % 10;
			data /= 10;
			buf[i++] = number + ZERO_CHARACTER ;
	}

	DebugAssertTrue(i <= MAX_U32_NUMBERS);

	for(i-=1 ; i>-1 ; i--)
		///
		///	This cast is to garantee that the right method is called.
		///		because C++ spec hides the Write(U8) and promotes
		///		the (U8)data to S32.
		///
		((IOutputStream*)this)->Write(buf[i]);
}

void TextOutputStream::Write(const char* str)
{
	while(*str)
	{
		Write(*str++);
	}
}

void TextOutputStream::Write(S8 data)
{
	((IOutputStream*)this)->Write((U8)data);
}

void TextOutputStream::Write(S16 data)
{
	CHECK_IF_IS_NEGATIVE(data);
	Write((U32)(-1 - data));
}

void TextOutputStream::Write(S32 data)
{
	CHECK_IF_IS_NEGATIVE(data);

	Bits<S32>::ClearBit(&data,INT_SIGNAL_BIT);
	Write((U32)(data));
}
