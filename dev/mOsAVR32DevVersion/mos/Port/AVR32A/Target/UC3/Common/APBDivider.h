#pragma once

#include "LPC2xxxTypes.h"

#define APB_MAX_DIVIDER (4)

struct APBDivider
{
private:
	LPC2xxx_REG APB;

#define APBDIV_MASK (0x3)
public:
	U8 GetClockDivider()
	{
		U8 dividers[] = {4,1,2};
		return dividers[APB & APBDIV_MASK];
	}

	void SetClockDivider(U8 divider)
	{
		APB = (divider == 4? 0 : divider) & APBDIV_MASK;
	}


};
