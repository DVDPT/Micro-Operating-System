/*
 * KernelPort.cpp
 *
 *  Created on: 9 de Jun de 2011
 *      Author: DVD
 */

#include "ARMKernelPort.h"

void ARMContext::SetThreadStartFunction(void (*ThreadStart)())
{
	Ret = ThreadStart;
}
