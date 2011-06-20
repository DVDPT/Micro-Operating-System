#pragma once

#include "SystemTypes.h"

//No thuumb Context
struct ARMContext
{
#define USER_MODE (1<<4)
#define INTERRUPTS_ENABLE (1<<7)
#define FIQ_ENABLE (1<<6)

	U32 flags,r4,r5,r6,r7,r8,r9,r10,fp,r12;

	void (*lr)();

	void SetThreadStartFunction(void (*ThreadStart)())
	{
		flags = INTERRUPTS_ENABLE | FIQ_ENABLE | USER_MODE	;
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
