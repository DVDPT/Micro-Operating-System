/*
 * BaseUThread.cpp
 *
 *  Created on: 10 de Jun de 2011
 *      Author: DVD
 */

#include "BaseUThread.h"
#include "BaseUScheduler.h"

///
///	Create and configure a new UThread
///
BaseUThread::BaseUThread(Void_P stack, U32 size, ThreadFunction func /*= NULL*/, ThreadArgument arg /*= NULL*/)
	:
		_stack(stack),
		_sizeOfStack(size),
		_func(func),
		_arg(arg),
		_threadPriority(KERNEL_DEFAULT_THREAD_PRIORITY),
		_node(),
		_parkerState(0),
		_parkerStatus(Success)
{
	InitializeStackAndContext(stack, size);

	_node.SetValue(this);
}

BaseUThread::BaseUThread()
	:
		_stack(NULL),
		_sizeOfStack(0),
		_func(NULL),
		_arg(NULL),
		_threadPriority(KERNEL_DEFAULT_THREAD_PRIORITY),
		_node(),
		_parkerState(0),
		_parkerStatus(Success)
{
	_node.SetValue(this);
}


void BaseUThread::InitializeStackAndContext(Void_P stack, U32 size)
{
	///
	///	Point context to the start of the Thread stack.
	///
	_context = (Context*) ((int) _stack + _sizeOfStack - sizeof(Context)
			- sizeof(unsigned));

	///
	///	Set start routine, so that UtThreadStart function runs after the first context switch of this thread.
	///
	_context->SetThreadStartFunction(UtThreadStart);

	///
	///	Set the stack pointer
	///
	_stack = _context;

}

///
///	This function is responsible for the call to the ThreadFunction with the ThreadArgument stored in the instance.
///
void BaseUThread::UtThreadStart()
{
	BaseUThread &thread = BaseUScheduler::GetRunningThread();
	thread._func(thread._arg);

}

///
///	Auxiliary function to the thread parker
///
BOOL BaseUThread::TestAndClearMask(U8 mask)
{
	int aux;
	do
	{
		aux = _parkerState & mask;
		///
		///	if the bit was already cleared return
		///
		if (aux == 0)
			return FALSE;

		if (Interlocked<U8>::CompareExchange(&_parkerState, aux & ~mask, aux)
				== aux)
			return TRUE;

	} while (true);
}



///
///	Removes this thread from ready list
///
BaseUThread::ParkerStatus BaseUThread::ParkThread(U32 timeout)
{
	Assert::Equals(this, &GetCurrentThread());

	///
	///	if the park in progress bit is cleared the thread was already unparked so just return the result
	///
	if (_parkerState == 0)
		return _parkerStatus;

	///
	///	Try to clear park in progress bit, if it fails the unpark method was already called, return the result
	///
	if (!TestAndClearMask(PARK_IN_PROGRESS_MASK))
		return _parkerStatus;

	///
	///	Acquire System lock to manipulate the ready queue
	///
	System::AcquireSystemLock();

	///
	///	Remove this thread from ready queue
	///
	BaseUScheduler::RemoveThreadFromReadyQueue(*this);

	///
	///	Call the scheduler to block this thread
	///
	BaseUScheduler::Schedule(TRUE);

	///
	///	The thread was unparked return the result
	///

	return _parkerStatus;

}

///
///	Schedules this thread
///
void BaseUThread::UnparkThread(ParkerStatus status /*= Success*/)
{
	_parkerStatus = status;

	///
	///	Wake the thread only when the Park in progress bit is cleared, meaning that the thread have already been parked
	///
	if (!TestAndClearMask(PARK_IN_PROGRESS_MASK))
	{
		System::AcquireSystemLock();

		BaseUScheduler::InsertThreadInReadyQueue(*this);

		System::ReleaseSystemLock();
	}

}

///
///	Tries to lock this thread parker
///
BOOL BaseUThread::TryLockParker()
{
	return TestAndClearMask(LOCK_MASK);
}

///
///	Resets this parker for further use
///
void BaseUThread::ResetParker()
{
	_parkerState = LOCK_MASK | PARK_IN_PROGRESS_MASK;
}

///
///	Schedules this thread instance as ready
///
BOOL BaseUThread::Start(ThreadFunction func /*= NULL*/, ThreadArgument arg /*= NULL*/,
		Void_P stack /*= NULL*/, U32 size /*= -1*/)
{
	///
	///	Check if the stack is null, to initialize it.
	///
	if (this->_stack == NULL)
	{
		if (stack == NULL)
			return FALSE;

		_stack = stack;
		_sizeOfStack = size;
		InitializeStackAndContext(stack, size);
	}

	///
	///	Check if the function is null, to initialize it.
	///
	if (this->_func == NULL)
	{
		if (func == NULL)
			return FALSE;
		this->_func = func;
		this->_arg = arg;
	}

	///
	///	Schedule this thread
	///
	UnparkThread();

	///
	/// Reset parker to further use
	///
	ResetParker();

	return TRUE;
}

///
///	Sets a new priority for this thread
///
void BaseUThread::SetThreadPriority(U8 newPriority)
{
	_threadPriority = newPriority;

	BaseUThread::Yield();
}

///
///	This function returns the instance of the current running thread
///
BaseUThread& BaseUThread::GetCurrentThread()
{
	return BaseUScheduler::GetRunningThread();
}

///
///	Yields the current thread
///
void BaseUThread::Yield()
{
	System::AcquireSystemLock();

	if (BaseUScheduler::HaveReadyThreads())
	{

		BaseUScheduler::InsertThreadInReadyQueue(GetCurrentThread());

		BaseUScheduler::Schedule(TRUE);

		return;
	}

	System::ReleaseSystemLock();

}
