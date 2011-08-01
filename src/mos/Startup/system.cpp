#include "Configuration.h"
#include "PortConfig.h"
#include "Interrupts.h"
extern "C"
{

int main();

void system_main()
{
	Interrupts::EnableInterrupts();
	main();
}
}

