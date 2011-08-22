#pragma once

#include "List.h"
#include "Threading.h"
#include "WaitBlock.h"

class Mutex
{
	WaitBlock _waitingThreads;
	volatile Thread* _owner;
	volatile U32 _reentrantCalls;

public:

	Mutex(bool owner = false);

	bool Acquire(U32 timeout = TIMEOUT_INFINITE);

	bool IsLocked();

	void Release();
};
