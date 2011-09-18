#include "InterruptDescriptor.h"

bool InterruptDescriptor::IsIsrAvailable(){ return _isr != NULL; }

bool InterruptDescriptor::IsPisrAvailable(){ return _pisr != NULL; }

IsrCompletationStatus InterruptDescriptor::RunIsr(InterruptArgs* args)
{
	return _isr != NULL?_isr(args):FINISHED_HANDLING;
}

void InterruptDescriptor::RunPisr()
{
	if(_pisr != NULL)
	{
		_pisr(*this);
	}
}
