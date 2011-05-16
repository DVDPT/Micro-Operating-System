#pragma once

#include "KernelPort.h"

class KernelController
{
	Task _idleThread;

	static Void IdleThreadRoutine();
public:
	KernelController();

};
