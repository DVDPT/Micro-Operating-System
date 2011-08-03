#pragma once



///
///	A constant defining the number of priorities that a thread can have.
///
#define KERNEL_NR_OF_THREAD_PRIORITIES (8)

///
///	Defines a thread default priority
///
#define KERNEL_DEFAULT_THREAD_PRIORITY (4)

///
///	Defines the value for the minimum priority that a thread can have
///
#define KERNEL_MINIMUM_THREAD_PRIORITY (7)

///
///	Defines the value for the maximum priority that a thread can have
///
#define KERNEL_MAXIMUM_THREAD_PRIORITY (1)

///
///	Defines the "static" stack of a Task
///
#define KERNEL_TASKS_STACK_SIZE (1024)

///
///	Defines the thread time slice in miliseconds
///
#define KERNEL_THREAD_TIME_SLICE (10)

