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
	_waitingThreads.Lock();

	if(_owner == NULL)
	{
		_owner = curr;
		_waitingThreads.Unlock();
		return true;
	}

	bool success = _waitingThreads.Wait(timeout);

	_waitingThreads.Unlock();

	DebugAssertEqualsP(Thread,curr,(Thread*)_owner);

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
		_waitingThreads.Lock();

		_owner = NULL;
		_reentrantCalls = 1;

		Thread** releaseThread = NULL;
		if(_waitingThreads.TryReleaseOne(releaseThread))
		{
			_owner = (volatile Thread*)*releaseThread;
		}

		_waitingThreads.Unlock();
	}


}
