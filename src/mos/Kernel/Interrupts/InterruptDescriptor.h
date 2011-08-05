#pragma once

#include "List.h"
#include "SystemTypes.h"
#include "Interrupts.h"
#include "InterruptController.h"
#include "Debug.h"
#include "Interlocked.h"

class InterruptController;

class InterruptDescriptor
{
	///
	///	General purpose field to be used by InterruptController.
	///
	Node<InterruptDescriptor> _node;

	///
	///	The vector index of this interrupt.
	///
	const U8 _interruptVectorIndex;

	///
	///	This interrupt service routine.
	///
	IsrFunction _isr;

	///
	///	This interrupt pos interrupt service routine.
	///
	PisrFunction _pisr;

	///
	///	Stores the number of times that this interrupt happened only available on debug.
	///
	DebugField(U32,_counterDebug);

	///
	///	This counter has the number of times that this interrupt occured.
	///	before the PISR was called.
	///
	volatile U16 _numberOfNestedIsr;

	///
	///	InterruptController can access private methods of this class.
	///
	friend class InterruptController;

	///
	///	Returns the general purpose node.
	///
	Node<InterruptDescriptor>& GetNode(){ return _node; }

	///
	///	Returns the Pisr function.
	///
	PisrFunction GetPisr(){ return _pisr; }

	///
	///	Returns the Isr function.
	///
	IsrFunction GetIsr(){ return _isr; }

	///
	///	Increments the number of nested isrs
	///
	void IncrementNumberOfNestedIsr()
	{
		_numberOfNestedIsr++;
	}

	///
	///	Resets the value of the number of nested isrs to 0
	///
	void SubtractNumberOfNestedIsr(U16 value)
	{
		Interlocked::Subtract<U16>((U16*)&_numberOfNestedIsr,value);
	}


public:

	///
	///
	///
	InterruptDescriptor(U8 interruptVectorIndex,IsrFunction function)
		:
			_interruptVectorIndex(interruptVectorIndex),
			_isr(function),
			_pisr(NULL),
			_numberOfNestedIsr(0)
	{
		DebugAssertNotNull(_isr);
		_node.SetValue(this);
	}

	InterruptDescriptor(U8 interruptVectorIndex)
		:
			_interruptVectorIndex(interruptVectorIndex),
			_isr(NULL),
			_pisr(NULL),
			_numberOfNestedIsr(0)
	{
		DebugAssertNotNull(_isr);
		_node.SetValue(this);
	}

	///
	///	Set the  Interrupt Service Routine
	///
	void SetIsr(IsrFunction isr)	{		_isr = isr;	}

	///
	///	Set the Post Interrupt Service Routine
	///
	void SetPisr(PisrFunction pisr)	{		_pisr = pisr;	}

	///
	///	Returns the vector index of this interrupt
	///
	U8 GetInterruptVectorIndex(){ return _interruptVectorIndex; }

	///
	///	Returns the number of times that this interrupt happened, DEBUG ONLY
	///
	DebugMethod(void,IncrementInterruptCounterDebug,_counterDebug++;)

	///
	///	Returns the number of times that this interrupt happened before the PISR
	///	was called, this value can change during the PISR.
	///
	U16 GetNumberOfIsrCalledBeforePisr(){return _numberOfNestedIsr;}

};
