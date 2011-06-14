/*
 * ARMKernelConfig.cpp
 *
 *  Created on: 14 de Jun de 2011
 *      Author: DVD
 */

#include "Configuration.h"
#include "KernelConfig.h"
#include "ARMScheduler.h"

void Configuration::ConfigureKernel()
{
	BaseUScheduler::RegisterScheduler(&armscheduler);
}
