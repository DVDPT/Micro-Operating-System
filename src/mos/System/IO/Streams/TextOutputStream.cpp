/*
 * BaseOutputStream.cpp
 *
 *  Created on: Aug 12, 2011
 *      Author: DVD
 */

#include "TextOutputStream.h"
#include "System.h"







void TextOutputStream::Write(U16 data)
{
	Write((U32)data);
}

void TextOutputStream::Write(U32 data)
{

	U8 buf[MAX_U32_NUMBERS];

	int i = 0;
	for(int number = 0; data!=0; ++i)
	{
			number = data % 10;
			data /= 10;
			buf[i] = number + ZERO_CHARACTER ;
	}

	DebugAssertTrue(i <= MAX_U32_NUMBERS);


	bool prevLock = System::AcquireSystemLock();

	for(i-=1 ; i>-1 ; i--)
		///
		///	This cast is to garantee that the right method is called.
		///		because C++ spec hides the Write(U8) and promotes
		///		the (U8)data to S32.
		///
		((IOutputStream*)this)->Write(buf[i]);

	System::ReleaseSystemLock(prevLock);

}

void TextOutputStream::Write(const char* str)
{
	bool prevLock = System::AcquireSystemLock();
	while(*str)
	{
		Write(*str++);
	}
	System::ReleaseSystemLock(prevLock);
}

void TextOutputStream::Write(S8 data)
{
	((IOutputStream*)this)->Write((U8)data);
}

void TextOutputStream::Write(S16 value)
{
	Write((S32)value);
}

void TextOutputStream::Write(S32 value)
{
	bool prevLock = System::AcquireSystemLock();
	if(value < 0)
	{
		((IOutputStream*)this)->Write(MINUS_CHARACTER);
		value = (-1 - (value) +1);
	}
	Write((U32)(value));
	System::ReleaseSystemLock(prevLock);
}
