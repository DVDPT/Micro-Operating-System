/*
 * Interrupts.h
 *
 *  Created on: Jun 20, 2011
 *      Author: DVD
 */

#pragma once

enum InterruptState{ Cleared , Setted };

class Interrupts
{
public:

	///
	///	Enables interrupts, returns the previous state of the interrupts
	///
	static InterruptState EnableInterrupts();

	///
	///	Disables interrupts, returns the previous state of the interrupts
	///
	static InterruptState DisableInterrupts();

	///
	///	Sets the state of the interrupts to @state, returns the previous state of the interrupts
	///
	static InterruptState SetInterruptSate(InterruptState state);


};
