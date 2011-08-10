/*
 * VectorIntreeuptController.cpp
 *
 *  Created on: 21 de Jun de 2011
 *      Author: Sorcha
 */

#include "VectorInterruptController.h"


#define VICVectCntl_IRQ_ENABLE (1<<5)
#define SIZE_OF_IRQS 16

extern "C" void arm_common_trap();

void empty_isr(){}


VectorInterruptController::VectorInterruptController()
	:	_interruptController((LPC22xx_VIC)VIC_BASE_ADDRESS)
{
	int i;
	for(i=0; i < SIZE_OF_IRQS; ++i)
	{
		_interruptController->VICVectAddrs[i] =  ((U32)&arm_common_trap);
		_interruptController->VICVectCntls[i] = 1<<i;
	}
	_interruptController->VICDefVectAddr = ((U32)&arm_common_trap);

}



void VectorInterruptController::SetISR(U32 entry, ISR function, U32 priority, U32 fiq)
{
	//_interruptController.VICVectAddrs[entry] =(U32)function;
	_interruptController->VICVectAddrs[priority] = (U32)function;
	//_isrs[entry] = function;
	_interruptController->VICVectCntls[priority] = (entry | VICVectCntl_IRQ_ENABLE) & 0x3F;

	_interruptController->VICIntSelect = Bits<U32>::ModifyBit(_interruptController->VICIntSelect,entry,fiq);
}

void VectorInterruptController::ModifyPriority(U32 entry, U32 priority)
{
	_interruptController->VICVectCntls[entry]|= (priority<<5);
}

void VectorInterruptController::UnmaskInterrupt(U32 irqIdx)
{
	_interruptController->VICIntEnable = (1 << irqIdx);

}
void VectorInterruptController::MaskInterrupt(U32 irqIdx)
{
	_interruptController->VICIntEnClr = (1 << irqIdx);
}
void VectorInterruptController::EndProcessTreatmentInterrupt()
{
	_interruptController->VICVectAddr = 0;
}

U32 VectorInterruptController::GetCurrentInterrupt()
{
	int irqsStatus, currentIrq;
	irqsStatus = _interruptController->VICIRQStatus;
	currentIrq = Bits<U32>::GetLowestBitSet(irqsStatus);

	return currentIrq;
}

void VectorInterruptController::EnableInterrupt()
{
	asm("mrs r0, cpsr");
	asm("bic r0, r0, #(3 << 6)");
	asm("msr cpsr_c, r0");
}
void VectorInterruptController::DisableInterrupt()
{
	asm("mrs r0, cpsr");
	asm("orr r0, r0, #(3 << 6)");
	asm("msr cpsr_c, r0");
}
