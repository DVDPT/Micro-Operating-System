#pragma once


#include "SystemTypes.h"
#include "List.h"
#include "Interlocked.h"
#include "KernelConfig.h"

#define TIMEOUT_INFINITE ((U32) -1)

typedef Void_P ThreadArgument;
typedef void (*ThreadFunction)(ThreadArgument);



class UScheduler;

///
///	The basic representations of a system thread
///
class UThread
{
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
	Node<UThread> _node;
	
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
	///	The time where the thread was putted on run state, this field is needed for timeslice calculation
	///
	volatile U64 _timestamp;

	///
	///	This method is initializes the thread stack, and its context
	/// The context is located at the first X bytes of the thread stack, being X the size of the context
	///
	void InitializeStackAndContext(Void_P stack, U32 size);

	///
	///	This function is responsible for the call to the ThreadFunction with the ThreadArgument stored in the instance.
	///
	static void UtThreadStart();

	///
	///	Auxiliary function to the thread parker
	///
	bool TestAndClearMask(U8 mask);

	///
	///
	///
	U32 GetTimestamp()
	{
		return _timestamp;
	}

	void SetTimestamp(U32 newStamp)
	{
		_timestamp = newStamp;
	}

	friend class UScheduler;


public:

	

	///
	///	Create and configure a new UThread
	///
	UThread(Void_P stack, U32 size, ThreadFunction func = NULL, ThreadArgument arg = NULL);

	UThread();


	///
	///	Removes this thread from ready list
	///
	ParkerStatus ParkThread(U32 timeout = -1);

	///
	///	Schedules this thread
	///
	void UnparkThread(ParkerStatus status = Success);

	///
	///	Tries to lock this thread parker
	///
	bool TryLockParker();

	///
	///	Resets this parker for further use
	///
	void ResetParker();


	///
	///	Schedules this thread instance as ready
	///
	bool Start(ThreadFunction func = NULL, ThreadArgument arg = NULL,Void_P stack = NULL, U32 size=-1);

	///
	///	Sets a new priority for this thread
	///
	void SetThreadPriority(U8 newPriority);
	///
	///	This function returns the instance of the current running thread
	///	
	static UThread& GetCurrentThread();

	///
	///	Yields the current thread
	///
	static void Yield();

};




