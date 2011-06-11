#pragma once

#include "BaseUThread.h"
#include "SystemTypes.h"


class UTask : public BaseUThread
{
	U8_P _stack[KERNEL_TASKS_STACK_SIZE];

public:
	UTask()
		: 	BaseUThread(this->_stack,KERNEL_TASKS_STACK_SIZE)
	{}

	UTask(ThreadFunction func, ThreadArgument arg)
		:	BaseUThread(this->_stack,KERNEL_TASKS_STACK_SIZE,func,arg)
	{}
};
