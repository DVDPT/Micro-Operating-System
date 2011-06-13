/*
 * BaseUScheduler.cpp
 *
 *  Created on: 10 de Jun de 2011
 *      Author: DVD
 */

#include "BaseUScheduler.h"


BaseUScheduler*  BaseUScheduler::_pScheduler = NULL;



///
///	A protected ctor so that only derived types can access it.
///	_pRunningThread is initialized with the value of the main thread (the thread running this code)
///
BaseUScheduler::BaseUScheduler(ContextSwitch contextSwitch) :
	_queuesBitMap(0), _mainThread(), _pRunningThread(&_mainThread),
			_idleThread(), _contextSwitch(contextSwitch)

{
	///
	///	Register the scheduler instance so it can be used on methods
	///
	_pScheduler = this;

	///
	///	Set idle thread priority and start it
	///
	_idleThread._threadPriority = KERNEL_MINIMUM_THREAD_PRIORITY;
	InsertThreadInReadyQueue(_idleThread);
}


Void IdleThreadRoutine()
{

}

///
///	Removes the thread passed as argument from its ready list
///
Void BaseUScheduler::RemoveThreadFromReadyQueue(BaseUThread& thread)
{
	if (&thread != _pScheduler->_pRunningThread)
	{
		List<BaseUThread>& list =
				_pScheduler->_readyQueues[thread._threadPriority];
		list.Remove(&thread._node);

		if (list.IsEmpty())
			Bits<U8>::ClearBit(&_pScheduler->_queuesBitMap,
					thread._threadPriority);
	}
}

///
///	Inserts this thread passed as argument in its ready queue
///
Void BaseUScheduler::InsertThreadInReadyQueue(BaseUThread& thread)
{

	List<BaseUThread >& list =
			_pScheduler->_readyQueues[thread._threadPriority];

	BOOL wasEmpty = list.IsEmpty();

	list.Enqueue(&thread._node);

	if (wasEmpty)
		Bits<U8>::SetBit(&(_pScheduler->_queuesBitMap), thread._threadPriority);
}

///
///	Returns and removes from the ready list the next thread ready to run
///		NOTE: this function always return a thread, because idle thread never blocks
///
BaseUThread& BaseUScheduler::DequeueNextReadyThread()
{
	BaseUThread& nextThread = PeekNextReadyThread();
	RemoveThreadFromReadyQueue(nextThread);
	return nextThread;
}

///
///	Returns the next ready thread.
///		NOTE: this function always return a thread, because idle thread never blocks
///
BaseUThread& BaseUScheduler::PeekNextReadyThread()
{
	U32 queueIndex = Bits<U8>::GetLowestBitSet(_pScheduler->_queuesBitMap);

	List<BaseUThread>& list = _pScheduler->_readyQueues[queueIndex];

	Node<BaseUThread>* threadNode = list.GetFirst();
	return *(threadNode->GetValue());
}

///
///	Returns TRUE when there is a ready thread with a bigger priority than the running thread. Returns FALSE otherwise.
///
BOOL BaseUScheduler::HaveReadyThreads()
{
	///
	///	Get the value of the next thread
	///
	BaseUThread& nextThread = PeekNextReadyThread();

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
Void BaseUScheduler::Schedule(BOOL locked)
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

	BaseUThread& currentThread = GetRunningThread();
	BaseUThread& nextThread = DequeueNextReadyThread();

	BaseUThread* p1 = _pScheduler->_pRunningThread;
	p1 = &currentThread;

	_pScheduler->_pRunningThread = &nextThread;

	System::ReleaseSystemLock();

	_pScheduler->_contextSwitch(&currentThread, &nextThread);
}

///
///	Returns the current running thread
///
BaseUThread& BaseUScheduler::GetRunningThread()
{
	return *_pScheduler->_pRunningThread;
}

U32 BaseUScheduler::GetLockCount()
{
	return _pScheduler->_schedulerLock;
}

Void BaseUScheduler::SetLockCount(U32 newlock)
{
	_pScheduler->_schedulerLock = newlock;
}

Void BaseUScheduler::lock()
{
	_pScheduler->_schedulerLock++;
}

Void BaseUScheduler::unlock()
{

}


