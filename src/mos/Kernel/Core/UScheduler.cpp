/*
 * BaseU_Scheduler.cpp
 *
 *  Created on: 10 de Jun de 2011
 *      Author: DVD
 */

#include "UScheduler.h"


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
	_idleThread._threadPriority = KERNEL_MINIMUM_THREAD_PRIORITY;
	InsertThreadInReadyQueue(_idleThread);
}


void IdleThreadRoutine()
{

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

	BOOL wasEmpty = list.IsEmpty();

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
BOOL UScheduler::HaveReadyThreads()
{
	///
	///	Get the value of the next thread
	///
	UThread& nextThread = PeekNextReadyThread();

	///
	///	Check if the next thread have a lower priority than the current thread, if so return FALSE
	///
	if (nextThread._threadPriority > GetRunningThread()._threadPriority)
		return FALSE;

	return TRUE;
}

///
///	The scheduler function
///
void UScheduler::Schedule(BOOL locked)
{

	///
	///	Check if there are ready threads to run
	///
	if (!HaveReadyThreads())
	{
		if (locked)
			System::ReleaseSystemLock();

		return;
	}

	///
	///	Acquire the System lock to safely manipulate the queues
	///
	if (!locked)
		System::AcquireSystemLock();

	UThread& currentThread = GetRunningThread();
	UThread& nextThread = DequeueNextReadyThread();

	UThread* p1 = _Scheduler._pRunningThread;
	p1 = &currentThread;

	_Scheduler._pRunningThread = &nextThread;

	System::ReleaseSystemLock();

	_Scheduler.ContextSwitch(&currentThread, &nextThread);
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

void UScheduler::lock()
{
	_Scheduler._schedulerLock++;
}

void UScheduler::unlock()
{

}

