/*
 * PhaseLockedLoop.h
 *
 *  Created on: Aug 2, 2011
 *      Author: Sorcha
 */

#pragma once
#include "LPC2xxxTypes.h"
#include "LPC2xxx.h"
#include "Debug.h"
#include "Arrays.h"
#include "System.h"

#define CLOCK_CRYSTAL_FREQUENCY (12)
#define CLOCK_MAX_FREQUENCY (60)
#define CLOCK_MIN_FREQUENCY (CLOCK_CRYSTAL_FREQUENCY)

#define CLOCK_PERIPHERALS_MAX_FREQUENCY (60)
#define CLOCK_PERIPHERALS_MIN_FREQUENCY (CLOCK_CRYSTAL_FREQUENCY / 4)

class PhaseLockedLoop {

	struct PLLRegisters
	{
		LPC2xxx_REG PLLCON;
		LPC2xxx_REG PLLCFG;
		LPC2xxx_REG PLLSTAT;
		LPC2xxx_REG PLLFEED;

	};

	static volatile PLLRegisters* _pllRegs;

	static S8 GetPLLPValue(U16 clock);
	static void Aprove();
	static void Configure(U32 m, U32 p);
	static void Stop();
	static void Start();
public:

	static bool SetClock(U16 clock);
	static U16 GetClock();
};


