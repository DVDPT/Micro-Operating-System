#include "System.h"
#include "Interlocked.h"
#include "SystemTimer.h"

void System::AcquireSystemLock()
{
	/// disable interrupts
}

void System::ReleaseSystemLock()
{
	/// enable interrupts
}

U32 System::GetTickCount()
{
	return SystemTimer::GetCurrentTicks();
}
