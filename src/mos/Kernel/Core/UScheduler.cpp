/*
 * BaseU_Scheduler.cpp
 *
 *  Created on: 10 de Jun de 2011
 *      Author: DVD
 */

#include "UScheduler.h"
#include "Debug.h"


UScheduler  UScheduler::_Scheduler;



///
///	A protected ctor so that only derived types can access it.
///	_pRunningThread is initialized with the value of the main thread (the thread running this code)
///
UScheduler::UScheduler()
	:
	_queuesBitMap(0), _mainThread(),_idleThread()

{
	_pRunningThread = &_mainThread;
	///
	///	Set idle thread priority and start it
	///
	_idleThread._threadPriority = KERNEL_THREAD_MINIMUM_PRIORITY;
	InsertThreadInReadyQueue(_idleThread);
}


void IdleThreadRoutine()
{
	while(true)
		UThread::Yield();
}

///
///	Removes the thread passed as argument from its ready list
///
void UScheduler::RemoveThreadFromReadyQueue(UThread& thread)
{
	if (&thread != _Scheduler._pRunningThread)
	{
		List<UThread>& list =
				_Scheduler._readyQueues[thread._threadPriority];
		list.Remove(&thread._node);

		if (list.IsEmpty())
			Bits<U8>::ClearBit(&_Scheduler._queuesBitMap,
					thread._threadPriority);
	}
}

///
///	Inserts this thread passed as argument in its ready queue
///
void UScheduler::InsertThreadInReadyQueue(UThread& thread)
{

	List<UThread >& list =
			_Scheduler._readyQueues[thread._threadPriority];

	bool wasEmpty = list.IsEmpty();

	list.Enqueue(&thread._node);

	if (wasEmpty)
		Bits<U8>::SetBit(&(_Scheduler._queuesBitMap), thread._threadPriority);
}

///
///	Returns and removes from the ready list the next thread ready to run
///		NOTE: this function always return a thread, because idle thread never blocks
///
UThread& UScheduler::DequeueNextReadyThread()
{
	UThread& nextThread = PeekNextReadyThread();
	RemoveThreadFromReadyQueue(nextThread);
	return nextThread;
}

///
///	Returns the next ready thread.
///		NOTE: this function always return a thread, because idle thread never blocks
///
UThread& UScheduler::PeekNextReadyThread()
{
	U32 queueIndex = Bits<U8>::GetLowestBitSet(_Scheduler._queuesBitMap);

	List<UThread>& list = _Scheduler._readyQueues[queueIndex];

	Node<UThread>* threadNode = list.GetFirst();
	return *(threadNode->GetValue());
}

///
///	Returns TRUE when there is a ready thread with a bigger priority than the running thread. Returns FALSE otherwise.
///
bool UScheduler::HaveReadyThreads()
{
	///
	///	Get the value of the next thread
	///
	UThread& nextThread = PeekNextReadyThread();
/*
	///
	///	Check if the next thread have a lower priority than the current thread, if so return FALSE
	///
	if (nextThread._threadPriority < GetRunningThread()._threadPriority)
		return false;

	return true;
	*/

	return &nextThread != &_Scheduler._idleThread;
}

///
///	The scheduler function
///
UThread& UScheduler::Schedule()
{

	UThread& nextThread = DequeueNextReadyThread();




	DebugExec(GetRunningThread().SetTimestamp(-1));

	nextThread.SetTimestamp(System::GetTickCount() + KERNEL_THREAD_TIME_SLICE);

	return nextThread;

}

///
///	Returns the current running thread
///
UThread& UScheduler::GetRunningThread()
{
	return *_Scheduler._pRunningThread;
}

U32 UScheduler::GetLockCount()
{
	return _Scheduler._schedulerLock;
}

void UScheduler::SetLockCount(U32 newlock)
{
	_Scheduler._schedulerLock = newlock;
}

void UScheduler::Lock()
{
	_Scheduler._schedulerLock++;
}

void UScheduler::Unlock()
{
	if(--_Scheduler._schedulerLock == 0)
	{
		UnlockInner(0);
	}
}

bool UScheduler::CanScheduleThreads()
{
	if(System::GetTickCount() >= _Scheduler._pRunningThread->_timestamp
			&& GetLockCount() == 0
			&& HaveReadyThreads())
	{
		return true;
	}
	return false;
}

bool UScheduler::IsLocked()
{
	return _Scheduler._schedulerLock == 0;
}

void UScheduler::UnlockInner(U32 lockCount)
{
	DebugAssertEquals(lockCount,GetLockCount());
	do
	{
		///
		///	If there are pending pisrs run them.
		///
		if(InterruptController::ArePisrsPending())
			InterruptController::RunPendingPisrs();
		else
		{

			///
			///	Get the next thread from the scheduler. And a reference to the current.
			///
			UThread& nextThread = Schedule();
			UThread& currentThread = *_Scheduler._pRunningThread;

			///
			/// Set the next thread as the running thread.
			///
			_Scheduler._pRunningThread = &nextThread;

			///
			///	Reset the lock count.
			///
			SetLockCount(0);

			///
			///	Switch threads
			///
			_Scheduler.ContextSwitch(&currentThread,&nextThread);


			DebugAssertEquals(GetLockCount(),0);

			///
			///	Set the scheduler lock with the value before the switch happened.
			///
			SetLockCount(lockCount);

			return;
		}

	}while(true);
}

void UScheduler::TrySwitchThread()
{
	if(HaveReadyThreads())
		SwitchThread();
}

void UScheduler::SwitchThread()
{
	UnlockInner(GetLockCount());
}

void UScheduler::SwitchContexts(Context ** trapContext)
{
	DebugAssertEquals(0,GetLockCount());
	DebugAssertTrue(CanScheduleThreads());

	UThread& next = Schedule();
	_Scheduler._pRunningThread = &next;

	*trapContext = next._context;

}

void UScheduler::SystemTimerInterruptRoutine(InterruptArgs* args, SystemIsrArgs sargs)
{
	if(CanScheduleThreads())
		SwitchContexts(args->InterruptContext);
}
