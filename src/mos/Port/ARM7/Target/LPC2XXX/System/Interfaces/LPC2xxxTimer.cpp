/*
 * LPC2xxxTimer.cpp
 *
 *  Created on: Aug 11, 2011
 *      Author: DVD
 */

#include "SystemTimer.h"
#include "Peripherals.h"

void SystemTimer::Configure(U32 clock, U32 interruptPeriod)
{
	PeripheralContainer::GetInstance().GetTimer0().SetClock(clock);
	PeripheralContainer::GetInstance().GetTimer0().SetInterruptPeriod(interruptPeriod);
}

U32 SystemTimer::GetCurrentTicks()
{
	return PeripheralContainer::GetInstance().GetTimer0().GetTimerCount();
}

void SystemTimer::Enable()
{
	PeripheralContainer::GetInstance().GetTimer0().Enable();
}
