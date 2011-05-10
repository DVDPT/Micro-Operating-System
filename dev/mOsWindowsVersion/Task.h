#pragma once

#include "ThreadingConfiguration.h"
#include "KernelTypes.h"
#include "UtThread.h"

template <typename Context>
class UtTask : public UtThread<Context>
{
	U8_P _stack[KERNEL_TASKS_STACK_SIZE];

public:
	UtTask()
		: 	UtThread<Context>(_stack,KERNEL_TASKS_STACK_SIZE)
	{}

	UtTask(ThreadFunction func, ThreadArgument arg)
		:	UtThread<Contex>(_stack,KERNEL_TASKS_STACK_SIZE,func,arg)
	{}
};