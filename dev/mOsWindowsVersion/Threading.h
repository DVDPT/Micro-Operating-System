#pragma once

#include "UtThread.h"
#include "DThread.h"
#include "Task.h"
#include "UtThread.cpp"

struct x86Context
{
	unsigned EDI;
	unsigned ESI;
	unsigned EBX;
	unsigned EBP;
	void (*Ret)();

	void SetThreadStartFunction(void (*ThreadStart)()){Ret = ThreadStart;}
};

typedef DThread<x86Context> Thread;
typedef UtTask<x86Context> Task;
