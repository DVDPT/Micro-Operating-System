#include "SystemConfiguration.h"
#include "PortConfig.h"
#include "InterruptController.h"
#include "UThread.h"

extern "C"
{

int main();

///
///	The system initializer function.
///
void system_main()
{

	SystemConfiguration config;
	///
	///	Initialize this port.
	///
	port_init();

	///
	///	Configure the system.
	///
	config.Configure();

	///
	///	Enable interrupts.
	///
	InterruptController::EnableInterrupts();

	///
	///	Call user program.
	///
	main();

	///
	///
	///
	UThread::GetCurrentThread().ParkThread();


}
}

