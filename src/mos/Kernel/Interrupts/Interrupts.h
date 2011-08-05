/*
 * Interrupts.h
 *
 *  Created on: Aug 3, 2011
 *      Author: DVD
 */

#pragma once

#include "SystemTypes.h"

enum IsrCompletationStatus { FINISHED_HANDLING, CALL_PISR, ERROR };

//typedef void* IsrArgs;
class InterruptDescriptor;
typedef InterruptDescriptor& PisrArgs;

///
///
///
typedef IsrCompletationStatus(*IsrFunction)();
typedef void(*PisrFunction)(PisrArgs);

///
///	The possible interrupts acceptable by the system
//	the port should undef this symbols and redefine new ones
///
 #define  KERNEL_INTERRUPTS_TIMER 	(-1)
 #define  KERNEL_INTERRUPTS_SERIAL	(-1)
 #define  KERNEL_INTERRUPTS_ADC		(-1)
 #define  KERNEL_INTERRUPTS_WATCHDOG	(-1)

#include "PortInterrupts.h"


