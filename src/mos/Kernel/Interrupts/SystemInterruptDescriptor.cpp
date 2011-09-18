#include "SystemInterruptDescriptor.h"

IsrCompletationStatus SystemInterruptDescriptor::RunIsr(InterruptArgs* args)
{
	IsrCompletationStatus res = FINISHED_HANDLING;

	if(_isrPrologue != NULL)
		_isrPrologue(args,_isrArgs);

	if(_sIsr != NULL)
		res = _sIsr(args,_isrArgs);

	if(_sIsr == NULL)
		res = InterruptDescriptor::RunIsr(args);
	else
		InterruptDescriptor::RunIsr(args);

	if(_isrEpilogue != NULL)
		_isrEpilogue(args,_isrArgs);

	return res;
}

void SystemInterruptDescriptor::RunPisr()
{
	if(_pisrPrologue != NULL)
		_pisrPrologue(_pisrArgs);

	if(_sPisr != NULL)
		_sPisr(_pisrArgs);

	InterruptDescriptor::RunPisr();

	if(_pisrEpilogue != NULL)
		_pisrEpilogue(_pisrArgs);
}
