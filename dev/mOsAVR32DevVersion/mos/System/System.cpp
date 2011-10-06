#include "System.h"
#include "Interlocked.h"
#include "SystemTimer.h"
#include "InterruptController.h"



IOutputStream* System::_out = (IOutputStream*)NULL;

void System::EnableInterrupts()
{
	InterruptController::EnableInterrupts();
}


void System::DisableInterrupts()
{
	InterruptController::DisableInterrupts();
}


U64 System::GetTickCount()
{
	return SystemTimer::GetCurrentTicks();
}

bool System::AcquireSystemLock()
{
	bool prevState = InterruptController::AreInterruptsEnable();
	DisableInterrupts();
	return prevState;
}

void System::ReleaseSystemLock(bool previousState)
{
	if(previousState)
		EnableInterrupts();
}
