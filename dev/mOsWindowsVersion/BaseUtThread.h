#pragma once

#include "KernelTypes.h"
#include "List.h"
#include "BaseUtScheduler.h"

typedef Void_P ThreadArgument;
typedef Void (*ThreadFunction)(ThreadArgument);

enum ParkerStatus { Success, Cancelled, Timeout };

///
///	The template defines the UtThread context
///
template<typename Context>

///
///	The basic representations of a system thread
///
class BaseUThread
{

	///
	///	A pointer to the thread context
	///
	Context * m_context;

	///
	///	The thread stack
	///
	Void_P m_stack;

	///
	///	The size of the thread stack
	///
	U32 m_sizeOfStack;

	///
	///	The Thread function
	///
	ThreadFunction m_func;

	///
	///	The Thread Argument
	///
	ThreadArgument m_arg;

	///
	///	A general purpose Node to store this thread in queues
	///
	Node<BaseUThread<Context>> m_node;

	///
	///	This thread parker state:
	/// bit 0: the lock bit, whe set, the lock is free
	///	bit 1: park in progress bit
	///
	volatile U8 _parkerState;
	volatile ParkerStatus _parkerResult;

	///
	///	This method is initializes the thread stack, and its context
	///
	void InitializeStackAndContext(Void_P stack, U32 size)
	{

		///
		///	Point context to the end of the Thread stack.
		///
		m_context = (Context*)((int)m_stack + m_sizeOfStack - sizeof(Context) - sizeof(int));

		///
		///	Set start routine, so that UtThreadStart function runs after the first context switch of this thread.
		///
		m_context->SetThreadStartFunction(UtThreadStart);

		///
		///	Set the stack pointer
		///
		m_stack = m_context; 

		

	}

	///
	///	This function is responsible for the call to the ThreadFunction with the ThreadArgument stored in the instance.
	///
	static void UtThreadStart()
	{
		BaseUThread<Context>& thread = BaseUScheduler<Context>::GetRunningThread();
		thread.m_func(thread.m_arg);

	}




public:

	

	ParkerStatus ParkThread(U32 timeout)
	{
		
	}

	Void UnparkThread(ParkerStatus status)
	{
		
	}

	BOOL TryLockParker()
	{

	}


	///
	///	Schedules this thread instance as ready
	///
	BOOL Start(ThreadFunction func = NULL, ThreadArgument arg = NULL,Void_P stack = NULL, U32 size=-1)
	{
		///
		///	Check if the stack is null, to initialize it.
		///
		if(this->m_stack == NULL)
		{
			if(stack == NULL)
				return FALSE;

			m_stack = stack;
			m_sizeOfStack = size;
			InitializeStackAndContext(stack,size);
		}

		///
		///	Check if the function is null, to initialize it.
		///
		if(this->m_func == NULL)
		{
			if(func == NULL)
				return FALSE;
			this->m_func = func;
			this->m_arg = arg;
		}

		///
		///	Schedule this thread
		///
		UnparkThread(Success);

		return TRUE;
	}



	///
	///	This function returns the instance of the current running thread
	///	
	static BaseUThread<Context>& GetCurrentThread()
	{
		return BaseUScheduler<Context>::GetRunningThread();
	}




protected:

	BaseUThread(Void_P stack, U32 size, ThreadFunction func = NULL, ThreadArgument arg = NULL)
		: 
		m_stack(stack), 
		m_sizeOfStack(size),
		m_func(func),
		m_arg(arg),
		m_node()
	{
		InitializeStackAndContext(stack, size);	

		m_node.SetValue(this);
	}


	BaseUThread()	
		:
		m_stack(NULL),
		m_sizeOfStack(0),
		m_func(NULL),
		m_arg(NULL)
	{
		m_node.SetValue(this);
	}


};




