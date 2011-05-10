#pragma once

#include "BaseUtThread.h"
#include "UtDThread.h"
#include "Task.h"
#include "BaseUtThread.cpp"

struct x86Context
{
	unsigned EDI;
	unsigned ESI;
	unsigned EBX;
	unsigned EBP;
	void (*Ret)();

	void SetThreadStartFunction(void (*ThreadStart)()){Ret = ThreadStart;}
};

typedef BaseUtThread<x86Context> UtThread;
typedef UtDThread<x86Context> Thread;
typedef UtTask<x86Context> Task;
