#pragma once

#include "List.h"
#include "Threading.h"

class Mutex
{
	List<Thread> _waitingThreads;
	volatile Thread* _owner;
	volatile U32 _reentrantCalls;

public:

	Mutex(bool owner = false);

	bool Acquire(U32 timeout = TIMEOUT_INFINITE);

	bool IsLocked();

	void Release();
};
