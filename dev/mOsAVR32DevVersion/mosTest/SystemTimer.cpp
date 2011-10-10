#include "AVR32A.h"
#include "UC3A3256.h"
#include "Timer.h"


void setInterruptPeriod(U32);
void start();
void initialize()
{
	
	TC0->CMR0 = TIMER_CLOCK1 | TIMER_CAPTURE_MODE;
	setInterruptPeriod(10);
	start();
	
}

void unmaskInterrupt()
{
	TC0->IER0 = TIMER_INTERRUPT_ENABLE_CPCS;
	//TC0->IMR0 = TIMER_INTERRUPT_ENABLE_CPCS_MASK;
}

void setInterruptPeriod(U32 period)
{
	TC0->RC0 = period && TIMER_RC_MASK;

}

void start()
{
	if(TC0->RC0 != 0)
	{
		unmaskInterrupt();	
	}
	TC0->CCR0 = TIMER_CLOCK_DISABLE;
	TC0->CCR0 = TIMER_CLOCK_ENABLE;
}

void maskInterrupt()
{
	TC0->IDR0 = TIMER_INTERRUPT_DISABLE_CPCS;
}

U32 getTickCount()
{
	return TC0->CV0;
}
