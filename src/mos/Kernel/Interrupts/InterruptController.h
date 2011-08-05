/*
 * Interrupts.h
 *
 *  Created on: Jun 20, 2011
 *      Author: DVD
 */

#pragma once

#include "SystemTypes.h"
#include "KernelConfig.h"
#include "Interrupts.h"
#include "InterruptDescriptor.h"
#include "Debug.h"
#include "Assert.h"
#include "List.h"
#include "Threading.h"

///
///	This constant is returned by GetCurrentInterruptVectorIndex when the method HandleInterrupt is called
///	outside a interrupt handling routine.
///
#define	KERNEL_INTERRUPTS_NOT_ATTENDING_AN_INTERRUPT (0xFF)

class InterruptController
{
	///
	///	An static array to store all the interrupt descriptors pointers.
	///
	static InterruptDescriptor* _interrupts[KERNEL_INTERRUPTS_MAX_NUMBER_OF_INTERRUPTS];

	///
	///	The list of pending Pos Interrupt Service Routines
	///
	static List<InterruptDescriptor> _pendingPisr;

	///
	///	The task responsible for running all PISRs
	///
	static UTask _pisrTask;
	///
	///	Returns the number of the current Interrupt.
	///
	PORT_SPECIFIC static U8 GetCurrentInterruptVectorIndex();

	///
	///	The routine of pisr task.
	///
	static void PisrTaskRoutine();

public:

	///
	///	Enables interrupts, returns the previous state of the interrupts.
	///
	PORT_SPECIFIC static void EnableInterrupts();

	///
	///	Disables interrupts, returns the previous state of the interrupts.
	///
	PORT_SPECIFIC static void DisableInterrupts();

	///
	///	Masks the interrupt with interruptIndex.
	///
	PORT_SPECIFIC static void MaskInterrupt(U8 interruptIndex);

	///
	///	Unmasks the interrupt with interruptIndex.
	///
	PORT_SPECIFIC static void UnmaskInterrupt(U8 interruptIndex);

	///
	///	Sets the state of the interrupts to @state.
	///
	static void SetInterruptState(bool state);

	///
	///	Returns the interrupt descritor for the given index.
	///
	static InterruptDescriptor& GetInterruptDescritor(U8 interruptIndex);

	///
	///	Sets the interrupt descritor in the controller vector table.
	///
	static void SetInterruptDescritor(InterruptDescriptor& desc);

	///
	///	When an Interrupt Occurs this method is responsible for calling its isr.
	///
	static void HandleInterrupt();

	///
	///	Returns true when there are Pisrs pending to execute.
	///
	static bool ArePisrsPending();

	///
	///	Runs the pending pisr
	///
	static void RunPendingPisrs();








};
