/*
 * KernelPort.cpp
 *
 *  Created on: 9 de Jun de 2011
 *      Author: DVD
 */

#include "Threading.h"




NAKED void UScheduler::ContextSwitch(Thread* oldThread, Thread* newThread)
{
	//	R0 oldThread
	//	R1 newThread
	ASM_VOLATILE
	(

		///
		///	Save the lr as the program counter in case that this threads switchs back via interrupt.
		///
		"push {lr}\n"

		///
		///	Set stack 1 position down because we dont need to save lr.
		///
		"sub sp,sp,#4 \n"

		///
		///	Save this thread context on stack.
		///
		"push {r4-r12};\n"

		///
		///	Set stack 4 (4 registers * 32bits = 16 bytes) positions under (r0-r3) registers don't need to be saved.
		///
		"sub sp,sp,#16 \n"

		///
		///	Get this thread flags.
		///
		"mrs   r2 , CPSR\n"

		///
		/// Save flags.
		///
		"push {r2}\n"


		///
		///	Store the stack pointer on the context.
		///	oldThread->Context = sp
		///
		"str sp,[r0];\n"

		///
		///	load the new thread stack.
		///	sp = newThread->Context
		///
		"ldr sp,[r1];\n"

		///
		/// r0 = flags.
		///
		"pop {r0} \n"

		///
		///	Load the new thread flags.
		///
		"msr    CPSR, r0\n"

		///
		///	Load the new thread context.
		///
		"pop {r0-r12,lr,pc}\n"
	);
}


