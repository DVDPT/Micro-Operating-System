#pragma once

#include "KernelConfiguration.h"
#include "KernelTypes.h"
#include "BaseUThread.h"

template <typename Context>
class UtTask : public BaseUThread<Context>
{
	U8_P _stack[KERNEL_TASKS_STACK_SIZE];

public:
	UtTask()
		: 	BaseUThread<Context>(this->_stack,KERNEL_TASKS_STACK_SIZE)
	{}

	UtTask(ThreadFunction func, ThreadArgument arg)
		:	BaseUThread<Contex>(this->_stack,KERNEL_TASKS_STACK_SIZE,func,arg)
	{}
};