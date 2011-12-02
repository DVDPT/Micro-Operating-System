#include "InterruptController.h"

#include "UC3A3256.h"

void InterruptController::MaskInterrupt(U8 interruptIndex)
{
	INTC->MaskInterrupt(interruptIndex);
}

void InterruptController::UnmaskInterrupt(U8 interruptIndex)
{
	INTC->UnmaskInterrupt(interruptIndex);
}

void InterruptController::InterruptHandled()
{
	///
	///	Nothing to do here
	///
}

U8 InterruptController::GetCurrentInterruptVectorIndex()
{
	return INTC->GetCauseIndex();
}
