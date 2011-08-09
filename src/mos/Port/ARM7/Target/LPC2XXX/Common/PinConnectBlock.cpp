/*
 * PinConnectBlock.cpp
 *
 *  Created on: Aug 1, 2011
 *      Author: Sorcha
 */

#include "PinConnectBlock.h"
#include "Bits.h"
#include "LPC2xxx.h"

#define NUMBER_OF_BITS_OF_PINSEL 3
#define PORT1 4





PinConnectBlock::PinConnectBlock():_pinConnectBlock((LPC2294_PinConnectBlock)PCB_BASE_ADDRESS)
{
	_pinConnectBlock->PINSEl2 = Bits<U32>::ModifyBit(_pinConnectBlock->PINSEl2,3,0);
}

void PinConnectBlock:: pinSelect(U32 pin, U32 mask)
{
	if(pin > 15)
	{

		_pinConnectBlock->PINSEL0 |= 0x3 << pin*2;
		_pinConnectBlock->PINSEL1 = Bits<U32>::ModifyBits(((pin-16)*2),mask,_pinConnectBlock->PINSEL1,NUMBER_OF_BITS_OF_PINSEL);
	}
	else{
		_pinConnectBlock->PINSEL0 |= 0x3 << pin*2;
		_pinConnectBlock->PINSEL0 = Bits<U32>::ModifyBits(pin*2,mask,_pinConnectBlock->PINSEL0,NUMBER_OF_BITS_OF_PINSEL);
	}
}



