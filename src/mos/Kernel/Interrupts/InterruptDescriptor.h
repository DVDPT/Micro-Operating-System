#pragma once

#include "SystemTypes.h"
#include "Interrupts.h"

class InterruptDescritor
{
	const U8 _interruptVectorIndex;
	const IsrFunction _isr;
	const PisrFunction _pisr;


public:

	InterruptDescritor(U8 interruptVectorIndex,isrFunction, PisrFunction pisrFunction)
		:
			_interruptVectorIndex(interruptVectorIndex),_isr(isrFunction), _pisr(pisrFunction)
	{}

};
