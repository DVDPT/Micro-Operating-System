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

bool InterruptController::ArePisrsPending()
{
	return !_pendingPisr.IsEmpty();
}

void InterruptController::RunPendingPisrs()
{
	DebugAssertTrue(ArePisrsPending());
	PisrTaskRoutine();
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

	irqDesc->IncrementNumberOfNestedIsr();

	switch(irqDesc->GetIsr()())
	{
		case FINISHED_HANDLING:
			break;
		case CALL_PISR:
		{
			Node<InterruptDescriptor>& descNode = irqDesc->GetNode();

			///
			///	If the pisr task is not running and the scheduler is not locked
			///	is save to unpark pisr task from within an isr.
			///
			if(!ArePisrsPending() && !Scheduler::IsLocked())
				_pisrTask.UnparkThread();

			///
			///	if is already in list, dont do nothing because the pisr is gonna be called.
			///
			if(!descNode.IsInList())
			{
				_pendingPisr.AddLast(&descNode);
			}
			break;
		}
		default:
			Assert::Error("An error occured when calling an isr");
	}

}

void InterruptController::PisrTaskRoutine()
{
	do
	{

		if(_pendingPisr.IsEmpty())
		{
			///
			///	The pisrs were ran on another thread, dont block, return.
			///
			if(&Thread::GetCurrentThread() != &_pisrTask)
				return;

			_pisrTask.ParkThread();
		}
		///
		///	Disable interrupts to dequeue an pisr from queue.
		///
		DisableInterrupts();

		///
		///	Get an interrupt descriptor to run its pisr.
		///
		InterruptDescriptor* interrupt = _pendingPisr.Dequeue()->GetValue();

		U16 nrOfCallsToIsr = interrupt->GetNumberOfIsrCalledBeforePisr();

		///
		///	Enable interrupts, from this to the end, isrs can be called.
		///
		EnableInterrupts();

		///
		///	Run pisr and restore the number of calls of the isr with the previous store value.
		///
		interrupt->GetPisr()(*interrupt);

		interrupt->SubtractNumberOfNestedIsr(nrOfCallsToIsr);

	}while(true);
}
