#pragma once

#include "BaseUtThread.h"

template<typename Context>

class UtDThread : public BaseUThread<Context>
{

public:
	UtDThread(Void_P stack, int size)
		: 	BaseUThread<Context>(stack,size)
	{}

	UtDThread()
		:	BaseUThread<Context>()
	{}
};