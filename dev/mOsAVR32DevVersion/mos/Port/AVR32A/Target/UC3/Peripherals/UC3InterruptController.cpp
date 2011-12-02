#include "UC3InterruptController.h"
#include "AVR32A.h"
#include "Bits.h"

#define AVR32_INT_LEVEL_0 (0)

extern U32 ipr_val[];


///
///	Some functions to mask and unmask interrupts.
///
InterruptControllerMaskChanger _maskChangers[KERNEL_INTERRUPTS_MAX_NUMBER_OF_INTERRUPTS];

void UC3InterruptController::Init()
{
	

	for(int i = 0; i < INTERRUPT_PRIORITY_REGISTER_SIZE; ++i)
	{
		IPR[i] = ipr_val[AVR32_INT_LEVEL_0];
	}
}
U32 UC3InterruptController::GetCauseIndex()
{
	return ICRn[AVR32_MAX_INTERRUPT_MODE - MOS_INTERRUPT_LEVEL_USED_MASK];
}

void UC3InterruptController::SetInterruptMaskChanger(U8 interruptIndex,InterruptControllerMaskChanger function)
{
	_maskChangers[interruptIndex] = function;
}

void UC3InterruptController::MaskInterrupt(U8 interruptIndex)
{
	_maskChangers[interruptIndex](true);
}

void UC3InterruptController::UnmaskInterrupt(U8 interruptIndex)
{
	_maskChangers[interruptIndex](false);
}
