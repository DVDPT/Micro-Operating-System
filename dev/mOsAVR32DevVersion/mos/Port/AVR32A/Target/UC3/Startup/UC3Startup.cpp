#include "InterruptController.h"
#include "SystemInterruptDescriptor.h"
#include "PlatformConfig.h"
#include "UC3A3256.h"


void platform_init()
{
	/*
	UART0 uart = PeripheralContainer::GetInstance().GetUart0();
	Timer& timer = PeripheralContainer::GetInstance().GetTimer0();

	InterruptController::SetInterruptDescriptor(timer.GetInterruptDescriptor());
	InterruptController::SetInterruptDescriptor(uart.GetInterruptDescriptor());

	SystemConfiguration::GetInstance()
		.WithTimer(timer.GetInterruptDescriptor())
		.WithOutputStream(PeripheralContainer::GetInstance().GetUart0());
*/
	
	///
	///	add timer mask and unmask function
	///
	InterruptController::SetInterruptDescriptor(UC3Timer::GetTimerInterruptDescriptor());
	
	SystemConfiguration::GetInstance().WithTimer(UC3Timer::GetTimerInterruptDescriptor());
	
	INTC->SetInterruptMaskChanger(KERNEL_INTERRUPTS_TIMER,UC3Timer::MaskInterrupt);
}
