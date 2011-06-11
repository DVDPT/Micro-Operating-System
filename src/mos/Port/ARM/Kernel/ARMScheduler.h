#pragma once

#include "Threading.h"
#include "SystemTypes.h"





class ARMScheduler : public BaseUScheduler
{
public:
	ARMScheduler();
protected:
	static Void ARMContextSwitch(Thread* oldThread, Thread* newThread);
};
