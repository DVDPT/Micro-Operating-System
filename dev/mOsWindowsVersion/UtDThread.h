#pragma once

#include "BaseUtThread.h"

template<typename Context>

class UtDThread : public BaseUtThread<Context>
{

public:
	UtDThread(Void_P stack, int size)
		: 	BaseUtThread<Context>(stack,size)
	{}

	UtDThread()
		:	BaseUtThread<Context>()
	{}
};