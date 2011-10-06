#pragma once

#include "SystemTypes.h"
class Assert
{
public:

	static void NotEquals(void * expected, void * value);

	static void Equals(void * expected, void* value);

	template <class T>
	static void Equals(T expected, T value){ Equals((void*)expected,(void*)value); }

	template <class T>
	static void NotEquals(T expected, T value){ NotEquals((void*)expected,(void*)value); }

	static void Equals (U32 expected, U32 value);

	static void Equals (U16 expected, U16 value){ Equals((U32)expected,(U32)value); }

	static void Equals (U8 expected, U8 value){ Equals((U32)expected,(U32)value); }

	static void True(bool expr);

	static void False(bool expr) { True(!expr); }

	static void Error(char * msg = ""){ Error((const char*)msg); }

	static void Error(const char * msg = "");

	static void Fail(){ for(;;); }



};
