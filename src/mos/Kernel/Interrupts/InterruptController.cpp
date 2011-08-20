/*
 * Interrupts.cpp
 *
 *  Created on: Jun 20, 2011
 *      Author: DVD
 */


#include "InterruptController.h"

InterruptDescriptor* InterruptController::_interrupts[KERNEL_INTERRUPTS_MAX_NUMBER_OF_INTERRUPTS];


List<InterruptDescriptor> InterruptController::_pendingPisr;


UTask InterruptController::_pisrTask((ThreadFunction)&PisrTaskRoutine);

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

void InterruptController::SetInterruptDescriptor(InterruptDescriptor& desc)
{

	DebugAssertTrue(_interrupts[desc.GetInterruptVectorIndex()] == NULL);
	_interrupts[desc.GetInterruptVectorIndex()] = &desc;
}

bool InterruptController::ArePisrsPending()
{
	return !_pendingPisr.IsEmpty() && _pisrTask.GetThreadState() != UThread::READY;
}

void InterruptController::RunPendingPisrs()
{
	DebugAssertTrue(ArePisrsPending());
	PisrTaskRoutine();
}

void InterruptController::HandleInterrupt(InterruptArgs * args)
{
	U8 interruptVectorIndex = GetCurrentInterruptVectorIndex();

	DebugAssertNotEquals(interruptVectorIndex,KERNEL_INTERRUPTS_NOT_ATTENDING_AN_INTERRUPT);

	DebugAssertTrue(interruptVectorIndex < KERNEL_INTERRUPTS_MAX_NUMBER_OF_INTERRUPTS);

	InterruptDescriptor* irqDesc = _interrupts[interruptVectorIndex];

	if(irqDesc == NULL)
		return;

	DebugExec(irqDesc->IncrementInterruptCounterDebug());

	irqDesc->IncrementNumberOfNestedIsr();

	switch(irqDesc->RunIsr(args))
	{
		case FINISHED_HANDLING:
			break;
		case CALL_PISR:
		{

			///
			///	If there isn't any PISR available do nothing.
			///
			if(!irqDesc->IsPisrAvailable())
				break;

			Node<InterruptDescriptor>& descNode = irqDesc->GetNode();


			///
			///	If the pisr task is not running and the scheduler is not locked
			///	is save to unpark pisr task from within an isr.
			///
			if(!ArePisrsPending() && !Scheduler::IsLocked() && _pisrTask.GetThreadState() != UThread::READY)
				Scheduler::InsertThreadInReadyQueue(_pisrTask);

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
	InterruptHandled();
}

void InterruptController::PisrTaskRoutine()
{
	do
	{

		while(_pendingPisr.IsEmpty())
		{
			///
			///	The pisrs were ran on another thread, dont block, return.
			///
			if(&Thread::GetCurrentThread() != &_pisrTask)
				return;

			_pisrTask.ParkThread();
			_pisrTask.ResetParker();
		}

		///
		///	Disable interrupts to dequeue an pisr from queue.
		///
		DisableInterrupts();

		///
		///	Check again if the list is empty, because the pisr could have already ran.
		///
		if(!_pendingPisr.IsEmpty())
		{
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
			interrupt->RunPisr();

			interrupt->SubtractNumberOfNestedIsr(nrOfCallsToIsr);
		}

	}while(true);
}
