/*
 * Timer.cpp
 *
 *  Created on: Aug 10, 2011
 *      Author: DVD
 */

#include "Timer.h"

#define	TIMER_TCR_COUNTER_DISABLE (0x0)
#define	TIMER_TCR_COUNTER_ENABLE (0x1)
#define	TIMER_TCR_COUNTER_RESET (0x2)

#define TIMER_IR_CLEAR_MR0_INTR (0x1)

///
///	Interrupt when MR0 == TC, Reset TC.
///
#define TIMER_MCR_MR0_IRQ_ENABLE (0x3)



Timer::Timer(void* timer, U32 clock/* = 0*/)
	:

		_timer((volatile LPC2xxxTimer*)timer),
		_timerIrq(( (( (U32)timer) == (U32)TIMER0_BASE_ADDRESS) ? INTERRUPT_ENTRY_TIMER0 : INTERRUPT_ENTRY_TIMER1)
					,NULL
					,this),
					_intrPeriod(0)
{
	SetClock(clock);
	_timer->TCR = 0;
	_timer->MCR = 0;
	_timerIrq.SetPrologueForIsr((IsrPending)&OnTimerInterrupt);

}

void Timer::Enable()
{
	///
	///	Reset timer.
	///
	_timer->TCR = TIMER_TCR_COUNTER_RESET;

	DebugAssertNotEquals(0,_timer->PR);

	if(_intrPeriod > 0)
	{
		///
		///	Set the interrupt period on MR0 to trigger interrupt and clear TC when matches MR0.
		///
		_timer->MR0 = _intrPeriod;

		///
		///	Enable timer interrupts.
		///
		_timer->MCR = TIMER_MCR_MR0_IRQ_ENABLE;

		_timerIrq.SetEpilogueForIsr((IsrComplete)&OnTimerIsrComplete);
	}
	///
	///	Enable timer.
	///
	_timer->TCR = TIMER_TCR_COUNTER_ENABLE;

}

void Timer::Disable()
{
	_timer->TCR = TIMER_TCR_COUNTER_DISABLE;
}

void Timer::SetClock(U32 clock)
{

	_timer->PR = clock;
}

U32 Timer::GetTimerCount()
{
	return _timer->TC;
}

void Timer::OnTimerIsrComplete(InterruptArgs* irq,Timer* timer)
{

	timer->_timer->IR = TIMER_IR_CLEAR_MR0_INTR;

}


void Timer::OnTimerInterrupt(InterruptArgs* irq,Timer* timer)
{
	///
	///	Update system clock.
	///
	SystemTimer::AddTimerCounter(timer->_intrPeriod);

}

void Timer::SetInterruptPeriod(U32 period){ _intrPeriod = period; }
