#pragma once

#include "KernelConfiguration.h"
#include "SystemTypes.h"
#include "List.h"
#include "BaseUScheduler.h"
#include "Interlocked.h"




typedef Void_P ThreadArgument;
typedef Void (*ThreadFunction)(ThreadArgument);

///
///	The template defines the UtThread context
///
template<typename Context>


///
///	The basic representations of a system thread
///
class BaseUThread
{
	typedef BaseUScheduler<Context> UScheduler;
public:
	///
	///	The possible results that an UnPark method can return
	///
	enum ParkerStatus { Success, Cancelled, Timeout };


private:
	///
	///	A pointer to the thread context
	///
	Context * _context;

	///
	///	The thread stack
	///
	Void_P _stack;

	///
	///	The size of the thread stack
	///
	U32 _sizeOfStack;

	///
	///	The Thread function
	///
	ThreadFunction _func;

	///
	///	The Thread Argument
	///
	ThreadArgument _arg;

	///
	///	The Thread Priority
	///
	U8 _threadPriority;

	///
	///	A general purpose Node to store this thread in queues
	///
	Node<BaseUThread<Context> > _node;
	
	///
	///	Auxiliary constants to control the state of the parker
	///
#define LOCK_BIT  (0)
#define PARK_IN_PROGRESS_BIT (1)
#define LOCK_MASK  (1 << LOCK_BIT)
#define PARK_IN_PROGRESS_MASK (1 << PARK_IN_PROGRESS_BIT)

	///
	///	This thread parker state:
	/// bit 0: the lock bit, whe set, the lock is free
	///	bit 1: park in progress bit
	///
	volatile U8 _parkerState;

	///
	///	The Parker Result, stores the last UnPark result
	///

	volatile ParkerStatus _parkerStatus;

	///
	///	This method is initializes the thread stack, and its context
	/// The context is located at the first X bytes of the thread stack, being X the size of the context
	///
	NOINLINE void InitializeStackAndContext(Void_P stack, U32 size)
	{

		int sizess = sizeof(Context);
		///
		///	Point context to the start of the Thread stack.
		///
		_context = (Context*)((int)_stack + _sizeOfStack - sizeof(Context) - sizeof(unsigned));
		
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
	static void UtThreadStart()
	{
		BaseUThread<Context>& thread = UScheduler::GetRunningThread();
		thread._func(thread._arg);

	}

	///
	///	Auxiliary function to the thread parker
	///
	NOINLINE BOOL TestAndClearMask(U8 mask)
	{
		int aux;
		do
		{
			aux = _parkerState & mask;
			///
			///	if the bit was already cleared return
			///
			if(aux == 0)
				return FALSE;

			if(Interlocked<U8>::CompareExchange(&_parkerState, aux & ~mask, aux) == aux)
				return TRUE;


		} while(true);
	}


	friend   class BaseUScheduler<Context>;


public:

	

	///
	///	Create and configure a new UThread
	///
	NOINLINE BaseUThread(Void_P stack, U32 size, ThreadFunction func = NULL, ThreadArgument arg = NULL)
		: 
		_stack(stack), 
		_sizeOfStack(size),
		_func(func),
		_arg(arg),
		_node(),
		_threadPriority(KERNEL_DEFAULT_THREAD_PRIORITY),
		_parkerState(0)
		
	{
		InitializeStackAndContext(stack, size);	

		_node.SetValue(this);
	}


	NOINLINE BaseUThread()	
		:
		_stack(NULL),
		_sizeOfStack(0),
		_func(NULL),
		_arg(NULL),
		_threadPriority(KERNEL_DEFAULT_THREAD_PRIORITY),
		_parkerState(PARK_IN_PROGRESS_MASK | LOCK_MASK)
	{
		_node.SetValue(this);
	}


	///
	///	Removes this thread from ready list
	///
	NOINLINE ParkerStatus ParkThread(U32 timeout)
	{
		Assert::Equals(this, &GetCurrentThread());

		///
		///	if the park in progress bit is cleared the thread was already unparked so just return the result
		///
		if(_parkerState == 0)
			return _parkerStatus;

		///
		///	Try to clear park in progress bit, if it fails the unpark method was already called, return the result
		///
		if(!TestAndClearMask(PARK_IN_PROGRESS_MASK))
			return _parkerStatus;

		///
		///	Acquire System lock to manipulate the ready queue
		///
		System::AcquireSystemLock();

		///
		///	Remove this thread from ready queue
		///
		UScheduler::RemoveThreadFromReadyQueue(*this);
		
		///
		///	Call the scheduler to block this thread
		///
		UScheduler::Schedule(TRUE);

		///
		///	The thread was unparked return the result
		///

		return _parkerStatus;

	}

	///
	///	Schedules this thread
	///
	NOINLINE Void UnparkThread(ParkerStatus status = Success)
	{
		_parkerStatus = status;

		///
		///	Wake the thread only when the Park in progress bit is cleared, meaning that the thread have already been parked 
		///
		if(!TestAndClearMask(PARK_IN_PROGRESS_MASK))
		{
			System::AcquireSystemLock();

			UScheduler::InsertThreadInReadyQueue(*this);

			System::ReleaseSystemLock();
		}

	}

	///
	///	Tries to lock this thread parker
	///
	NOINLINE BOOL TryLockParker()
	{
		return TestAndClearMask(LOCK_MASK);
	}

	///
	///	Resets this parker for further use
	///
	NOINLINE Void ResetParker()
	{
		_parkerState = LOCK_MASK | PARK_IN_PROGRESS_MASK;
	}


	///
	///	Schedules this thread instance as ready
	///
	NOINLINE BOOL Start(ThreadFunction func = NULL, ThreadArgument arg = NULL,Void_P stack = NULL, U32 size=-1)
	{
		///
		///	Check if the stack is null, to initialize it.
		///
		if(this->_stack == NULL)
		{
			if(stack == NULL)
				return FALSE;

			_stack = stack;
			_sizeOfStack = size;
			InitializeStackAndContext(stack,size);
		}

		///
		///	Check if the function is null, to initialize it.
		///
		if(this->_func == NULL)
		{
			if(func == NULL)
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
	NOINLINE Void SetThreadPriority(U8 newPriority)
	{
		_threadPriority = newPriority;

		/// yield
	}

	///
	///	This function returns the instance of the current running thread
	///	
	static BaseUThread<Context>& GetCurrentThread()
	{
		return UScheduler::GetRunningThread();
	}

	///
	///	Yields the current thread
	///
	static Void Yield()
	{
		System::AcquireSystemLock();

		if(UScheduler::HaveReadyThreads())
		{
			
			UScheduler::InsertThreadInReadyQueue(GetCurrentThread());

			UScheduler::Schedule(TRUE);

			return;
		}

		System::ReleaseSystemLock();
		
	}





};




