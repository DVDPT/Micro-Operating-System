/*
 * LPC2294_GPIO.h
 *
 *  Created on: 20 de Mai de 2011
 *      Author: Sorcha
 */
#pragma once

#include "LPC2xxxTypes.h"
#include "PinConnectBlock.h"



class GPIO{

private:

	typedef struct _GPIO
	{
		LPC2xxx_REG IOPIN_PORT0;
		LPC2xxx_REG IOSET_PORT0;
		LPC2xxx_REG IODIR_PORT0;
		LPC2xxx_REG IOCLR_PORT0;
		LPC2xxx_REG IOPIN_PORT1;
		LPC2xxx_REG IOSET_PORT1;
		LPC2xxx_REG IODIR_PORT1;
		LPC2xxx_REG IOCLR_PORT1;

	}*LPC22xx_GPIO;

	LPC22xx_GPIO _gpio;
	PinConnectBlock& _selectPin;
	void PinSelect(U32 pin);
	void SetPin(U32 maskPin);
	void SetBits(U32 mask);
	void ResetBits(U32 mask);
	void SetValue(U32 pin, U32 value, U32 mask);


public:


	GPIO(PinConnectBlock& p);

	void InitializePinAsGPIO(U32 pin);
	void SetPinWrite(U32 pin, U32 size);
	void SetPinRead(U32 pin, U32 size);
	void WriteValue(U32 value,U32 pin, U32 size);
	U32 ReadValue(U32 pin, U32 size);

};


