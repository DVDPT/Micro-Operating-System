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
	///	Configure the system.
	///
	config.Configure();

	///
	///	Enable interrupts.
	///
	InterruptController::EnableInterrupts();
	InterruptController::EnableInterrupts();
	int i=0;
	do
	{
	//System::GetStandardOutput().Write('_');
	while(i++ < 100000);
	i=0;
	}while(true);
	///
	///	Call user program.
	///
	main();

}
}

