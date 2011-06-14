#pragma once

#include "Threading.h"
#include "SystemTypes.h"





class ARMScheduler : public BaseUScheduler
{

public:
	ARMScheduler();
protected:
	static void ARMContextSwitch(Thread* oldThread, Thread* newThread);

};

extern ARMScheduler armscheduler;
