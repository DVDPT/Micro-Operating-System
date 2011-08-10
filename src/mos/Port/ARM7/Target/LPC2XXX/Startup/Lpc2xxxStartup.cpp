#include "InterruptController.h"
#include "SystemInterruptDescriptor.h"
#include "PlatformConfig.h"

#include "Peripherals.h"

SystemInterruptDescriptor _uart0(KERNEL_INTERRUPTS_SERIAL);

void platform_init()
{
	PeripheralContainer::GetInstance().GetUart0Instance()
			.ConfigureInterrupts(PeripheralContainer::GetInstance().GetVic());


	InterruptController::SetInterruptDescritor(_uart0);

	SystemInterruptDescriptor& timerIntrDesc = PeripheralContainer::GetInstance().GetTimer0().GetInterruptDescriptor();

	PeripheralContainer::GetInstance().GetTimer0().SetClock(6000000);
	PeripheralContainer::GetInstance().GetTimer0().SetInterruptPeriod(100);
	PeripheralContainer::GetInstance().GetTimer0().Enable();
	InterruptController::SetInterruptDescritor(timerIntrDesc);

	SystemConfiguration::GetInstance().WithTimer(timerIntrDesc);



}
