#pragma once



#include "List.h"
#include "Assert.h"
#include "Bits.h"
#include "System.h"
#include "KernelConstants.h"
#include "UThread.h"
#include "UTask.h"
#include "InterruptController.h"
#include "SystemConfiguration.h"

class UScheduler
{

	///
	///	The purpose of this class is to handle the timeout when a thread is blocked.
	///
	class Timer
	{

		///
		///	General purpose node.
		///
		Node<Timer> _node;

		///
		///	The thread that created this timer.
		///
		UThread& _thread;

		///
		///	The operation timeout time.
		///
		U64 _timeoutTime;




	public:

		Timer(UThread& thread) : _thread(thread){ _node.SetValue(this);}

		///
		///	Shedules this thread to be awake when timeout has passed.
		///
		void SetTimeout(U32 timeout);

		///
		///	Returns if the operation timed out.
		///
		bool HasTimedout();

		///
		///	Wake up the thread.
		///
		void Trigger();

		///
		///	Disables this timer.
		///
		void Disable();

		///
		///	Returns the timeout time.
		///
		U64 GetTimeoutTime(){ return _timeoutTime; }

		///
		///	The destructor of this instance, disables the timer.
		///
		~Timer(){ Disable(); }
	};

	///
	///	The array of ready queues supported by the kernel.
	///
	List<UThread> _readyQueues[KERNEL_THREAD_NR_OF_PRIORITIES];

	///
	///	An array of threads waiting for an event with timeout.
	///
	List<Timer> _waitingQueue;

	///
	///	A bit map that indicates witch ready queues have threads.
	///
	U8 _queuesBitMap;

	///
	///	The current running thread.
	///
	volatile UThread * _pRunningThread;
	
	///
	///	The main thread	descriptor.
	///
	UThread _mainThread;

	///
	///	The idle Thread descriptor.
	///
	UTask _idleThread;

	///
	///	The Scheduler lock counter
	///
	volatile U32 _schedulerLock;

	///
	///	The singleton instance of the scheduler
	///
	static  UScheduler _Scheduler;

	///
	///	The routine that the idle thread will be running.
	///
	static void IdleThreadRoutine();

	///
	///	The system timer interrupt service routine, this function is responsable
	///	to do the context switch inside an isr if possible.
	///
	CRITICAL_OPERATION static IsrCompletationStatus SystemTimerInterruptRoutine(InterruptArgs* args, SystemIsrArgs sargs);

	///
	///	The system timer post interrupt service routine. this function is responsable
	///	to wake up threads that are in an EVENT state.
	///
	CRITICAL_OPERATION static void SystemTimerPostInterruptRoutine(SystemPisrArgs args);

	///
	///	Removes the thread passed as argument from its ready list
	///
	CRITICAL_OPERATION static void RemoveThreadFromReadyQueue(UThread& thread);

	///
	///	Inserts this thread passed as argument in its ready queue
	///
	CRITICAL_OPERATION static void InsertThreadInReadyQueue(UThread& thread);
	
	///
	///	Renews this thread timestamp.
	///
	static void RenewThread(UThread& thread);

	///
	///	Returns and removes from the ready list the next thread ready to run
	///		NOTE: this function always return a thread, because idle thread never blocks
	///
	CRITICAL_OPERATION static UThread& DequeueNextReadyThread();

	///
	///	Returns the next ready thread.
	///		NOTE: this function always return a thread, because idle thread never blocks
	///
	CRITICAL_OPERATION static UThread* PeekNextReadyThread();

	///
	///	Returns TRUE when there is a ready thread with a bigger priority than the running thread. Returns FALSE otherwise.
	///
	CRITICAL_OPERATION static bool HaveReadyThreads();

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
	CRITICAL_OPERATION static UThread& Schedule();
	///
	///	Returns the current running thread
	///
	static UThread& GetRunningThread();

	///
	///	Returns true if the thread timestamp was already consumed, false otherwise.
	///
	static bool HasCurrentThreadTimestampPassed();

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
	CRITICAL_OPERATION static void UnlockInner(U32 lockCount);

	///
	///	Adds to the waiting queue the @operation. This timer will
	///	be triggered when the timeout is reached.
	///
	static void AddOperationWithTimeout(Node<Timer>& operation);

	///
	///	UThread class can access private UScheduler members
	///
	friend class UThread;

	friend class SystemConfiguration;

	friend class InterruptController;

	///
	///	Performs context switch this function is not implemented by the kernel core
	///		for porting reasons
	///
	CRITICAL_OPERATION PORT_SPECIFIC NAKED static void ContextSwitch(UThread * old, UThread * next);


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

	///
	///	Sets the lock count
	///
	static void SetLockCount(U32 newlockCount);

};




