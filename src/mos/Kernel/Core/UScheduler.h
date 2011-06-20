#pragma once



#include "List.h"
#include "Assert.h"
#include "Bits.h"
#include "System.h"
#include "KernelConstants.h"
#include "UThread.h"
#include "UTask.h"

class UScheduler
{


private:
	///
	///	The array of ready queues supported by the kernel.
	///
	List<UThread> _readyQueues[KERNEL_NR_OF_THREAD_PRIORITIES];

	///
	///	A bit map that indicates witch ready queues have threads.
	///
	U8 _queuesBitMap;

	///
	///	The current running thread
	///
	UThread * _pRunningThread;
	
	///
	///	The main thread	descriptor
	///
	UThread _mainThread;

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
	static UScheduler _Scheduler;


	static void IdleThreadRoutine();

	///
	///	Removes the thread passed as argument from its ready list
	///
	static void RemoveThreadFromReadyQueue(UThread& thread);

	///
	///	Inserts this thread passed as argument in its ready queue
	///
	static void InsertThreadInReadyQueue(UThread& thread);

	
	///
	///	Returns and removes from the ready list the next thread ready to run
	///		NOTE: this function always return a thread, because idle thread never blocks
	///
	static UThread& DequeueNextReadyThread();

	///
	///	Returns the next ready thread.
	///		NOTE: this function always return a thread, because idle thread never blocks
	///
	static UThread& PeekNextReadyThread();
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
	static UThread& GetRunningThread();

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
	friend class UThread;

	///
	///	Performs context switch this function is not implemented by the kernel core
	///		for porting reasons
	///
	NAKED static void ContextSwitch(UThread * old, UThread * next);


	///
	///	public constructor to be
	///
	UScheduler();

};




