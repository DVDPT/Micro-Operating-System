#pragma once

#include "ThreadingConfiguration.h"
#include "KernelTypes.h"
#include "BaseUtThread.h"

template <typename Context>
class UtTask : public BaseUtThread<Context>
{
	U8_P _stack[KERNEL_TASKS_STACK_SIZE];

public:
	UtTask()
		: 	BaseUtThread<Context>(_stack,KERNEL_TASKS_STACK_SIZE)
	{}

	UtTask(ThreadFunction func, ThreadArgument arg)
		:	BaseUtThread<Contex>(_stack,KERNEL_TASKS_STACK_SIZE,func,arg)
	{}
};