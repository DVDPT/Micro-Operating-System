#pragma once

#include "Threading.h"

class Scheduler
{
	///
	///	A constant defining the number of priorities that a thread can have.
	///
#define KERNEL_NR_OF_THREAD_PRIORITIES (8)

	///
	///	The array of ready queues supported by the kernel.
	///
	List<UtThread> _readyQueues[KERNEL_NR_OF_THREAD_PRIORITIES]; 

	///
	///	A bit map that indicates witch ready queues have threads.
	///
	U8 _queuesBitMap;


};