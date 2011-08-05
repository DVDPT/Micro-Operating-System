/*
 * LPC2294_GPIO.cpp
 *
 *  Created on: 20 de Mai de 2011
 *      Author: Sorcha
 */

#include "GPIO.h"
#include "Bits.h"
#include "PeripheralsAddress.h"
#include "PinConnectBlock.h"

#define PINSELECT_GPIOMASK 0



/*Construtores*/


GPIO::GPIO(PinConnectBlock& p): _gpio((LPC22xx_GPIO)GPIO_BASE_ADDRESS),_selectPin(p)
{

}


void GPIO::PinSelect(U32 pin)
{
	_gpio->IODIR_PORT1 = pin;
}

void GPIO::SetPin(U32 maskPin)
{
	_gpio->IODIR_PORT1 = maskPin;
}

void GPIO::SetBits(U32 mask)
{
	_gpio->IOSET_PORT1 = mask;
}

void GPIO::ResetBits(U32 mask)
{
	_gpio->IOCLR_PORT1 = mask;
}

void GPIO::SetValue(U32 pin, U32 value, U32 mask)
{
	SetBits((value<<pin) & mask);
	ResetBits((~value<<pin) & mask);
}


void GPIO::SetPinWrite(U32 pin, U32 size)
{
	SetPin(_gpio->IODIR_PORT1 | Bits<U32>::SetBits(pin,size));
}

void GPIO::SetPinRead(U32 pin, U32 size)
{
	SetPin(_gpio->IODIR_PORT1 & ~(Bits<U32>::SetBits(pin,size)));

}

void GPIO::WriteValue(U32 value,U32 pin, U32 size)
{
	SetValue(pin, value,(Bits<U32>::SetBits(pin,size)));

}

U32 GPIO::ReadValue(U32 pin, U32 size)
{
	return ((_gpio->IOPIN_PORT1 >> pin) & (Bits<U32>::SetBits(size)));

}

void GPIO::InitializePinAsGPIO(U32 pin)
{
	_selectPin.pinSelect(pin,PINSELECT_GPIOMASK);

}


