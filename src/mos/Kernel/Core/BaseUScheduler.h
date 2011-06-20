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
	///	The Scheduler lock counter
	///
	volatile U32 _schedulerLock;

	///
	///	The singleton instance of the scheduler
	///
	static BaseUScheduler _Scheduler;


	static void IdleThreadRoutine();

	///
	///	Removes the thread passed as argument from its ready list
	///
	static void RemoveThreadFromReadyQueue(BaseUThread& thread);

	///
	///	Inserts this thread passed as argument in its ready queue
	///
	static void InsertThreadInReadyQueue(BaseUThread& thread);

	
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
	static void Schedule(BOOL locked);

	///
	///	Returns the current running thread
	///
	static BaseUThread& GetRunningThread();

	///
	///	Returns the current lock count
	///
	static U32 GetLockCount();

	///
	///	Sets the lock count
	///
	static void SetLockCount(U32 newlock);

	///
	///	Disables context switching
	///
	static void lock();
	
	///
	///	Enables context switching if possible
	///
	static void unlock();
	 

	///
	///	BaseUThread class can access private BaseUScheduler members
	///
	friend class BaseUThread;

	///
	///	Performs context switch this function is not implemented by the kernel core
	///		for porting reasons
	///
	NAKED static void ContextSwitch(BaseUThread * old, BaseUThread * next);


	///
	///	public constructor to be
	///
	BaseUScheduler();

};




