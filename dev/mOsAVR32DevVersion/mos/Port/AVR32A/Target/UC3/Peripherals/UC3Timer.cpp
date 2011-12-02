#include "AVR32A.h"
#include "UC3A3256.h"
#include "UC3Timer.h"


SystemInterruptDescriptor _timerIrqDesc(KERNEL_INTERRUPTS_TIMER,NULL,TC0);

void UC3Timer::Init()
{
	///
	/// Sets the 32khz clock enable.
	///
	U32* clock  = (U32*)(0x30 + 0xFFFF0C00);
	*clock = 1 | (1<<8);
	
	TC0->CMR = TIMER_CLOCK1 | TIMER_CAPTURE_MODE | TIMER_RC_COMPARE_TRIGGER_ENABLE;
	
	_timerIrqDesc.SetPrologueForIsr((IsrPending)UC3Timer::OnTimerIsr);
	
	
}

void UC3Timer::UnmaskInterrupt()
{
	TC0->IER = TIMER_INTERRUPT_ENABLE_CPCS;
}

void UC3Timer::SetInterruptPeriod(U32 period)
{
	TC0->RC = period && TIMER_RC_MASK;
}

void UC3Timer::Start()
{
	if(TC0->RC != 0)
	{
		this->UnmaskInterrupt();	
	}
	
	TC0->CCR = TIMER_CLOCK_ENABLE;
	TC0->CCR = TIMER_CLOCK_SWTRG;
}

void UC3Timer::MaskInterrupt()
{
	TC0->IDR = TIMER_INTERRUPT_DISABLE_CPCS;
}

U32 UC3Timer::GetClockValue()
{
	return TC0->CV;
}

void UC3Timer::Stop()
{
	TC0->CCR = TIMER_CLOCK_DISABLE;
}

void UC3Timer::OnTimerIsr(InterruptArgs* args,UC3Timer* timer)
{
	///
	///	disable the irq
	///	
	U32 dummy = timer->SR;
	dummy++;
}

SystemInterruptDescriptor& UC3Timer::GetTimerInterruptDescriptor()
{
	return _timerIrqDesc;
}

void UC3Timer::MaskInterrupt(bool mask)
{
	if(mask)
		TC0->MaskInterrupt();
	else
		TC0->UnmaskInterrupt();
}