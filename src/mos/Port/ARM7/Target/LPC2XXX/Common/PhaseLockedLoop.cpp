/*
 * PhaseLockedLoop.cpp
 *
 *  Created on: Aug 2, 2011
 *      Author: Sorcha
 */

#include "PhaseLockedLoop.h"

#define DEFAULT_MULTIPLER 4
#define DEFAULT_DIVIDER 1
#define APROVE_COMMAND 0xAA
#define VALUE_COMMAND 0x55
#define ONPLL 0x1
#define PLL_M_MAX_VALUE (32)
#define PLL_M_MIN_VALUE (1)

PhaseLockedLoop::PLLRegisters PhaseLockedLoop::_pllRegs = PLL_BASE_ADDRESS;



void PhaseLockedLoop::Aprove()
{
	_pll->PLLFEED = APROVE_COMMAND;
	_pll->PLLSTAT = VALUE_COMMAND;
}
void PhaseLockedLoop::Configure(U32 m, U32 p)
{

}
void PhaseLockedLoop::Stop()
{
	_pll->PLLCON = 0x1;
	Aprove();
	_pll->PLLCON = 0x0;
	Aprove();
}


void PhaseLockedLoop::Start()
{
	_pll->PLLCON = ONPLL; //Liga a PLL
	Aprove();
	//while(!(_pll->PLLSTAT & PLL_LOCK)); //Espera ate o sinal ficar igual, aka, periodico aka estabelizou cara, puxa ai nessa
	_pll->PLLCON = 0x3; //Coloca a saida do MUX à saida da PLL
	Aprove();
}

void PhaseLockedLoop::SetClock(U8 clock)
{
	///
	///	m = FOSC / CCLK
	///
	U32 m = clock / CLOCK_CRYSTAL_FREQUENCY;

	DebugAssertTrue(m >= PLL_M_MIN_VALUE && m <= PLL_M_MAX_VALUE);




}

void PhaseLockedLoop::GetPLLPValue()
{

}
