/*
 * VectorIntreeuptController.h
 *
 *  Created on: 21 de Jun de 2011
 *      Author: Sorcha
 */
#pragma once

#include "LPC2xxxTypes.h"
#include "LPC2xxx.h"
#include "Bits.h"

typedef void (*ISR)();

class VectorInterruptController {
private:
	typedef volatile struct _VIC
	{
		LPC2xxx_REG VICIRQStatus;
		LPC2xxx_REG VICFIQStatus;
		LPC2xxx_REG VICRawIntr;
		LPC2xxx_REG VICIntSelect;
		LPC2xxx_REG VICIntEnable;
		LPC2xxx_REG VICIntEnClr;
		LPC2xxx_REG VICSoftInt;
		LPC2xxx_REG VICSoftIntClear;
		LPC2xxx_REG VICProtection;
		LPC2xxx_REG DUMMY[3];
		LPC2xxx_REG VICVectAddr;
		LPC2xxx_REG VICDefVectAddr;
		LPC2xxx_REG DUMMY1[50];
		LPC2xxx_REG VICVectAddrs[16];
		LPC2xxx_REG DUMMY2[48];
		LPC2xxx_REG VICVectCntls[16];
	}*LPC22xx_VIC;

	volatile LPC22xx_VIC  _interruptController;
	ISR _isrs[16];



public:
	VectorInterruptController();
	void SetISR(U32 entry, ISR function, U32 priority, U32 fiq);
	void ModifyPriority(U32 entry, U32 priority);
	void UnmaskInterrupt(U32 irqIdx);
	void MaskInterrupt(U32 irqIdx);
	void EnableInterrupt();
	void DisableInterrupt();
	void EnableFiq();
	void DisableFiq();
	void EndProcessTreatmentInterrupt();
	///
	///	This method should only be called when an interrupt had occured.
	///
	U32 GetCurrentInterrupt();


};



