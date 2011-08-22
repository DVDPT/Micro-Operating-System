#include "WaitBlock.h"


bool WaitBlock::TryReleaseOne(UThread ** thread)
{
	DebugExec(thread = NULL);
	DebugAssertTrue(Scheduler::IsLocked())
	if(_waitingThreads.IsEmpty())
		return false;

	do
	{
		UThread* t = _waitingThreads.Dequeue()->GetValue();
		if(t->TryLockParker())
		{
			t->UnparkThread(UThread::PARK_SUCCESS);
			*thread = t;
			return true;
		}

	}while(_waitingThreads.IsEmpty());

	return false;
}


void WaitBlock::ReleaseAll()
{
	UThread** dummy = NULL;
	DebugAssertTrue(Scheduler::IsLocked())
	while(TryReleaseOne(dummy));
}


bool WaitBlock::Wait(U32 timeout /*= TIMEOUT_INFINITE*/)
{
	DebugAssertTrue(Scheduler::IsLocked())
	UThread* current = &UThread::GetCurrentThread();
	Node<UThread> node(current);
	_waitingThreads.AddLast(&node);

	UThread::ParkerStatus parkReturn = current->ParkThread(timeout);

	DebugAssertTrue(Scheduler::IsLocked());

	current->ResetParker();

	if(parkReturn == UThread::PARK_SUCCESS)
		return true;

	DebugAssertTrue(node.IsInList());


	_waitingThreads.Remove(&node);

	return false;
}
