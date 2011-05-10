#pragma once

#include "UtThread.h"

template<typename Context>

class DThread : public UtThread<Context>
{

public:
	DThread(Void_P stack, int size)
		: 	UtThread<Context>(stack,size)
	{}

	DThread()
		:	UtThread<Context>()
	{}
};