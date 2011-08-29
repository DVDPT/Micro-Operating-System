#pragma once

#include "KernelConstants.h"
#include "Clock.h"


///
///	The frequency that the clock should work on, it should work on 1000 ticks per second.
///
#define SYSTEM_TIMER_CLOCK_FREQUENCY (Clock::GetClockFrequency() * 1000000 / 1000)

///
///	The time that the timer should request an interrupt, so that threads can do context switch.
///
#define SYSTEM_TIMER_INTERRUPT_PERIOD 1 //(KERNEL_THREAD_TIME_SLICE)
