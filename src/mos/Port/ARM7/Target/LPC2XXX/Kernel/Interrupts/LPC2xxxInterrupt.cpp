/*
 * LPC2xxxInterrupt.cpp
 *
 *  Created on: Aug 5, 2011
 *      Author: DVD
 */
#include "InterruptController.h"
#include "Peripherals.h"

VectorInterruptController controller;

void InterruptController::MaskInterrupt(U8 interruptIndex)
{
	PeripheralContainer::GetInstance().GetVic().MaskInterrupt(interruptIndex);
}

void InterruptController::UnmaskInterrupt(U8 interruptIndex)
{
	PeripheralContainer::GetInstance().GetVic().UnmaskInterrupt(interruptIndex);
}

void InterruptController::InterruptHandled()
{
	PeripheralContainer::GetInstance().GetVic().EndProcessTreatmentInterrupt();
}

U8 InterruptController::GetCurrentInterruptVectorIndex()
{
	return PeripheralContainer::GetInstance().GetVic().GetCurrentInterrupt();
}
