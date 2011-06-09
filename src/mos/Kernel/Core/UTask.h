#pragma once

#include "KernelConfiguration.h"
#include "SystemTypes.h"
#include "BaseUThread.h"

template <typename Context>
class UTask : public BaseUThread<Context>
{
	U8_P _stack[KERNEL_TASKS_STACK_SIZE];

public:
	UTask()
		: 	BaseUThread<Context>(this->_stack,KERNEL_TASKS_STACK_SIZE)
	{}

	UTask(ThreadFunction func, ThreadArgument arg)
		:	BaseUThread<Context>(this->_stack,KERNEL_TASKS_STACK_SIZE,func,arg)
	{}
};