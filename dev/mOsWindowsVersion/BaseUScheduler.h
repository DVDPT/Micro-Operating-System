#pragma once

#include "KernelConfiguration.h"
#include "Assert.h"
#include "Bits.h"

template <typename Context>
class BaseUThread;


template <typename Context>
class UTask;

template<typename Context>
class BaseUScheduler
{

protected:
	///
	///	The prototype to the context switch function
	///
	typedef Void (FASTCALL *ContextSwitch)(BaseUThread<Context>* oldThread, BaseUThread<Context>* newThread);

private:
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
	///	The idle Thread descriptor
	///
	UTask<Context> _idleThread;

	///
	///	A function Pointer to the Context Switch
	///
	ContextSwitch _contextSwitch;
	///
	///	A pointer to the scheduler instance
	///
	static BaseUScheduler* _pScheduler;

	NOINLINE static Void IdleThreadRoutine()
	{

	}

	///
	///	Removes the thread passed as argument from its ready list
	///
	NOINLINE static Void RemoveThreadFromReadyQueue(BaseUThread<Context>& thread)
	{
		if(&thread != _pScheduler->_pRunningThread)
		{
			List<BaseUThread<Context>>& list = _pScheduler->_readyQueues[thread._threadPriority];
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

		List<BaseUThread<Context>>& list =  _pScheduler->_readyQueues[thread._threadPriority]; 
		
		BOOL wasEmpty = list.IsEmpty();
		
		list.Enqueue(&thread._node);

		if(wasEmpty)
			Bits<U8>::SetBit(&(_pScheduler->_queuesBitMap), thread._threadPriority);
	}

	

	///
	///	Returns and removes from the ready list the next thread ready to run
	///		NOTE: this function always return a thread, because idle thread never blocks
	///
	NOINLINE static BaseUThread<Context>& DequeueNextReadyThread()
	{
		BaseUThread<Context>& nextThread = PeekNextReadyThread();
		RemoveThreadFromReadyQueue(nextThread);
		return nextThread;
	}

	///
	///	Returns the next ready thread.
	///		NOTE: this function always return a thread, because idle thread never blocks
	///
	NOINLINE static BaseUThread<Context>& PeekNextReadyThread()
	{
		U32 queueIndex = Bits<U8>::GetLowestBitSet(_pScheduler->_queuesBitMap);

		List<BaseUThread<Context>>& list =  _pScheduler->_readyQueues[queueIndex];
		
		Node<BaseUThread<Context>>* threadNode = list.GetFirst();
		return *(threadNode->GetValue());
	}



	///
	///	Returns TRUE when there is a ready thread with a bigger priority than the running thread. Returns FALSE otherwise.
	///
	NOINLINE static BOOL HaveReadyThreads()
	{
		///
		///	Get the value of the next thread
		///
		BaseUThread<Context>& nextThread = PeekNextReadyThread();
		
		///
		///	Check if the next thread have a lower priority than the current thread, if so return FALSE
		///
		if(nextThread._threadPriority > GetRunningThread()._threadPriority)
			return FALSE;

		return TRUE;
	}

	///
	///	The scheduler function
	///
	NOINLINE static Void Schedule(BOOL locked)
	{

		///
		///	Check if there are ready threads to run
		///
		if(!HaveReadyThreads())
		{
			if(locked)	
				System::ReleaseSystemLock();
			
			return;
		}
			
		///
		///	Acquire the System lock to safely manipulate the queues
		///
		if(!locked)
			System::AcquireSystemLock();

		BaseUThread<Context>& currentThread = GetRunningThread();
		BaseUThread<Context>& nextThread = DequeueNextReadyThread();
		
		BaseUThread<Context>* p1 = _pScheduler->_pRunningThread;
		p1 = &currentThread;


		_pScheduler->_pRunningThread = &nextThread;

		System::ReleaseSystemLock();

		_pScheduler->_contextSwitch(&currentThread, &nextThread);
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
	///	A protected ctor so that only derived types can access it.
	///	_pRunningThread is initialized with the value of the main thread (the thread running this code)
	///
	NOINLINE BaseUScheduler(ContextSwitch contextSwitch)
		:	
		_queuesBitMap(0),
		_mainThread(),
		_pRunningThread(&_mainThread),
		_idleThread(),
		_contextSwitch(contextSwitch)

	{
		///
		///	Register the scheduler instance so it can be used on static methods
		///
		_pScheduler = this;
		
		///
		///	Set idle thread priority and start it
		///
		_idleThread.SetThreadPriority(KERNEL_MINIMUM_THREAD_PRIORITY);
		InsertThreadInReadyQueue(_idleThread);
		
		
	}


	friend BaseUThread<Context>;
};

template<typename Context>
BaseUScheduler<Context>*  BaseUScheduler<Context>::_pScheduler = NULL;



