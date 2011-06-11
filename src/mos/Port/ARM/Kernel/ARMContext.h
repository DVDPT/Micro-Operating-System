#pragma once

#include "SystemTypes.h"

struct ARMContext
{
	U32 r0;
	void (*Ret)();

	void SetThreadStartFunction(void (*ThreadStart)())
	{
		Ret = ThreadStart;
	}
};
