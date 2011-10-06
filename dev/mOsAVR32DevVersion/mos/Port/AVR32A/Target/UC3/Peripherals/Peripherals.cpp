/*
 * Peripherals.cpp
 *
 *  Created on: Aug 5, 2011
 *      Author: DVD
 */

#include "Peripherals.h"

PeripheralContainer instance;

PeripheralContainer :: PeripheralContainer():
	_pcb(),
	_serial(_pcb),
	_intrCtrl(),
	_gpio(_pcb),
	_timer0(LPC2xxx_TIMER0)
{}

PeripheralContainer& PeripheralContainer::GetInstance(){return instance;}
