/*
 * PhaseLockedLoop.h
 *
 *  Created on: Aug 2, 2011
 *      Author: Sorcha
 */

#pragma once
#include "LPC2xxxTypes.h"

class PhaseLockedLoop {

	typedef struct _PLL
	{
		LPC2xxx_REG PLLCON;
		LPC2xxx_REG PLLCFG;
		LPC2xxx_REG PLLSTAT;
		LPC2xxx_REG PLLFEED;

	}*LPC22xx_PLL;

	LPC22xx_PLL _pll;
	U32 _multiplier ;
	U32 _divider;

	static PhaseLockedLoop _instance;
public:
	PhaseLockedLoop();
	PhaseLockedLoop getInstance();
	void aprove();
	void configuration(U32 m, U32 p);
	void stop();
	void start();
};


