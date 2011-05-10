#pragma once

#include <stdio.h>
#include "KernelTypes.h"



typedef Void_P ThreadArgument;
typedef Void (*ThreadFunction)(ThreadArgument);

///
///	The template defines the UtThread context
///
template<typename Context>

///
///	The basic representations of a system thread
///
class UtThread
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	///																								   ///
	///											PRIVATE FIELDS										   ///
	///																								   ///
	//////////////////////////////////////////////////////////////////////////////////////////////////////

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

	UtThread(Void_P stack, U32 size, ThreadFunction func = NULL, ThreadArgument arg = NULL);
	UtThread();		


};




