#include "Mutex.h"
#include "Debug.h"

Mutex::Mutex(bool owner)
	:
	_owner(owner? &Thread::GetCurrentThread() : NULL), _reentrantCalls(1)
{

}

bool Mutex::IsLocked() { return _owner != NULL; }

bool Mutex::Acquire(U32 timeout /* = TIMEOUT_INFINITE*/)
{
	Thread* curr = &Thread::GetCurrentThread();

	if(curr == _owner)
	{
		_reentrantCalls++;
		return true;
	}
	Scheduler::Lock();

	if(_owner == NULL)
	{
		_owner = curr;
		Scheduler::Unlock();
		return true;
	}
	Node<Thread> threadNode(curr);

	_waitingThreads.Enqueue(&threadNode);

	bool success = curr->ParkThread(timeout) == UThread::PARK_SUCCESS;

	if(!success)
	{
		_waitingThreads.Remove(&threadNode);
	}

	curr->ResetParker();



	Scheduler::Unlock();

	return success;
}

void Mutex::Release()
{

	if(_owner != &Thread::GetCurrentThread())
	{
		DebugAssertFail();
		return;
	}
	if(--_reentrantCalls == 0)
	{
		Scheduler::Lock();

		_owner = NULL;
		_reentrantCalls = 1;

		while(!_waitingThreads.IsEmpty())
		{

			Thread* possibleOwner = _waitingThreads.Dequeue()->GetValue();
			if(possibleOwner->TryLockParker())
			{
				_owner = possibleOwner;
				possibleOwner->UnparkThread(Thread::PARK_SUCCESS);
				break;
			}

		}

		Scheduler::Unlock();
	}


}
