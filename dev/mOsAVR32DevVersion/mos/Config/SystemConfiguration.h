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
#include "IOutputStream.h"

class SystemConfiguration
{

	static SystemConfiguration* _configuration;
	SystemInterruptDescriptor* _timerIntrDesc;
	IOutputStream* _systemOutStream;


public:
	SystemConfiguration(){ _configuration = this; }

	static SystemConfiguration& GetInstance(){ return *_configuration; }

	SystemConfiguration& WithTimer(SystemInterruptDescriptor& timerInterruptDesc)
	{
		_timerIntrDesc = &timerInterruptDesc;
		return *this;
	}

	SystemConfiguration& WithOutputStream(IOutputStream& systemOutStream )
	{
		_systemOutStream = &systemOutStream;
		return *this;
	}

	SystemConfiguration& WithDefaultInputStream()
	{

		return *this;
	}

	void Configure();

};
