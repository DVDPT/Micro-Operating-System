/*
 * LPC2xxxTimer.cpp
 *
 *  Created on: Aug 11, 2011
 *      Author: DVD
 */

#include "SystemTimer.h"
#include "UC3A3256.h"

void SystemTimer::Configure(U32 clock, U32 interruptPeriod)
{
	
	TC0->SetInterruptPeriod(interruptPeriod);
}


void SystemTimer::Enable()
{
	TC0->Start();
}

void SystemTimer::Disable()
{
	TC0->Stop();
}
