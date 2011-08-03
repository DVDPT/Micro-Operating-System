#pragma once

#include "List.h"
#include "SystemTypes.h"
#include "Interrupts.h"
#include "InterruptController.h"
#include "Debug.h"

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
	const IsrFunction _isr;

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


public:

	///
	///
	///
	InterruptDescriptor(U8 interruptVectorIndex,IsrFunction function)
		:
			_interruptVectorIndex(interruptVectorIndex),
			_isr(function),
			_pisr(NULL)
	{
		DebugAssertNotNull(_isr);
		_node.SetValue(this);
	}

	void SetPisr(PisrFunction pisr)	{		_pisr = pisr;	}

	U8 GetInterruptVectorIndex(){ return _interruptVectorIndex; }

	DebugMethod(void,IncrementInterruptCounterDebug,_counterDebug++;)

	U16 GetNumberOfIsrCalledBeforePisr(){return _numberOfNestedIsr;}

};
