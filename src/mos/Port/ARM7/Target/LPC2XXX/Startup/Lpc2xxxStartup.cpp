#include "InterruptController.h"
#include "SystemInterruptDescriptor.h"
#include "PlatformConfig.h"

#include "Peripherals.h"

#include "Clock.h"

SystemInterruptDescriptor _uart0(KERNEL_INTERRUPTS_SERIAL);

void platform_init()
{
	PeripheralContainer::GetInstance().GetUart0Instance()
			.ConfigureInterrupts(PeripheralContainer::GetInstance().GetVic());


	InterruptController::SetInterruptDescritor(_uart0);

	Timer& timer = PeripheralContainer::GetInstance().GetTimer0();


	SystemInterruptDescriptor& timerIntrDesc = timer.GetInterruptDescriptor();

	InterruptController::SetInterruptDescritor(timerIntrDesc);

	SystemConfiguration::GetInstance()
		.WithTimer(timerIntrDesc)
		.WithOutputStream(PeripheralContainer::GetInstance().GetUart0Instance());



}
