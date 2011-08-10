#include "SystemConfiguration.h"
#include "PortConfig.h"
#include "InterruptController.h"

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
	///	Enable interrupts.
	///
	InterruptController::EnableInterrupts();

	///
	///	Call user program.
	///
	main();

}
}

