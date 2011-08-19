#pragma once


///
///	A constant defining the number of priorities that a thread can have.
///
#define KERNEL_THREAD_NR_OF_PRIORITIES (8)

///
///	Defines a thread default priority.
///
#define KERNEL_THREAD_DEFAULT_PRIORITY (4)

///
///	Defines the value for the minimum priority that a thread can have.
///
#define KERNEL_THREAD_MINIMUM_PRIORITY (7)

///
///	Defines the value for the maximum priority that a thread can have.
///
#define KERNEL_THREAD_MAXIMUM_PRIORITY (1)

///
///	Defines the thread time slice in miliseconds.
///
#define KERNEL_THREAD_TIME_SLICE (15)

///
///	Defines the "static" stack of a Task.
///
#define KERNEL_TASKS_STACK_SIZE (1024 * 4 * 2 )

///
///	Defines the value for the priority to be used in system threads.
///
#define KERNEL_SYSTEM_THREADS_PRIORITY (0)
