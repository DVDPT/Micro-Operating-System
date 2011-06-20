#pragma once

#include "SystemTypes.h"

//No thuumb Context
struct ARMContext
{
	U32 r4,r5,r6,r7,r8,r9,r10,fp,r12;

	void (*lr)();

	void SetThreadStartFunction(void (*ThreadStart)())
	{
		r4  = 0x1111111;
		r5  = 0x2222222;
		r6  = 0x3333333;
		r7  = 0x4444444;
		r8  = 0x5555555;
		r9  = 0x6666666;
		r10 = 0x7777777;
		fp  = 0x8888888;
		r12 = 0x9999999;
		lr = ThreadStart;
	}
};
