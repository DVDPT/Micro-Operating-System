#pragma once

#include "UThread.h"
#include "SystemTypes.h"


class UTask : public UThread
{
	U8_P _stack[KERNEL_TASKS_STACK_SIZE];

public:
	UTask()
		: 	UThread(this->_stack,KERNEL_TASKS_STACK_SIZE)
	{}

	UTask(ThreadFunction func, ThreadArgument arg)
		:	UThread(this->_stack,KERNEL_TASKS_STACK_SIZE,func,arg)
	{}
};
