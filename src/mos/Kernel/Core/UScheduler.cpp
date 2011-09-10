/*
 * BaseU_Scheduler.cpp
 *
 *  Created on: 10 de Jun de 2011
 *      Author: DVD
 */

#include "UScheduler.h"
#include "Debug.h"
#include "SystemConfig.h"
#include "SystemTimer.h"


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
	_mainThread.SetThreadState(UThread::READY);
	_mainThread.ResetParker();
	///
	///	Set idle thread priority and start it
	///
	_idleThread._threadPriority = KERNEL_THREAD_MINIMUM_PRIORITY;
	DebugExec(_schedulerLock = 1);
	InsertThreadInReadyQueue(_idleThread);
	DebugExec(_schedulerLock = 0);
}

#include "System.h"
void UScheduler::IdleThreadRoutine()
{

	while(true)
	{
		System::GetStandardOutput().Write("Idle");
		UThread::Yield();
	}
}

///
///	Removes the thread passed as argument from its ready list
///
void UScheduler::RemoveThreadFromReadyQueue(UThread& thread)
{
	DebugAssertTrue(thread._node.IsInList());

	if (&thread != _Scheduler._pRunningThread)
	{
		List<UThread>& list = _Scheduler._readyQueues[thread._threadPriority];
		list.Remove(&thread._node);

		if (list.IsEmpty())
			Bits<volatile U8>::ClearBit(&_Scheduler._queuesBitMap,thread._threadPriority);
	}
}

///
///	Inserts this thread passed as argument in its ready queue
///
void UScheduler::InsertThreadInReadyQueue(UThread& thread)
{

	//DebugAssertTrue(IsLocked());
	DebugAssertTrue(!thread._node.IsInList());

	thread.SetThreadState(UThread::READY);

	List<UThread >& list =
			_Scheduler._readyQueues[thread._threadPriority];

	bool wasEmpty = list.IsEmpty();

	list.Enqueue(&thread._node);

	if (wasEmpty)
		Bits<volatile U8>::SetBit(&(_Scheduler._queuesBitMap), thread._threadPriority);
}

///
///	Returns and removes from the ready list the next thread ready to run
///		NOTE: this function always return a thread, because idle thread never blocks
///
UThread& UScheduler::DequeueNextReadyThread()
{

	UThread* nextThread = PeekNextReadyThread();
	DebugAssertNotNull(nextThread);
	RemoveThreadFromReadyQueue(*nextThread);
	return *nextThread;
}

///
///	Returns the next ready thread.
///		NOTE: this function always return a thread, because idle thread never blocks
///
UThread* UScheduler::PeekNextReadyThread()
{
	U32 queueIndex = Bits<U8>::GetLowestBitSet(_Scheduler._queuesBitMap);

	List<UThread>& list = _Scheduler._readyQueues[queueIndex];

	if(list.IsEmpty())
		return NULL;

	Node<UThread>* threadNode = list.GetFirst();
	return threadNode->GetValue();
}

///
///	Returns TRUE when there is a ready thread with a bigger priority than the running thread. Returns FALSE otherwise.
///
bool UScheduler::HaveReadyThreads()
{
	///
	///	Get the value of the next thread
	///
	UThread* nextThread = PeekNextReadyThread();

	if(nextThread == NULL)
		return false;

	///
	///	Check if the next thread have a lower priority than the current thread, if so return FALSE
	///
	if (nextThread->_threadPriority > GetRunningThread()._threadPriority)
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

	RenewThread(nextThread);

	return nextThread;

}

///
///	Returns the current running thread
///
UThread& UScheduler::GetRunningThread()
{
	return (UThread&)*_Scheduler._pRunningThread;
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
	if((_Scheduler._schedulerLock -1 ) == 0)
	{
		UnlockInner(0);
	}
	else
		_Scheduler._schedulerLock--;
}

void UScheduler::RenewThread(UThread& thread)
{
	thread.SetTimestamp(System::GetTickCount() + KERNEL_THREAD_TIME_SLICE);
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

void UScheduler::UnlockInner(U32 lockCount)
{
	DebugAssertTrue(lockCount+1 == GetLockCount() || lockCount == GetLockCount());

	do
	{
		///
		///	If there are pending pisrs run them.
		///
		if(InterruptController::ArePisrsPending())
			InterruptController::RunPendingPisrs();
		else
		{

			UThread& currentThread = GetRunningThread();

			///
			///	Check if this thread already consumed its time stamp.
			///	if so and there are no more threads to run, renew its timestamp and return.
			///
			if(currentThread.GetThreadState() == UThread::READY)
			{
				if(!HasCurrentThreadTimestampPassed())
					break;

				if(!HaveReadyThreads())
				{
					RenewThread(currentThread);
					break;
				}

				if(!currentThread._node.IsInList())
				{
					InsertThreadInReadyQueue(currentThread);
				}
			}


			///
			///	Get the next thread from the scheduler. And a reference to the current.
			///
			UThread& nextThread = Schedule();

			DebugAssertNotEqualsP(UThread,&currentThread,&nextThread);

			///
			/// Set the next thread as the running thread.
			///
			_Scheduler._pRunningThread = &nextThread;

			DebugExec(
						if(!currentThread._node.IsInList())
							DebugAssertTrue(currentThread.GetThreadState() != UThread::READY)
					  );

			///
			///	Disable interrupts so that no interrupt occur during context switching,
			///		that way its impossible an interrupt service routine switchs threads
			///		without their contexts are properly saved.
			///
			bool prevState = System::AcquireSystemLock();

			///
			///	Set scheduler lock count to 0 this thread isn't doing any critical operation on
			///		the scheduler instance.
			///
			SetLockCount(0);

			///
			///	Switch threads.
			///
			_Scheduler.ContextSwitch(&currentThread,&nextThread);

			DebugAssertFalse(currentThread._node.IsInList());

			DebugAssertEquals(0,GetLockCount());

			DebugAssertEquals(&currentThread,(void*)_Scheduler._pRunningThread);

			SetLockCount(lockCount);

			///
			///	Reenable interrupts, disabled before context switching.
			///
			System::ReleaseSystemLock(prevState);



			return;
		}

	}while(true);

	///
	///	Set the scheduler lock with the value before the switch happened.
	///
	SetLockCount(lockCount);
	DebugAssertFalse(GetRunningThread()._node.IsInList());

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
	DebugAssertTrue(!IsLocked());
	DebugAssertTrue(CanScheduleThreads());

	///
	///	Retrieve the current thread to do the context switch.
	///
	UThread& current = GetRunningThread();

	DebugAssertFalse(current._node.IsInList());

	///
	///	Save the current thread context (saved on interrupts trap)
	///
	current._context = *trapContext;

	///
	///	Insert the current thread on ready queue, to further scheduling.
	///
	InsertThreadInReadyQueue(current);

	///
	///	Get the ready thread to run.
	///
	UThread& next = Schedule();

	DebugAssertNotEqualsP(UThread,&current,&next);

	///
	///	Set the @next thread as the running thread.
	///
	_Scheduler._pRunningThread = &next;

	///
	/// Switch contexts.
	///
	*trapContext = next._context;

}

IsrCompletationStatus UScheduler::SystemTimerInterruptRoutine(InterruptArgs* args, SystemIsrArgs sargs)
{
	SystemTimer::AddTimerCounter(SYSTEM_TIMER_INTERRUPT_PERIOD);

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

		///
		///	Release the thread waiting for the timer to fire.
		///
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
	return System::GetTickCount() > _timeoutTime;
}

void UScheduler::Timer::Disable()
{
	if(!_node.IsInList())
		return;

	Lock();
	_Scheduler._waitingQueue.Remove(&_node);
	Unlock();

}

void UScheduler::Timer::Trigger()
{
	DebugAssertTrue(IsLocked());

	if(!_node.IsInList())
		return;


	///
	///	if the thread is still waiting for timer event wake it up.
	///
	if(_thread.TryLockParker())
	{
		DebugAssertEquals(_thread.GetThreadState(),UThread::EVENT);

		///
		///	Its possible that the timer event was triggered before the thread could
		///	switch to another, so to avoid control erros, check if the waiting thread already
		///	switched. And if not set its state to ready. This behaviour is possible because the
		///	pending pisrs call be called before the thread actually switchs with anoter.
		///
		if(&GetRunningThread() != &_thread)
			_thread.UnparkThread(UThread::PARK_TIMEOUT);

		///
		///
		///
		else
		{
			///
			///	If the thread is still on UnlockInner function, set
			///	the park state as timeout, and the thread state to READY.
			///
			_thread._parkerState = UThread::PARK_TIMEOUT;
			_thread.SetThreadState(UThread::READY);
		}
	}
}

