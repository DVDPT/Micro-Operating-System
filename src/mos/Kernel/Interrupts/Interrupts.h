/*
 * Interrupts.h
 *
 *  Created on: Jun 20, 2011
 *      Author: DVD
 */

#pragma once

#include "SystemTypes.h"
#include "Config.h"


enum IsrCompletationStatus {  };

typedef void* IsrArgs;
typedef void* PisrArgs;

///
///
///
typedef IsrCompletationStatus(*IsrFunction)(IsrArgs);
typedef void(*PisrFunction)(PisrArgs);

class Interrupts
{
public:

	///
	///	Enables interrupts, returns the previous state of the interrupts
	///
	static void EnableInterrupts();

	///
	///	Disables interrupts, returns the previous state of the interrupts
	///
	static void DisableInterrupts();

	///
	///	Sets the state of the interrupts to @state, returns the previous state of the interrupts
	///
	static void SetInterruptSate(BOOL set)
	{
		if(set)
			Interrupts::EnableInterrupts();
		else
			Interrupts::DisableInterrupts();
	}




};
