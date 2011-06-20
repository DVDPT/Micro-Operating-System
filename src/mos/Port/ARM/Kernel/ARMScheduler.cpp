/*
 * KernelPort.cpp
 *
 *  Created on: 9 de Jun de 2011
 *      Author: DVD
 */

#include "Threading.h"




NAKED void BaseUScheduler::ContextSwitch(Thread* oldThread, Thread* newThread)
{
	//	R0 oldThread
	//	R1 newThread
	ASM_VOLATILE
	(

		///
		///	Save this thread context on stack
		///
		"push { r4,r5,r6,r7,r8,r9,r10,r11,r12,lr};\n"
		///
		///	Store the stack pointer on the context
		///	oldThread->Context = sp
		///
		"str sp,[r0];\n"
		///
		///	load the new thread stack
		///	sp = newThread->Context
		///
		"ldr sp,[r1];\n"
		///
		///	Load the new thread context
		///
		"pop { r4,r5,r6,r7,r8,r9,r10,r11,r12,lr};\n"
		///
		///	The newThread context is now loaded just return
		///
		"mov pc,lr\n"
	);
}


