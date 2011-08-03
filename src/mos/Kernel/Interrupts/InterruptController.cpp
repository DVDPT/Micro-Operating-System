/*
 * Interrupts.cpp
 *
 *  Created on: Jun 20, 2011
 *      Author: DVD
 */


#include "InterruptController.h"

void InterruptController::SetInterruptState(bool state)
{
	if(state)
		InterruptController::EnableInterrupts();
	else
		InterruptController::DisableInterrupts();
}

InterruptDescriptor& InterruptController::GetInterruptDescritor(U8 interruptIndex)
{
	return *_interrupts[interruptIndex];
}

void InterruptController::SetInterruptDescritor(InterruptDescriptor& desc)
{

	DebugAssertTrue(_interrupts[desc.GetInterruptVectorIndex()] == NULL);
	_interrupts[desc.GetInterruptVectorIndex()] = &desc;
}

void InterruptController::HandleInterrupt()
{
	U8 interruptVectorIndex = GetCurrentInterruptVectorIndex();

	DebugAssertNotEquals(interruptVectorIndex,KERNEL_INTERRUPTS_NOT_ATTENDING_AN_INTERRUPT);

	DebugAssertTrue(interruptVectorIndex < KERNEL_INTERRUPTS_MAX_NUMBER_OF_INTERRUPTS);

	InterruptDescriptor* irqDesc = _interrupts[interruptVectorIndex];

	if(irqDesc == NULL)
		return;

	DebugExec(irqDesc->IncrementInterruptCounterDebug());

	switch(irqDesc->GetIsr()())
	{
		case FINISHED_HANDLING:
			break;
		case CALL_PISR:
			Node<InterruptDescriptor>& descNode = irqDesc->GetNode();
			if(descNode)
			break;
		default:
	}


}
