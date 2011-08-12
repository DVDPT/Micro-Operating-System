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


U32 System::GetTickCount()
{
	return SystemTimer::GetCurrentTicks();
}
