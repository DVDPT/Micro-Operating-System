/*
 * PhaseLockedLoop.cpp
 *
 *  Created on: Aug 2, 2011
 *      Author: Sorcha
 */

#include "PhaseLockedLoop.h"
#include "PeripheralsAddress.h"

#define DEFAULT_MULTIPLER 4
#define DEFAULT_DIVIDER 1
#define APROVE_COMMAND 0xAA
#define VALUE_COMMAND 0x55
#define ONPLL 0x1

PhaseLockedLoop PhaseLockedLoop::_instance;
PhaseLockedLoop::PhaseLockedLoop():_pll((LPC22xx_PLL)PLL_BASE_ADDRESS) {
}

PhaseLockedLoop PhaseLockedLoop::getInstance()
{
	return _instance;
}

void PhaseLockedLoop::aprove()
{
	_pll->PLLFEED = APROVE_COMMAND;
	_pll->PLLSTAT = VALUE_COMMAND;
}
void PhaseLockedLoop::configuration(U32 m, U32 p)
{

}
void PhaseLockedLoop::stop()
{
	_pll->PLLCON = 0x1;
	aprove();
	_pll->PLLCON = 0x0;
	aprove();
}


void PhaseLockedLoop::start()
{
	_pll->PLLCON = ONPLL; //Liga a PLL
	aprove();
	//while(!(_pll->PLLSTAT & PLL_LOCK)); //Espera ate o sinal ficar igual, aka, periodico aka estabelizou cara, puxa ai nessa
	_pll->PLLCON = 0x3; //Coloca a saida do MUX à saida da PLL
	aprove();
}
