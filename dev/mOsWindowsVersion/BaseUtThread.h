#pragma once

#include <stdio.h>
#include "KernelTypes.h"
#include "List.h"



typedef Void_P ThreadArgument;
typedef Void (*ThreadFunction)(ThreadArgument);

///
///	The template defines the UtThread context
///
template<typename Context>

///
///	The basic representations of a system thread
///
class BaseUtThread
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	///																								   ///
	///											PRIVATE FIELDS										   ///
	///																								   ///
	//////////////////////////////////////////////////////////////////////////////////////////////////////

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
	Node<BaseUtThread<Context>> _node;

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	///																								   ///
	///											PRIVATE METHODS										   ///
	///																								   ///
	//////////////////////////////////////////////////////////////////////////////////////////////////////


	///
	///	This method is initializes the thread stack, and its context
	///
	void InitializeStackAndContext(Void_P stack, U32 size);

	///
	///	This function is responsible for the call to the ThreadFunction with the ThreadArgument stored in the instance.
	///
	static void UtThreadStart(){}
public:

	BOOL Start(ThreadFunction func = NULL, ThreadArgument arg = NULL,Void_P stack = NULL, U32 size=-1);
protected:

	BaseUtThread(Void_P stack, U32 size, ThreadFunction func = NULL, ThreadArgument arg = NULL);
	BaseUtThread();		


};




