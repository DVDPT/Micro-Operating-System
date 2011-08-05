#pragma once



#include "List.h"
#include "Assert.h"
#include "Bits.h"
#include "System.h"
#include "KernelConstants.h"
#include "UThread.h"
#include "UTask.h"
#include "InterruptController.h"

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
	static bool HaveReadyThreads();

	///
	///	This function switches the the current thread if there are other threads to run.
	///
	static void TrySwitchThread();

	///
	///	Always switch the current thread to another one.
	///
	static void SwitchThread();

	///
	///	The scheduler function is responsible for returning the next fit thread to run.
	///
	static UThread& Schedule();
	///
	///	Returns the current running thread
	///
	static UThread& GetRunningThread();

	///
	///	This functions returns TRUE when the current thread timeslice is over, the lock is free and there are new threads available.
	///
	static bool CanScheduleThreads();

	///
	///	Switch the context @trapContext to the next ready thread context.
	///		This is an auxiliary function to switch threads in a ISR.
	///		Only system functions should call this method.
	///
	static void SwitchContexts(Context ** trapContext);

	///
	///	This function must not be called outside the Scheduler. Switch the current thread.
	///
	static void UnlockInner(U32 lockCount);

	///
	///	BaseUThread class can access private BaseUScheduler members
	///
	friend class UThread;

	///
	///	Performs context switch this function is not implemented by the kernel core
	///		for porting reasons
	///
	PORT_SPECIFIC NAKED static void ContextSwitch(UThread * old, UThread * next);


	///
	///	private constructor so that only this class can create instances of Scheduler
	///
	UScheduler();



public:
	///
	///	Returns the current lock count
	///
	static U32 GetLockCount();

	///
	///	Sets the lock count
	///
	static void SetLockCount(U32 newlockCount);

	///
	///	Disables context switching
	///
	static void Lock();

	///
	///	Enables context switching if possible
	///
	static void Unlock();

	///
	///	Returns if the scheduler lock is locked
	///
	static bool IsLocked();
};




