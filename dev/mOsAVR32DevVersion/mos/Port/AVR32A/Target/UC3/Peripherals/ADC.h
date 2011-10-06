#pragma once
#include "SystemTypes.h"
#include "LPC2xxxTypes.h"
#include "Bits.h"
#include "VectorInterruptController.h"
#include "PinConnectBlock.h"

class ADC {

private:
	struct LPC2xxxADC
	{
		LPC2xxx_REG ADCR;
		LPC2xxx_REG ADGDR;
		LPC2xxx_REG DUMMY;
		LPC2xxx_REG ADINTEN;
		LPC2xxx_REG ADDR[8];
		LPC2xxx_REG ADSTAT;
	};

	volatile LPC2xxxADC * _adc;

public:
	ADC(PinConnectBlock& p);
	ADC(PinConnectBlock& p, U8 clock);
	void SetClock(U8 clock);
	U16 GetSample();
};

