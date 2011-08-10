/*
 * Configuration.h
 *
 *  Created on: 14 de Jun de 2011
 *      Author: DVD
 */

#pragma once



#include "SystemInterruptDescriptor.h"
#include "InterruptController.h"
#include "UScheduler.h"
#include "Debug.h"

class SystemConfiguration
{

	static SystemConfiguration* _configuration;
	SystemInterruptDescriptor* _timerIntrDesc;

public:
	SystemConfiguration(){ _configuration = this; }

	static SystemConfiguration& GetInstance(){ return *_configuration; }

	SystemConfiguration& WithTimer(SystemInterruptDescriptor& timerInterruptDesc)
	{
		_timerIntrDesc = &timerInterruptDesc;
		return *this;
	}

	SystemConfiguration& WithDefaultOutputStream()
	{

		return *this;
	}

	SystemConfiguration& WithDefaultInputStream()
	{

		return *this;
	}

	void Configure();

};
