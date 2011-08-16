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


void SystemTimer::Enable()
{
	PeripheralContainer::GetInstance().GetTimer0().Enable();
}

void SystemTimer::Disable()
{
	PeripheralContainer::GetInstance().GetTimer0().Disable();
}
