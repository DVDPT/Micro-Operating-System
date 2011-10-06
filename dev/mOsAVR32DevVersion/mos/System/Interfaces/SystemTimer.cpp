/*
 * SystemTimer.cpp
 *
 *  Created on: Aug 15, 2011
 *      Author: DVD
 */
#include "SystemTimer.h"

U64 SystemTimer::_timerCounter = 0;


void SystemTimer::AddTimerCounter(U32 milis)
{
	_timerCounter += milis;
}


