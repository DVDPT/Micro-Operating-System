#pragma once



#include "List.h"
#include "Assert.h"
#include "Bits.h"
#include "System.h"
#include "KernelConstants.h"
#include "BaseUThread.h"
#include "UTask.h"

class BaseUScheduler
{

protected:
	///
	///	The prototype to the context switch function
	///
	typedef Void (FASTCALL *ContextSwitch)(BaseUThread* oldThread, BaseUThread* newThread);

private:
	///
	///	The array of ready queues supported by the kernel.
	///
	List<BaseUThread> _readyQueues[KERNEL_NR_OF_THREAD_PRIORITIES];

	///
	///	A bit map that indicates witch ready queues have threads.
	///
	U8 _queuesBitMap;

	///
	///	The current running thread
	///
	BaseUThread * _pRunningThread;
	
	///
	///	The main thread	descriptor
	///
	BaseUThread _mainThread;

	///
	///	The idle Thread descriptor
	///
	UTask _idleThread;

	///
	///	A function Pointer to the Context Switch
	///
	ContextSwitch _contextSwitch;

	///
	///	A pointer to the scheduler instance
	///
	static BaseUScheduler* _pScheduler;

	///
	///	The Scheduler lock counter
	///
	volatile U32 _schedulerLock;

	static Void IdleThreadRoutine();

	///
	///	Removes the thread passed as argument from its ready list
	///
	static Void RemoveThreadFromReadyQueue(BaseUThread& thread);

	///
	///	Inserts this thread passed as argument in its ready queue
	///
	static Void InsertThreadInReadyQueue(BaseUThread& thread);

	
	///
	///	Returns and removes from the ready list the next thread ready to run
	///		NOTE: this function always return a thread, because idle thread never blocks
	///
	static BaseUThread& DequeueNextReadyThread();

	///
	///	Returns the next ready thread.
	///		NOTE: this function always return a thread, because idle thread never blocks
	///
	static BaseUThread& PeekNextReadyThread();
	///
	///	Returns TRUE when there is a ready thread with a bigger priority than the running thread. Returns FALSE otherwise.
	///
	static BOOL HaveReadyThreads();

	///
	///	The scheduler function
	///
	static Void Schedule(BOOL locked);

	///
	///	Returns the current running thread
	///
	static BaseUThread& GetRunningThread();

	static U32 GetLockCount();

	static Void SetLockCount(U32 newlock);

	static Void lock();
	
	static Void unlock();
	 


protected:
	///
	///	A protected ctor so that only derived types can access it.
	///	_pRunningThread is initialized with the value of the main thread (the thread running this code)
	///
	BaseUScheduler(ContextSwitch contextSwitch);

	friend class BaseUThread;
};




