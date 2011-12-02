/*
 * AVR32Interrupt.cpp
 *
 *  Created on: Jun 20, 2011
 *      Author: DVD
 */


#include "SystemTypes.h"
#include "InterruptController.h"
#include "AVR32A.h"


void InterruptController::EnableInterrupts()
{
	U32 currFlags = avr32_get_system_register(AVR32_SYSTEM_REGISTERS_ADDRESS_STATUS_REGISTER);
	
	Bits<U32>::ClearBit(&currFlags,AVR32_STATUS_REGISTER_GLOBAL_INTERRUPT_MASK_POSITION);
	
	avr32_set_system_register(AVR32_SYSTEM_REGISTERS_ADDRESS_STATUS_REGISTER,currFlags);	
}

void InterruptController::DisableInterrupts()
{
	U32 currFlags = avr32_get_system_register(AVR32_SYSTEM_REGISTERS_ADDRESS_STATUS_REGISTER);
	currFlags |= ( AVR32_STATUS_REGISTER_DISABLE_GLOBAL_INTERRUPTS <<	AVR32_STATUS_REGISTER_GLOBAL_INTERRUPT_MASK_POSITION );
	
	avr32_set_system_register(AVR32_SYSTEM_REGISTERS_ADDRESS_STATUS_REGISTER,currFlags);	
}

bool InterruptController::AreInterruptsEnable()
{
	return !avr32_get_system_register(AVR32_SYSTEM_REGISTERS_ADDRESS_STATUS_REGISTER) & (AVR32_STATUS_REGISTER_DISABLE_GLOBAL_INTERRUPTS <<	AVR32_STATUS_REGISTER_GLOBAL_INTERRUPT_MASK_POSITION);
}


