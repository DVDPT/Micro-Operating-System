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
int xpto()
{
	return 1;
}
int main()
{

	while(true)
	{

		System::GetStandardOutput().Write("a");
		xpto();

	}
	return 0;
}
//*/
