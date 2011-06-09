#pragma once
#include "KernelPort.h"



struct X86Context 
{
	unsigned EDI;\
	unsigned ESI;
	unsigned EBX;
	unsigned EBP;
	void (*Ret)();


	void SetThreadStartFunction(void (*ThreadStart)())
	{
		X86Context* aaaa = this;
		EDI = 0x11111111;
		ESI = 0x22222222;
		EBX = 0x33333333;
		EBP = 0x44444444;
		Ret = ThreadStart;	
	}
};


typedef BaseUThread<X86Context> Thread;
typedef UTask<X86Context> Task;


class X86Scheduler : public BaseUScheduler<X86Context>
{
public:
	X86Scheduler();
protected:
	static Void FASTCALL X86ContextSwitch(Thread* oldThread, Thread* newThread);
};



