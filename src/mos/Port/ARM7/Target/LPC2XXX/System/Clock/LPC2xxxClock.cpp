#include "Clock.h"
#include "LPC2xxx.h"
#include "PhaseLockedLoop.h"
#include "APBDivider.h"

static APBDivider* _peripheralClockDivider = (APBDivider*)APB_DIVIDER_ADDRESS;


U16 Clock::GetCrystalFrequency()
{
	return CLOCK_CRYSTAL_FREQUENCY;
}

U16 Clock::GetClockFrequency()
{
	return PhaseLockedLoop::GetClock();
}

U16 Clock::GetPeripheralsClockFrequency()
{
	return GetClockFrequency() / _peripheralClockDivider->GetClockDivider();
}

bool Clock::SetClockFrequency(U16 newClock)
{
	if(newClock % CLOCK_CRYSTAL_FREQUENCY != 0)
		return false;

	U16 oldClock = GetClockFrequency();

	bool changedClock =  PhaseLockedLoop::SetClock(newClock);

	if(changedClock)
		TriggerAllEvents(EVENT_TYPE_CLOCK,oldClock,GetClockFrequency());

	return changedClock;
}

bool Clock::SetPeripheralsClockFrequency(U16 newClock)
{
	U8 divider;
	if((GetClockFrequency() % newClock ) != 0 || (divider = GetClockFrequency() / newClock) <= APB_MAX_DIVIDER)
		return false;

	U16 oldClock = GetPeripheralsClockFrequency();

	_peripheralClockDivider->SetClockDivider(divider);

	TriggerAllEvents(EVENT_TYPE_PERIPHERALS_CLOCK,oldClock,GetPeripheralsClockFrequency());

	return true;
}

void Clock::SetClockAtMaxFrequency()
{
	SetClockFrequency(CLOCK_MAX_FREQUENCY);
}
void Clock::SetClockAtMinFrequency()
{
	SetClockFrequency(CLOCK_MIN_FREQUENCY);
}

bool Clock::SetPeripheralsClockAtMaxFrequency()
{
	return SetPeripheralsClockFrequency(CLOCK_PERIPHERALS_MAX_FREQUENCY);
}

bool Clock::SetPeripheralsClockAtMinFrequency()
{
	return SetPeripheralsClockFrequency(CLOCK_PERIPHERALS_MIN_FREQUENCY);
}


