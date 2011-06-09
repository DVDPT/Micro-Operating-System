#pragma once

#include "KernelPort.h"

struct ARMContext
{
	U32 r0;
	void (*Ret)();

	void SetThreadStartFunction(void (*ThreadStart)());
};

typedef BaseUScheduler<ARMContext> UScheduler;
typedef BaseUThread<ARMContext> Thread;

class ARMScheduler : public UScheduler
{
public:
	ARMScheduler();
protected:
	static Void FASTCALL ARMContextSwitch(Thread* oldThread, Thread* newThread);
};
