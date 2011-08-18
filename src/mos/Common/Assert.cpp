/*
 * Assert.cpp
 *
 *  Created on: 9 de Jun de 2011
 *      Author: DVD
 */

#include "Assert.h"

void Assert::NotEquals(void * expected, void * value)
{
	if(&expected == &value)
		for(;;);
}

void Assert::Equals(void * expected, void* value)
{
	if((U32)expected != (U32)value)
		for(;;);
}

void Assert::Equals(U32 expected, U32 value)
{
	if(expected != value)
		for(;;);
}

void Assert::True(bool expr)
{
	if(!expr)
		for(;;);
}

void Assert::Error(const char * msg)
{
	for(;;);
}


