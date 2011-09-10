#pragma once

#include "Threading.h"
#include "List.h"

////
////	TODO: use spin lock.
////

///
///	The kernel base synchronizer.
///
class WaitBlock
{
	///
	///	The list that threads that wait in this class are stored.
	///
	List<UThread> _waitingThreads;

public:

	///
	///	The lock method should be acquired to call WaitBlock public methods.
	///
	void Lock(){ Scheduler::Lock(); }

	///
	///	This method unlocks the lock of this instance.
	///
	void Unlock() {Scheduler::Unlock();}


	///
	///	Try to release one thread waiting, when the parker lock
	///	can't be acquired this method discards the thread
	///	tries to lock the next one until the list is empty or a thread
	///	is released. Return true
	///	when a waiting thread is released, false otherwise.
	///
	bool TryReleaseOne(UThread ** thread);

	///
	///	Try to release all thread waiting.
	///
	void ReleaseAll();

	///
	///	Waits the current thread to be signalled.
	///	Returns true when the thread is successful awaken,
	///	false otherwise.
	///
	bool Wait(U32 timeout = TIMEOUT_INFINITE);

	///
	///	Returns true when there are threads waiting in this waitblock.
	///
	bool HaveThreadsWaiting(){ return !_waitingThreads.IsEmpty(); }

};
