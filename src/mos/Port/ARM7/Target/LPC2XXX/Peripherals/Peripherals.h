/*
 * Peripherals.h
 *
 *  Created on: Aug 5, 2011
 *      Author: DVD
 */

#pragma once

#include "UART0.h"
#include "VectorInterruptController.h"
#include "GPIO.h"
#include "PinConnectBlock.h"
#include "Timer.h"

class PeripheralContainer
{
	PinConnectBlock _pcb;
	UART0 _serial;
	VectorInterruptController _intrCtrl;
	GPIO _gpio;
	Timer _timer0;

public:
	PeripheralContainer():
		_pcb(),
		_serial(_pcb),
		_intrCtrl(),
		_gpio(_pcb),
		_timer0(LPC2xxx_TIMER0)
	{}

	UART0& GetUart0Instance(){return _serial;}
	VectorInterruptController& GetVic(){return _intrCtrl;}
	GPIO& GetGpio(){return _gpio;}
	Timer& GetTimer0(){ return _timer0; }

	static PeripheralContainer& GetInstance();
};
