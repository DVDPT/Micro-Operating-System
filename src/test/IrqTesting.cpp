/*
 * IrqTesting.c
 *
 *  Created on: Aug 2, 2011
 *      Author: DVD
 */

#include <ARMContext.h>
int main();

ARMContext demoContext;
extern "C"
{
	extern void arm_common_trap();
	void system_common_trap(ARMContext ** ctx)
	{
		demoContext.SetThreadStartFunction((void (*)())main);
		demoContext.pc = (U32)main;
		*ctx = &demoContext;
		demoContext.flags.cpsr = 0;
		demoContext.flags.mode = 0x13;
	}
}


int main()
{
	arm_common_trap();
	return 0;
}

