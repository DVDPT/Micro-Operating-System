#pragma once

#include "SystemTypes.h"

//No thuumb Context
struct ARMContext
{
	U32 r4,r5,r6,r7,r8,r9,r10,fp,r12;


	//U32 r14,r12,fp,r10,r9,r8,r7,r6,r5,r4;
	void (*lr)();
	void SetThreadStartFunction(void (*ThreadStart)())
	{
		r4 = 0x4;
		r5 = 0x5;
		fp = 0xA;
		r12 = 0xB;
		lr = ThreadStart;
	}
};
