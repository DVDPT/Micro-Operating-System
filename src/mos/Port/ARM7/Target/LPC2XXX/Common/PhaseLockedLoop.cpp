/*
 * PhaseLockedLoop.cpp
 *
 *  Created on: Aug 2, 2011
 *      Author: Sorcha
 */

#include "PhaseLockedLoop.h"

#define PLL_APROVE_COMMAND1 (0xAA)
#define PLL_APROVE_COMMAND2 (0x55)

#define PLL_M_MASK (0x1F)
#define PLL_P_MASK (0x3)

#define PLL_M_POSITION (0)
#define PLL_P_POSITION (5)

#define PLL_ON (0x1)
#define PLL_ENABLE (0x3)

#define PLL_OFF (0x1)
#define PLL_DISABLE (0x0)

#define PLL_STAT_LOCK_POSITION (10)
#define PLL_LOCK (0x1 << PLL_STAT_LOCK_POSITION)

#define PLL_M_MAX_VALUE (32)
#define PLL_M_MIN_VALUE (1)

#define PLL_CONNECTED (0x3<<8)

#define PPL_FCCO_MIN_VALUE (156)
#define PPL_FCCO_MAX_VALUE (320)

volatile PhaseLockedLoop::PLLRegisters * PhaseLockedLoop::_pllRegs = (volatile PLLRegisters *)PLL_BASE_ADDRESS;



void PhaseLockedLoop::Aprove()
{

	_pllRegs->PLLFEED = PLL_APROVE_COMMAND1;
	_pllRegs->PLLFEED = PLL_APROVE_COMMAND2;
}
void PhaseLockedLoop::Configure(U32 m, U32 p)
{
	_pllRegs->PLLCFG = (((m-1) & PLL_M_MASK) << PLL_M_POSITION) | ((p & PLL_P_MASK) << PLL_P_POSITION);

}

void PhaseLockedLoop::Stop()
{
	_pllRegs->PLLCON = PLL_OFF;
	Aprove();
	_pllRegs->PLLCON = PLL_DISABLE;
	Aprove();
}


void PhaseLockedLoop::Start()
{
	_pllRegs->PLLCON = PLL_ON;

	Aprove();

	while((_pllRegs->PLLSTAT & PLL_LOCK ) == 0 );

	_pllRegs->PLLCON = PLL_ENABLE;
	Aprove();
}

bool PhaseLockedLoop::SetClock(U16 clock)
{
	System::AcquireSystemLock();
	Stop();
	///
	///	m = FOSC / CCLK
	///
	if(clock == CLOCK_CRYSTAL_FREQUENCY)
	{
		System::ReleaseSystemLock();
		return true;
	}
	U32 m = clock / CLOCK_CRYSTAL_FREQUENCY;

	DebugAssertTrue(m >= PLL_M_MIN_VALUE && m <= PLL_M_MAX_VALUE);

	S32 p = GetPLLPValue(clock);

	DebugAssertNotEquals(-1,p);

	if(p == -1 || m < PLL_M_MIN_VALUE || m > PLL_M_MAX_VALUE)
		return false;

	Configure(m,p == 0x8 ? 0x3 : p);
	Start();

	System::ReleaseSystemLock();
	return true;

}

S8 PhaseLockedLoop::GetPLLPValue(U16 clock)
{

	U8 possiblePValues[] ={1,2,4,8};
	U8 p = -1;
	U16 clockTimesTwo = clock * 2;
	///
	///	p = Fcco / (clock * 2)
	///
	for(int i = 0; i < Arrays::Length(possiblePValues); ++i)
	{
		U32 fcco = possiblePValues[i] * clockTimesTwo;

		if(fcco >= PPL_FCCO_MIN_VALUE && fcco <= PPL_FCCO_MAX_VALUE )
		{
			p = possiblePValues[i];
			break;
		}
	}

	return p;
}

U16 PhaseLockedLoop::GetClock()
{
	return _pllRegs->PLLSTAT & PLL_CONNECTED? CLOCK_CRYSTAL_FREQUENCY * ((_pllRegs->PLLSTAT & PLL_M_MASK)+1) : CLOCK_CRYSTAL_FREQUENCY;
}
