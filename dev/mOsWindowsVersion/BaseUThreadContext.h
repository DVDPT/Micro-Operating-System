#pragma once

#include "SystemTypes.h"

class BaseUThreadContext
{

protected:
	BaseUThreadContext();

public:
	typedef void (*ThreadStartRoutine)();

	virtual Void SetThreadStartFunction(ThreadStartRoutine start) = 0;
};