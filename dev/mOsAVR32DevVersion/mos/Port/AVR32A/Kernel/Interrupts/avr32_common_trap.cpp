/*
 * avr32_common_trap.cpp
 *
 * Created: 24-10-2011 16:53:44
 *  Author: DVD
 */ 

#include "AVR32Context.h"
#include "Timer.h"
#include "UC3A3256.h"

extern AVR32Context * secondt;

extern "C" void avr32_common_trap(AVR32Context** context)
{
	U32 sr = TC0->SR;
	U32 cause = INTC->ICRn[0];
	cause = INTC->ICRn[1];
	cause = INTC->ICRn[2];
	cause = INTC->ICRn[3];
	cause++;
	*context = secondt;
	
}