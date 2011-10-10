#include "UC3InterruptController.h"

#define AVR32_INT_LEVEL_0 (0)

extern U32* ipr_val;

void UC3InterruptController::Init()
{
	for(int i = 0; i < INTERRUPT_PRIORITY_REGISTER_SIZE; ++i)
	{
		IPR[i] = ipr_val[AVR32_INT_LEVEL_0];
	}
}
U32 UC3InterruptController::GetCauseIndex()
{
	//return ICRn[MOS_INTERRUPT_LEVEL_USED]	;
	return 1;
}

