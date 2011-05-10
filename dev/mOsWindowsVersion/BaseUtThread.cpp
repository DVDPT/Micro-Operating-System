#include "BaseUtThread.h"


///
///	Creates a UtThread and initializes it.
///

template<typename Context>
BaseUtThread<Context>::BaseUtThread(Void_P stack, U32 size, ThreadFunction func = NULL, ThreadArgument arg = NULL)
	: 
m_stack(stack), 
	m_sizeOfStack(size),
	m_func(func),
	m_arg(arg)
{
	InitializeStackAndContext(stack, size);	
	_node.SetValue(this);
}

///
///	Creates a UtThread, this constructor should be used only for arrays.
///
template<typename Context>
BaseUtThread<Context>::BaseUtThread()
	:
m_stack(NULL),
	m_sizeOfStack(0),
	m_func(NULL),
	m_arg(NULL)
{
	_node.SetValue(this);
}

template<typename Context>
void BaseUtThread<Context>::InitializeStackAndContext(Void_P stack, U32 size)
{
	///
	///	Point context to the end of the Thread stack.
	///
	m_context = (Context*)m_stack + m_sizeOfStack - (sizeof(Context));

	///
	///	Set start routine, so that UtThreadStart function runs after the first context switch of this thread.
	///
	m_context->SetThreadStartFunction(UtThreadStart);


}

template<typename Context>
BOOL BaseUtThread<Context>::Start(ThreadFunction func = NULL, ThreadArgument arg = NULL, Void_P stack = NULL, U32 size=-1)
{
	///
	///	Check if the stack is null, to initialize it.
	///
	if(m_stack == NULL)
	{
		if(stack == NULL)
			return FALSE;

		InitializeStackAndContext(stack,size);
	}

	///
	///	Check if the function is null, to initialize it.
	///
	if(m_func == NULL)
	{
		if(m_func == NULL)
			return FALSE;
		m_func = func;
		m_arg = arg;
	}

	///
	///	Schedule this thread
	///

	return TRUE;
}