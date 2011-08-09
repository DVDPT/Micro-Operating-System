#include "InterruptController.h"
#include "PlatformConfig.h"

#include "Peripherals.h"

InterruptDescriptor _uart0(KERNEL_INTERRUPTS_SERIAL);

void platform_init()
{
	PeripheralContainer::GetInstance().GetUart0Instance()
			.ConfigureInterrupts(PeripheralContainer::GetInstance().GetVic());


	InterruptController::SetInterruptDescritor(_uart0);


}
