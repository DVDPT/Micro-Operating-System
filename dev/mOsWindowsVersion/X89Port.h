#include "KernelPort.h"

struct x86Context
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

X86Scheduler _scheduler;
template <typename Context>

const BaseUScheduler<Context>& BaseUScheduler<Context>::_pScheduler = _scheduler;


typedef BaseUThread<x86Context> Thread;
typedef UtTask<x86Context> Task;