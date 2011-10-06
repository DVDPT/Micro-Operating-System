#include "InterruptController.h"
#include "SystemInterruptDescriptor.h"
#include "PlatformConfig.h"

#include "Peripherals.h"

#include "Clock.h"


void platform_init()
{
	UART0 uart = PeripheralContainer::GetInstance().GetUart0();
	Timer& timer = PeripheralContainer::GetInstance().GetTimer0();

	InterruptController::SetInterruptDescriptor(timer.GetInterruptDescriptor());
	InterruptController::SetInterruptDescriptor(uart.GetInterruptDescriptor());

	SystemConfiguration::GetInstance()
		.WithTimer(timer.GetInterruptDescriptor())
		.WithOutputStream(PeripheralContainer::GetInstance().GetUart0());

}
