#pragma once

#include "AVR32A.h"
#include "SystemTypes.h"
#include "SystemInterruptDescriptor.h"

#define TIMER_CLOCK_CLKEN_POSITION (0)
#define TIMER_CLOCK_ENABLE (1 << TIMER_CLOCK_CLKEN_POSITION)

#define TIMER_CLOCK_SWTRG_POSITION (2)
#define TIMER_CLOCK_SWTRG (1 << TIMER_CLOCK_SWTRG_POSITION)

#define TIMER_CLOCK_CLKDIS_POSITION (1)
#define TIMER_CLOCK_DISABLE (1 << TIMER_CLOCK_CLKDIS_POSITION)

#define TIMER_RC_COMPARE_TRIGGER_ENABLE_POSITION (14)
#define TIMER_RC_COMPARE_TRIGGER_ENABLE (1 << TIMER_RC_COMPARE_TRIGGER_ENABLE_POSITION)

#define TIMER_CAPTURE_MODE_POSITION (15)
#define TIMER_CAPTURE_MODE (0 << TIMER_CAPTURE_MODE_POSITION)

#define TIMER_CLOCK_POSITION (0)
#define TIMER_CLOCK1 (0 << TIMER_CLOCK_POSITION)

#define TIMER_RC_MASK (0xFFFFFFFF)

#define TIMER_INTERRUPT_CPCS_POSITION (4)
#define TIMER_INTERRUPT_ENABLE_CPCS (1 << TIMER_INTERRUPT_CPCS_POSITION)

#define TIMER_INTERRUPT_DISABLE_CPCS TIMER_INTERRUPT_ENABLE_CPCS

#define TIMER_INTERRUPT_ENABLE_CPCS_MASK TIMER_INTERRUPT_ENABLE_CPCS


struct UC3Timer
{
	U32 CCR	;
	U32 CMR	;
	U32 dummy[2];
	U32 CV		;
	U32 RA		;
	U32 RB		;
	U32 RC		;
	U32 SR		;
	U32 IER	;
	U32 IDR	;
	U32 IMR	;

	void Start();
	void Stop();
	void Init();
	void MaskInterrupt();
	void UnmaskInterrupt();
	void SetInterruptPeriod(U32 interruptPeriod);
	U32 GetClockValue();
	static SystemInterruptDescriptor& GetTimerInterruptDescriptor();
	static void OnTimerIsr(InterruptArgs* args,UC3Timer* timer);
	static void MaskInterrupt(bool mask);
};


