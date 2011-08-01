#include "System.h"
#include "Interlocked.h"
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
	///	get timer values
	return 0;
}
