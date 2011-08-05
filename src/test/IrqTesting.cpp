/*
 * IrqTesting.c
 *
 *  Created on: Aug 2, 2011
 *      Author: DVD
 */

#include <Interrupts.h>
#include <InterruptController.h>

int main();



IsrCompletationStatus some_isr()
{

	return FINISHED_HANDLING;
}

int main()
{
	InterruptController::GetInterruptDescritor(KERNEL_INTERRUPTS_SERIAL)
		.SetIsr(some_isr);
	InterruptController::UnmaskInterrupt(KERNEL_INTERRUPTS_SERIAL);

	int i = 0;
	while(true)
	{
		i++;
	}
	return 0;
}

