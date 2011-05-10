#include "UtThread.h"


///
///	Creates a UtThread and initializes it.
///

template<typename Context>
UtThread<Context>::UtThread(Void_P stack, U32 size, ThreadFunction func = NULL, ThreadArgument arg = NULL)
	: 
	_stack(stack), 
	_sizeOfStack(size),
	_func(func),
	_arg(arg)
{
	InitializeStackAndContext(stack, size);	
}

///
///	Creates a UtThread, this constructor should be used only for arrays.
///
template<typename Context>
UtThread<Context>::UtThread()
	:
	_stack(NULL),
	_sizeOfStack(0),
	_func(NULL),
	_arg(NULL)
{

}

template<typename Context>
void UtThread<Context>::InitializeStackAndContext(Void_P stack, U32 size)
{
	///
	///	Point context to the end of the Thread stack.
	///
	_context = (Context*)_stack + _sizeOfStack - (sizeof(Context));
	
	///
	///	Set start routine, so that UtThreadStart function runs after the first context switch of this thread.
	///
	_context->SetThreadStartFunction(UtThreadStart);


}

template<typename Context>
BOOL UtThread<Context>::Start(ThreadFunction func = NULL, ThreadArgument arg = NULL, Void_P stack = NULL, U32 size=-1)
{
	///
	///	Check if the stack is null, to initialize it.
	///
	if(_stack == NULL)
	{
		if(stack == NULL)
			return false;

		InitializeStackAndContext(stack,size);
	}

	///
	///	Check if the function is null, to initialize it.
	///
	if(_func == NULL)
	{
		_func = func;
		_arg = arg;
	}

	///
	///	Schedule this thread
	///


}