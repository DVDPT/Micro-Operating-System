/*
 * Interrupts.h
 *
 *  Created on: Aug 3, 2011
 *      Author: DVD
 */

#pragma once



#include "SystemTypes.h"
#include "KernelConfig.h"

struct InterruptArgs
{
	Context** InterruptContext;

	InterruptArgs(Context** context) : InterruptContext(context)
	{

	}


};

enum IsrCompletationStatus { FINISHED_HANDLING, CALL_PISR, ERROR };




class InterruptDescriptor;
typedef InterruptDescriptor& PisrArgs;




///
///
///
typedef IsrCompletationStatus(*IsrFunction)(InterruptArgs*);
typedef void(*PisrFunction)(PisrArgs);

///
///	The possible interrupts acceptable by the system
//	the port should undef this symbols and redefine new ones
///
 #define  KERNEL_INTERRUPTS_TIMER 	(-1)
 #define  KERNEL_INTERRUPTS_SERIAL	(-1)
 #define  KERNEL_INTERRUPTS_ADC		(-1)
 #define  KERNEL_INTERRUPTS_WATCHDOG	(-1)

typedef void* SystemIsrArgs;
typedef void* SystemPisrArgs;


typedef IsrCompletationStatus (*SystemIsr)(InterruptArgs*,SystemIsrArgs);
typedef void (*SystemPisr)(SystemPisrArgs);

typedef void (*IsrComplete)(InterruptArgs*,SystemIsrArgs);
typedef void (*PisrComplete)(SystemPisrArgs);

typedef void (*IsrPending)(InterruptArgs*,SystemIsrArgs);
typedef void (*PisrPending)(SystemPisrArgs);


#include "PortInterrupts.h"


