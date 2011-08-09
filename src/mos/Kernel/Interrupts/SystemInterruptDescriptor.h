/*
 * InterruptDescriptorDecorator.h
 *
 *  Created on: Aug 9, 2011
 *      Author: DVD
 */
#pragma once

#include "InterruptDescriptor.h"

typedef void (*SystemDefinedIsr)();
typedef void (*SystemDefinedPisr)();
typedef void (*IsrComplete)();
typedef void (*PisrComplete)();

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
	SystemDefinedIsr _sIsr;

	///
	///	The system defined PISR, this function will be called before any system defined PISR.
	///
	SystemDefinedPisr _sPisr;

	///
	///	This function will be called after both user and system isr ran.
	///
	IsrComplete _isrEpilogue;

	///
	///	This function will be called after both user and system isr ran.
	///
	PisrComplete _pisrEpilogue;

protected:
	///
	///	Overrided method, to add functionality.
	///
	IsrCompletationStatus RunIsr()
	{
		if(_sIsr != NULL)
			_sIsr();
		IsrCompletationStatus res = InterruptDescriptor::RunIsr();

		if(_isrEpilogue != NULL)
			_isrEpilogue();

		return res;
	}

	///
	///	Overrided method, to add functionality.
	///
	void RunPisr()
	{
		if(_sPisr != NULL)
			_sPisr();

		InterruptDescriptor::RunPisr();

		if(_pisrEpilogue != NULL)
			_pisrEpilogue();

}

public:
	SystemInterruptDescriptor(U8 interruptVectorIndex,IsrFunction function = NULL)
		:
			InterruptDescriptor(interruptVectorIndex,function),
			_sIsr(NULL),
			_sPisr(NULL),
			_isrEpilogue(NULL),
			_pisrEpilogue(NULL)
	{}

	///
	///	Sets the system defined isr to @sIsr.
	///
	void SetSystemDefinedIsr(SystemDefinedIsr sIsr){_sIsr = sIsr;}

	///
	///	Sets the system defined isr to @sPisr.
	///
	void SetSystemDefinedPisr(SystemDefinedPisr sPisr){_sIsr = sPisr;}

	///
	///	Sets the system isr epilogue to @isr.
	///
	void SetEpilogueForIsr(IsrComplete isr){ _isrEpilogue = isr; }

	///
	///Sets the system isr epilogue to @pisr.
	///
	void SetEpilogueForIPisr(PisrComplete pisr){ _pisrEpilogue = pisr; }


};
