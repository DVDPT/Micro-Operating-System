#pragma once


#include "LPC2xxx.h"
#include "LPC2xxxTypes.h"
#include "Debug.h"
#include "SystemInterruptDescriptor.h"
#include "SystemConfig.h"
#include "SystemTimer.h"

#define INTERRUPT_ENTRY_TIMER0 (0x4)
#define INTERRUPT_ENTRY_TIMER1 (0x5)

#define LPC2xxx_TIMER0 	((void*)TIMER0_BASE_ADDRESS)
#define LPC2xxx_TIMER1	((void*)TIMER1_BASE_ADDRESS)


class Timer
{

	struct LPC2xxxTimer
	{
		LPC2xxx_REG IR;
		LPC2xxx_REG TCR;
		LPC2xxx_REG TC;
		LPC2xxx_REG PR;
		LPC2xxx_REG PC;
		LPC2xxx_REG MCR;
		LPC2xxx_REG MR0;
		LPC2xxx_REG MR1;
		LPC2xxx_REG MR2;
		LPC2xxx_REG MR3;
		LPC2xxx_REG CCR;
		LPC2xxx_REG CR0;
		LPC2xxx_REG CR1;
		LPC2xxx_REG CR2;
		LPC2xxx_REG CR3;
		U8 dummy[52];
		LPC2xxx_REG CTCR;
	};
	///
	///	This timer pointer to its registers.
	///
	volatile LPC2xxxTimer * _timer;

	///
	///	The instance of this timer interrupt descriptor.
	///
	SystemInterruptDescriptor _timerIrq;

	///
	///	The period that this timer should do a interrupt.
	///
	U32 _intrPeriod;

	///
	///	Method to clear this timer interrupt request.
	///
	static void OnTimerIsrComplete(InterruptArgs* irq,Timer* timer);

	///
	///	Clears the current interrupt request and sets the next.
	///
	static void OnTimerInterrupt(InterruptArgs* irq,Timer* timer);

public:
	///
	///	@timer - the timer for this instance.
	///	@clock - the clock that this timer should work in Hz.
	///
	Timer(void* timer, U32 clock = 0)
		:
			_timer((volatile LPC2xxxTimer*)timer),
			_timerIrq(( (( (U32)timer) == (U32)TIMER0_BASE_ADDRESS) ? INTERRUPT_ENTRY_TIMER0 : INTERRUPT_ENTRY_TIMER1)
						,NULL
						,this)
	{
		SetClock(clock);
		_timerIrq.SetPrologueForIsr((IsrPending)&OnTimerInterrupt);
		_timerIrq.SetEpilogueForIsr((IsrComplete)&OnTimerIsrComplete);
	}

	///
	///	Sets the @clock into the PrescaleRegister
	///
	void SetClock(U32 clock);

	///
	///	Enable this timer.
	///
	void Enable();

	///
	///	Disable this timer.
	///
	void Disable();

	///
	///	Returns the current timer count.
	///
	U32 GetTimerCount();

	///
	///	Sets this time interrupt period.
	///
	void SetInterruptPeriod(U32 period){ _intrPeriod = period; }

	///
	///	Returns this timer interrupt descriptor.
	///
	SystemInterruptDescriptor& GetInterruptDescriptor(){return _timerIrq;}



};
