/*
 * BaseUThread.cpp
 *
 *  Created on: 10 de Jun de 2011
 *      Author: DVD
 */

#include "UThread.h"
#include "UScheduler.h"

///
///	Create and configure a new UThread
///
UThread::UThread(Void_P stack, U32 size, ThreadFunction func /*= NULL*/, ThreadArgument arg /*= NULL*/)
	:
		_stack(stack),
		_sizeOfStack(size),
		_func(func),
		_arg(arg),
		_threadPriority(KERNEL_THREAD_DEFAULT_PRIORITY),
		_node(),
		_parkerState(0),
		_parkerStatus(SUCCESS)
{
	InitializeStackAndContext(stack, size);

	_node.SetValue(this);
}

UThread::UThread()
	:
		_stack(NULL),
		_sizeOfStack(0),
		_func(NULL),
		_arg(NULL),
		_threadPriority(KERNEL_THREAD_DEFAULT_PRIORITY),
		_node(),
		_parkerState(0),
		_parkerStatus(SUCCESS)
{
	_node.SetValue(this);

}


void UThread::InitializeStackAndContext(Void_P stack, U32 size)
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
void UThread::UtThreadStart()
{
	UThread &thread = UScheduler::GetRunningThread();
	thread._func(thread._arg);
	thread.ParkThread(TIMEOUT_INFINITE);
}

///
///	Auxiliary function to the thread parker
///
bool UThread::TestAndClearMask(U8 mask)
{
	int aux;
	do
	{
		aux = _parkerState;
		///
		///	if the bit was already cleared return
		///
		if (!(aux & mask))
			return false;

		if (Interlocked::CompareExchange(&_parkerState, aux & ~mask, aux) == aux)
			return true;

	} while (true);
}


UThread::ParkerStatus UThread::ParkThread(U32 timeout /* = TIMEOUT_INFINITE */)
{
	return ParkInner(timeout,WAIT);
}

///
///	Removes this thread from ready listParkInner
///
UThread::ParkerStatus UThread::ParkInner(U32 timeout, ThreadState threadState)
{


	///
	///	Only this thread can park itself.
	///
	DebugAssertEqualsP(UThread,&GetCurrentThread(),this);

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
	///	Acquire Scheduler lock to manipulate the ready queue
	///
	UScheduler::Lock();

	///
	///	Alloc a timer to wake up this thread when the timeout passes.
	///
	UScheduler::Timer timer(*this);

	if(timeout != TIMEOUT_INFINITE)
	{
		///
		///	Enable timeout.
		///
		timer.SetTimeout(timeout);
	}

	///
	///	Set this thread state.
	///
	SetThreadState(threadState);

	///
	///	Unlock the Scheduler lock.
	///
	UScheduler::Unlock();

	///
	///	The thread was unparked return the result
	///
	return _parkerStatus;

}

///
///	Schedules this thread
///
void UThread::UnparkThread(ParkerStatus status /*= Success*/)
{

	_parkerStatus = status;

	///
	///	Wake the thread only when the Park in progress bit is cleared, meaning that the thread have already been parked
	///
	if (!TestAndClearMask(PARK_IN_PROGRESS_MASK))
	{
		UScheduler::Lock();
		UScheduler::InsertThreadInReadyQueue(*this);
		UScheduler::Unlock();
	}


}

///
///	Tries to lock this thread parker
///
bool UThread::TryLockParker()
{
	return TestAndClearMask(LOCK_MASK);
}

///
///	Resets this parker for further use
///
void UThread::ResetParker()
{
	_parkerState = LOCK_MASK | PARK_IN_PROGRESS_MASK;
}

///
///	Schedules this thread instance as ready
///
bool UThread::Start(ThreadFunction func /*= NULL*/, ThreadArgument arg /*= NULL*/,
		Void_P stack /*= NULL*/, U32 size /*= -1*/)
{
	///
	///	Check if the stack is null, to initialize it.
	///
	if (this->_stack == NULL)
	{
		if (stack == NULL)
			return false;

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
			return false;
		this->_func = func;
		this->_arg = arg;
	}

	///
	///	Acquire scheduler lock to insert thread into the ready queue.
	///
	UScheduler::Lock();

	///
	///	Schedule this thread
	///
	UnparkThread();

	///
	/// Reset parker to further use
	///
	ResetParker();

	///
	///	Renable context switching.
	///
	UScheduler::Unlock();

	return true;
}

///
///	Sets a new priority for this thread
///
void UThread::SetThreadPriority(U8 newPriority)
{
	if(_node.IsInList())
	{
		UScheduler::RemoveThreadFromReadyQueue(*this);
		_threadPriority = newPriority;
		UScheduler::InsertThreadInReadyQueue(*this);
	}
	else
		_threadPriority = newPriority;

	UThread::Yield();
}

///
///	This function returns the instance of the current running thread
///
UThread& UThread::GetCurrentThread()
{
	return UScheduler::GetRunningThread();
}

///
///	Yields the current thread
///
void UThread::Yield()
{
	UScheduler::Lock();

	if(UScheduler::HaveReadyThreads())
	{
		UScheduler::InsertThreadInReadyQueue(GetCurrentThread());
	}

	UScheduler::Unlock();



}

void UThread::Sleep(U32 milis)
{
	if(milis == 0)
		Yield();

	UThread& curr = GetCurrentThread();

	///
	///	This thread parker knows how to wait with timeout so call it.
	///
	curr.ParkInner(milis,EVENT);

	///
	///	Reset thread parker to further use.
	///
	curr.ResetParker();

}
