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
	_queuesBitMap(0), _mainThread(),_idleThread((ThreadFunction)UScheduler::IdleThreadRoutine)

{
	_pRunningThread = &_mainThread;
	///
	///	Set idle thread priority and start it
	///
	_idleThread._threadPriority = KERNEL_THREAD_MINIMUM_PRIORITY;
	InsertThreadInReadyQueue(_idleThread);
}


void UScheduler::IdleThreadRoutine()
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
	if(thread._node.IsInList())
		return;

	thread.SetThreadState(UThread::READY);

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


	///
	///	if the list is empty is because all the threads are Waiting or in Event.
	///
	if(list.IsEmpty())
	{
		DebugAssertEquals(0,queueIndex);
		return _Scheduler._idleThread;
	}

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
	///
	///	Check if the next thread have a lower priority than the current thread, if so return FALSE
	///
	if (nextThread._threadPriority < GetRunningThread()._threadPriority)
		return false;

	return true;

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

bool UScheduler::HasCurrentThreadTimestampPassed()
{
	return System::GetTickCount() >= _Scheduler._pRunningThread->_timestamp;
}

bool UScheduler::CanScheduleThreads()
{
	if(HasCurrentThreadTimestampPassed()
			&& !IsLocked()
			&& HaveReadyThreads())
	{
		return true;
	}
	return false;
}

bool UScheduler::IsLocked()
{
	return _Scheduler._schedulerLock != 0;
}
#include "System.h"
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

			UThread& currentThread = *_Scheduler._pRunningThread;

			///
			///	Check if this thread already consumed its time stamp.
			///
			if(currentThread.GetThreadState() == UThread::READY && !HasCurrentThreadTimestampPassed())
				return;

			///
			///	Get the next thread from the scheduler. And a reference to the current.
			///
			UThread& nextThread = Schedule();


			///
			/// Set the next thread as the running thread.
			///
			_Scheduler._pRunningThread = &nextThread;

			///
			///	Store this thread into the ready queue, only if the counter is 0
			///		this means that the thread isn't blocking, and just came out
			///		of a system critical section.
			///
			if(currentThread.GetThreadState() == UThread::READY)
				InsertThreadInReadyQueue(currentThread);

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
	DebugAssertTrue(IsLocked());
	DebugAssertTrue(CanScheduleThreads());

	UThread& current = GetRunningThread();

	current._context = *trapContext;

	InsertThreadInReadyQueue(current);

	UThread& next = Schedule();

	_Scheduler._pRunningThread = &next;

	*trapContext = next._context;

}

IsrCompletationStatus UScheduler::SystemTimerInterruptRoutine(InterruptArgs* args, SystemIsrArgs sargs)
{
	///
	///	If its possible and its time to schedule the current thread do it.
	///
	if(CanScheduleThreads())
		SwitchContexts(args->InterruptContext);

	///
	///
	///	The following code is reading data from the kernel without the scheduler lock
	///	this is possible because even if there is a thread manipulating the waitingQueue
	///	the reads made inside the isr won't do any kind of damage, and even if this function
	///	returns CALL_PISR the InterruptController is smart enough to know that someone has the
	/// scheduler lock so there's no point on Unparking the PISR thread.
	///
	///

	///
	///	Check if there are threads waiting to be awaken.
	///
	if(_Scheduler._waitingQueue.IsEmpty())
		return FINISHED_HANDLING;

	///
	///	Check if there are sleeping threads ready to run.
	///		if so mobilize the pisr to unlock all threads that are ready.
	///

	if(_Scheduler._waitingQueue.GetFirst()->GetValue()->HasTimedout())
		return CALL_PISR;

	return FINISHED_HANDLING;

}

void UScheduler::SystemTimerPostInterruptRoutine(SystemPisrArgs args)
{
	///
	///	Acquire the scheduler lock to manipulate the waiting queue.
	///
	Lock();


	if(_Scheduler._waitingQueue.IsEmpty())
	{
		Unlock();
		return;
	}

	List<Timer>& sleepThreads = _Scheduler._waitingQueue;

	Timer* threadTimer;
	do
	{
		threadTimer = sleepThreads.GetFirst()->GetValue();

		///
		///	Check if the thread is ready to run.
		///
		if(!threadTimer->HasTimedout())
			break;

		threadTimer->Trigger();

		sleepThreads.RemoveFirst();

	}while(!sleepThreads.IsEmpty());

	Unlock();
}


void UScheduler::AddOperationWithTimeout(Node<Timer>& operation)
{
	DebugAssertTrue(IsLocked());
	if(_Scheduler._waitingQueue.IsEmpty())
	{
		_Scheduler._waitingQueue.AddFirst(&operation);
		return;
	}

	Node<Timer>* aux = _Scheduler._waitingQueue.GetFirst();

	U64 timeout = operation.GetValue()->GetTimeoutTime();

	do
	{
		if(aux->GetValue()->GetTimeoutTime() >= timeout)
		{
			_Scheduler._waitingQueue.AddBefore(aux,&operation);
			return;
		}
	}while((aux = _Scheduler._waitingQueue.GetNext(aux)) != NULL);

	_Scheduler._waitingQueue.AddLast(&operation);
}



/////
/////
/////	UScheduler::Timer implementation.
/////
/////

void UScheduler::Timer::SetTimeout(U32 timeout)
{
	DebugAssertTrue(IsLocked());
	_timeoutTime = System::GetTickCount() + timeout;
	AddOperationWithTimeout(_node);
}

bool UScheduler::Timer::HasTimedout()
{
	return System::GetTickCount() >= _timeoutTime;
}

void UScheduler::Timer::Disable()
{
	if(!_node.IsInList())
		return;

}

void UScheduler::Timer::Trigger()
{
	DebugAssertTrue(IsLocked());

	if(!_node.IsInList())
		return;

	_thread.UnparkThread(UThread::TIMEOUT);
}

