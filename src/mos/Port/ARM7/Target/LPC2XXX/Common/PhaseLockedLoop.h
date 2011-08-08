/*
 * PhaseLockedLoop.h
 *
 *  Created on: Aug 2, 2011
 *      Author: Sorcha
 */

#pragma once
#include "LPC2xxxTypes.h"
#include "PeripheralsAddress.h"
#include "Debug.h"

#define CLOCK_CRYSTAL_FREQUENCY (12)

class PhaseLockedLoop {

	struct PLLRegisters
	{
		LPC2xxx_REG PLLCON;
		LPC2xxx_REG PLLCFG;
		LPC2xxx_REG PLLSTAT;
		LPC2xxx_REG PLLFEED;

	};

	static PLLRegisters* _pllRegs;

	static U8 GetPLLPValue();
public:
	static void Aprove();
	static void Configure(U32 m, U32 p);
	static void Stop();
	static void Start();
	static void SetClock(U8 clock);
};


