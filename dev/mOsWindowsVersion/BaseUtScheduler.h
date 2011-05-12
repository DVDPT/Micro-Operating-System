#pragma once

#include "BaseUtThread.h"

template <typename Context>
class BaseUThread;

template<typename Context>
class BaseUScheduler
{
	///
	///	A constant defining the number of priorities that a thread can have.
	///
#define KERNEL_NR_OF_THREAD_PRIORITIES (8)

	///
	///	The array of ready queues supported by the kernel.
	///
	List<BaseUThread<Context>> _readyQueues[KERNEL_NR_OF_THREAD_PRIORITIES]; 

	///
	///	A bit map that indicates witch ready queues have threads.
	///
	U8 _queuesBitMap;

	///
	///	The current running thread
	///
	BaseUThread<Context> * _pRunningThread;
	
	///
	///	A pointer to the scheduler instance
	///
	static const BaseUScheduler& _pScheduler;

	///
	///	The schedule function
	///
	static Void Schedule()
	{

	}

	///
	///	
	///

	///
	///	Returns the current running thread
	///
	static BaseUThread<Context>& GetRunningThread()
	{
		return *_pScheduler._pRunningThread;
	}

	
	 


protected:

	///
	///	This functions is responsible by the context switching
	///
	virtual Void ContextSwitch(Context* const oldThreadContext, Context* const newThreadContext) = 0;

	///
	///	A protected ctor so that only derived types can access it
	///
	BaseUScheduler()
		:	
	_queuesBitMap(0),
		_pRunningThread(NULL)
	{}


	friend BaseUThread<Context>;
};