#pragma once

#include "Threading.h"
#include "WaitBlock.h"

class Monitor
{
	WaitBlock _monitor;

public :
	static void Enter(Monitor& m);
	static void Exit(Monitor& m);
	static void Wait(Monitor& m,U32 timeout = TIMEOUT_INFINITE);
	static void Notify(Monitor& m);
	static void NotifyAll(Monitor& m);

	Monitor();
	~Monitor();

};
