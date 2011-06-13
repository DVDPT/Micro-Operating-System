#pragma once

#include "Threading.h"
#include "SystemTypes.h"





class ARMScheduler : public BaseUScheduler
{

public:
	static ARMScheduler* _scheduler;
	ARMScheduler();
protected:
	static Void ARMContextSwitch(Thread* oldThread, Thread* newThread);
};
