/*
 * Assert.cpp
 *
 *  Created on: 9 de Jun de 2011
 *      Author: DVD
 */

#include "Assert.h"
#include "System.h"
void Assert::NotEquals(void * expected, void * value)
{
	if(&expected == &value)
	{
		System::GetStandardOutput().Write("Assert not equals failed.");
		for(;;);
	}
}

void Assert::Equals(void * expected, void* value)
{
	if((U32)expected != (U32)value)
	{
		System::GetStandardOutput().Write("Assert equals failed.");
		for(;;);
	}
}

void Assert::Equals(U32 expected, U32 value)
{
	if(expected != value)
	{
		System::GetStandardOutput().Write("Assert equals failed.");
		for(;;);
	}
}

void Assert::True(bool expr)
{
	if(!expr)
	{
		System::GetStandardOutput().Write("Assert true equals failed.");
		for(;;);
	}
}

void Assert::Error(const char * msg)
{
	System::GetStandardOutput().Write("Assert error failed.");
	for(;;);
}


