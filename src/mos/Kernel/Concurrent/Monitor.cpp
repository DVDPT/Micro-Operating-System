#include "Monitor.h"
Monitor::Monitor()
{
}
void Monitor::Enter(Monitor& m)
{
	m._monitor.Lock();

}

void Monitor::Exit(Monitor& m)
{
	m._monitor.Unlock();
}

void Monitor::Wait(Monitor& m,U32 timeout /*= TIMEOUT_INFINITE*/)
{

	m._monitor.Wait(timeout);


}

void Monitor::Notify(Monitor& m)
{
	Thread ** dummy = NULL;
	m._monitor.TryReleaseOne(dummy);
}

void Monitor::NotifyAll(Monitor& m)
{
	m._monitor.ReleaseAll();
}


Monitor::~Monitor()
{

}
