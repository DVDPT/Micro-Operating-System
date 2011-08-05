/*
 * PlatformInterrupts.h
 *
 *  Created on: Aug 5, 2011
 *      Author: DVD
 */

#pragma once
#include "UART0.h"

#undef KERNEL_INTERRUPTS_TIMER
#undef KERNEL_INTERRUPTS_SERIAL
#undef KERNEL_INTERRUPTS_ADC
#undef KERNEL_INTERRUPTS_WATCHDOG

#define KERNEL_INTERRUPTS_TIMER 0
#define KERNEL_INTERRUPTS_SERIAL ENTRY_UART0_INTERRUPT
#define KERNEL_INTERRUPTS_ADC 2
#define KERNEL_INTERRUPTS_WATCHDOG 3
