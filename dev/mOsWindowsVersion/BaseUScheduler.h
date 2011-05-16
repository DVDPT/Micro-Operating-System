#pragma once

#include "BaseUThread.h"
#include "KernelConfiguration.h"
#include "Assert.h"
#include "Bits.h"

template <typename Context>
class BaseUThread;

template<typename Context>
class BaseUScheduler
{


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
	///	The main thread	descriptor
	///
	BaseUThread<Context> _mainThread;
	
	///
	///	A pointer to the scheduler instance
	///
	static BaseUScheduler* _pScheduler;

	

	///
	///	Removes the thread passed as argument from its ready list
	///
	NOINLINE static Void RemoveThreadFromReadyQueue(BaseUThread<Context>& thread)
	{
		if(&thread != _pScheduler->_pRunningThread)
		{
			List<BaseUThread<Context>> list = _pScheduler->_readyQueues[thread._threadPriority];
			list.Remove(&thread._node);
			
			if(list.IsEmpty())
				Bits<U8>::ClearBit(&_pScheduler->_queuesBitMap, thread._threadPriority);
		}
	}

	///
	///	Inserts this thread passed as argument in its ready queue
	///
	NOINLINE static Void InsertThreadInReadyQueue(BaseUThread<Context>& thread)
	{
		Assert::NotEquals(&thread,_pScheduler->_pRunningThread);
		
		List<BaseUThread<Context>> list =  _pScheduler->_readyQueues[thread._threadPriority]; 
		
		BOOL wasEmpty = list.IsEmpty();
		
		list.Enqueue(&thread._node);

		if(wasEmpty)
			Bits<U8>::SetBit(&(_pScheduler->_queuesBitMap), thread._threadPriority);
	}

	///
	///	Returns the next thread ready to run
	///
	NOINLINE static BaseUThread<Context>& GetNextReadyThread()
	{
		U32 queueIndex = Bits<U8>::GetLowestBitSet(_pScheduler->_queuesBitMap);
		return *(_pScheduler->_readyQueues[queueIndex].Dequeue()->GetValue());
	}

	///
	///	The scheduler function
	///
	NOINLINE static Void Schedule(BOOL locked)
	{
		///
		///	Acquire the System lock to safely manipulate the queues
		///

		if(!locked)
			System::AcquireSystemLock();

		BaseUThread<Context>& currentThread = GetRunningThread();
		BaseUThread<Context>& nextThread = GetNextReadyThread();

		System::ReleaseSystemLock();
		///
		///	Check if the next and current thread are the same to avoid a context switch
		///
		if(currentThread != nextThread)
			_pScheduler->ContextSwitch(current._contextThread, next._contextThread);
	}

	///
	///	Returns the current running thread
	///
	static BaseUThread<Context>& GetRunningThread()
	{
		return *_pScheduler->_pRunningThread;
	}

	
	 


protected:

	///
	///	This functions is responsible by the context switching
	///
	NOINLINE virtual Void ContextSwitch(Context* const oldThreadContext, Context* const newThreadContext) = 0;

	///
	///	A protected ctor so that only derived types can access it
	///
	NOINLINE BaseUScheduler()
		:	
		_queuesBitMap(0),
		_mainThread(),
		_pRunningThread(&_mainThread)

	{
		
		_pScheduler = this;
		
	}


	friend BaseUThread<Context>;
};

template<typename Context>
BaseUScheduler<Context>*  BaseUScheduler<Context>::_pScheduler = NULL;



