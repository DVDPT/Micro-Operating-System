#include "Configuration.h"
#include "PortConfig.h"
#include "InterruptController.h"

extern "C"
{

int main();

void system_main()
{

	port_init();
	InterruptController::EnableInterrupts();
	main();

}
}

