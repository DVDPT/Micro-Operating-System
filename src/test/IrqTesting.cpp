/*
 * IrqTesting.c
 *
 *  Created on: Aug 2, 2011
 *      Author: DVD
 */

#include <Interrupts.h>
#include <InterruptController.h>
//
int main();



IsrCompletationStatus some_isr()
{

	int * reg = (int*)0xE000C014;
	int xpto = *reg;
	reg -= 0x14/4;
	xpto = *reg;
	xpto++;
	return FINISHED_HANDLING;
}

int main()
{

	InterruptController::UnmaskInterrupt(KERNEL_INTERRUPTS_SERIAL);
	InterruptController::UnmaskInterrupt(KERNEL_INTERRUPTS_TIMER);

	int i = 0;
	while(true)
	{
		i++;
	}
	return 0;
}
//*/
