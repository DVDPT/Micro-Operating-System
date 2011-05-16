#pragma once
#include "KernelPort.h"

struct x86Context : public BaseUThreadContext
{
	unsigned EDI;
	unsigned ESI;
	unsigned EBX;
	unsigned EBP;
	void (*Ret)();

	void SetThreadStartFunction(void (*ThreadStart)())
	{
		x86Context* aaaa = this;
		Ret = ThreadStart;	
	}
};


class X86Scheduler : public BaseUScheduler<x86Context>
{
protected:
	virtual Void ContextSwitch(x86Context* const oldThreadContext, x86Context* const newThreadContext)
	{

	}
};




typedef BaseUThread<x86Context> Thread;
typedef UtTask<x86Context> Task;