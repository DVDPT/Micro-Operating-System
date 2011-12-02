#pragma once
typedef unsigned int U32;

#include "SystemTypes.h"

#include "PortKernelConfig.h"

#define INTERRUPT_PRIORITY_REGISTER_SIZE (64)
#define INTERRUPT_REQUEST_REGISTER_SIZE (64)
#define INTERRUPT_LEVEL_CAUSES_SIZE (4)

typedef void (*InterruptControllerMaskChanger)(bool mask);

struct UC3InterruptController
{

	///
	///	Interrupt Priority Registers
	///
	U32 IPR[INTERRUPT_PRIORITY_REGISTER_SIZE];
	
	///
	///	Interrupt Request Registers
	///
	U32 IRR[INTERRUPT_REQUEST_REGISTER_SIZE];
	
	///
	///	Interrupt Cause registers
	///
	U32 ICRn[INTERRUPT_LEVEL_CAUSES_SIZE];
	
	///
	///	Initializes the interrupt controller.
	///
	void Init();
	
	///
	///	Sets a function pointer that knows how to mask and unmask interrupts from the peripherals.
	///
	void SetInterruptMaskChanger(U8 interruptIndex,InterruptControllerMaskChanger function);
	
	///
	///	Returns the IRR index cause.
	///
	U32 GetCauseIndex();
	
	///
	///	Masks the interrupt.
	///	
	void MaskInterrupt(U8 interruptIndex);
	
	///
	///	Unmasks the interrupt.
	///
	void UnmaskInterrupt(U8 interruptIndex);
	
};