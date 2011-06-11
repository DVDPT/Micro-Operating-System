/*
 * KernelPort.cpp
 *
 *  Created on: 9 de Jun de 2011
 *      Author: DVD
 */

#include "ARMScheduler.h"




ARMScheduler::ARMScheduler() : Scheduler(ARMContextSwitch)
{}

Void ARMScheduler::ARMContextSwitch(Thread* oldThread, Thread* newThread)
{

}
