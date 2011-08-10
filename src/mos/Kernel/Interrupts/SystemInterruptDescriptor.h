/*
 * InterruptDescriptorDecorator.h
 *
 *  Created on: Aug 9, 2011
 *      Author: DVD
 */
#pragma once

class SystemInterruptDescriptor;

#include "InterruptDescriptor.h"
#include "Interrupts.h"





///
///	The purpose of this class is to redefine the Interrupt handling execution.
///		This class redefine the methods RunIsr and RunPisr of InterruptDescriptor,
///		this new functions call first the a system defined isr, then the user isr, finally
///		calls an epilogue for cleanup.
///
class SystemInterruptDescriptor : public InterruptDescriptor
{

	///
	///	The system defined ISR, this function will be called before any system defined ISR.
	///
	SystemIsr _sIsr;

	///
	///	The system defined PISR, this function will be called before any system defined PISR.
	///
	SystemPisr _sPisr;

	///
	///	This function will be called after both user and system isr ran.
	///
	IsrComplete _isrEpilogue;

	///
	///	This function will be called after both user and system isr ran.
	///
	PisrComplete _pisrEpilogue;

	///
	///	The parameter to pass to the system ISR.
	///
	SystemIsrArgs _systemIsrArgs;

	///
	///	The parameter to pass to the system PISR.
	///
	SystemPisrArgs _pisrArgs;

protected:
	///
	///	Overrided method, to add functionality.
	///
	IsrCompletationStatus RunIsr(InterruptArgs* args)
	{
		if(_sIsr != NULL)
			_sIsr(args,_systemIsrArgs);
		IsrCompletationStatus res = InterruptDescriptor::RunIsr(args);

		if(_isrEpilogue != NULL)
			_isrEpilogue(args,_systemIsrArgs);

		return res;
	}

	///
	///	Overrided method, to add functionality.
	///
	void RunPisr()
	{
		if(_sPisr != NULL)
			_sPisr(_pisrArgs);

		InterruptDescriptor::RunPisr();

		if(_pisrEpilogue != NULL)
			_pisrEpilogue(_pisrArgs);

}

public:
	SystemInterruptDescriptor(U8 interruptVectorIndex,IsrFunction function = NULL,SystemIsrArgs systemIsrData = NULL)
		:
			InterruptDescriptor(interruptVectorIndex,function),
			_sIsr(NULL),
			_sPisr(NULL),
			_isrEpilogue(NULL),
			_pisrEpilogue(NULL),
			_systemIsrArgs(systemIsrData)

	{}

	///
	///	Sets the system defined isr to @sIsr.
	///
	void SetSystemDefinedIsr(SystemIsr sIsr){_sIsr = sIsr;}

	///
	///	Sets the system defined isr to @sPisr.
	///
	void SetSystemDefinedPisr(SystemPisr sPisr){_sPisr = sPisr;}

	///
	///	Sets the system isr epilogue to @isr.
	///
	void SetEpilogueForIsr(IsrComplete isr){ _isrEpilogue = isr; }

	///
	///Sets the system isr epilogue to @pisr.
	///
	void SetEpilogueForIPisr(PisrComplete pisr){ _pisrEpilogue = pisr; }


};
