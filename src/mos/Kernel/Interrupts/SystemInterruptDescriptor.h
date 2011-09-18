/*
 * InterruptDescriptorDecorator.h
 *
 *  Created on: Aug 9, 2011
 *      Author: DVD
 */
#pragma once

class SystemInterruptDescriptor;

#include "Interrupts.h"
#include "InterruptDescriptor.h"






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
	///	This function will be called before both user and system isr ran.
	///
	IsrPending _isrPrologue;

	///
	///	This function will be called before both user and system pisr ran.
	///
	PisrPending _pisrPrologue;

	///
	///	This function will be called after both user and system isr ran.
	///
	IsrComplete _isrEpilogue;

	///
	///	This function will be called after both user and system pisr ran.
	///
	PisrComplete _pisrEpilogue;

	///
	///	The parameter to pass to the system ISR.
	///
	SystemIsrArgs _isrArgs;

	///
	///	The parameter to pass to the system PISR.
	///
	SystemPisrArgs _pisrArgs;



public:
	SystemInterruptDescriptor(U8 interruptVectorIndex,IsrFunction function = NULL,SystemIsrArgs systemIsrData = NULL)
		:
			InterruptDescriptor(interruptVectorIndex,function),
			_sIsr(NULL),
			_sPisr(NULL),
			_isrEpilogue(NULL),
			_pisrEpilogue(NULL),
			_isrArgs(systemIsrData)

	{}

	///
	///	Sets the args for the isr.
	///
	void SetSystemIsrArgument(SystemIsrArgs args){ _isrArgs = args; }

	///
	///	Sets the args for the pisr.
	///
	void SetSystemPisrArgument(SystemPisrArgs args) { _pisrArgs = args; }

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
	///	Sets the system pisr epilogue to @pisr.
	///
	void SetEpilogueForPisr(PisrComplete pisr){ _pisrEpilogue = pisr; }

	///
	///	Sets the system isr prologue to @isr.
	///
	void SetPrologueForIsr(IsrPending isr){ _isrPrologue = isr; }

	///
	///	Sets the system pisr prologue to @pisr.
	///
	void SetPrologueForPisr(PisrPending pisr){ _pisrPrologue = pisr; }

	///
	///	Overrided method, to add functionality.
	///
	IsrCompletationStatus RunIsr(InterruptArgs* args);

	///
	///	Overrided method, to add functionality.
	///
	void RunPisr();

	bool IsIsrAvailable(){return _isrEpilogue != NULL || _isrPrologue != NULL || _sIsr != NULL || InterruptDescriptor::IsIsrAvailable();}

	bool IsPisrAvailable(){return _pisrEpilogue != NULL || _pisrPrologue != NULL || _sPisr != NULL || InterruptDescriptor::IsPisrAvailable();}
};
