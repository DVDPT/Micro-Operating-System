#pragma once
typedef unsigned int U32;

#define INTERRUPT_PRIORITY_REGISTER_SIZE (64)
#define INTERRUPT_REQUEST_REGISTER_SIZE (64)
#define INTERRUPT_LEVEL_CAUSES_SIZE (4)

struct UC3InterruptController
{
private:
	
	
	///
	///	Interrupt Priority Registers
	///
	U32 IPR[INTERRUPT_PRIORITY_REGISTER_SIZE];
	
	///
	///	Interrupt Request Registers
	///
	U32 IRR[INTERRUPT_REQUEST_REGISTER_SIZE];
	
	///
	///	Interrupt Cause registers
	///
	U32 ICRn[INTERRUPT_LEVEL_CAUSES_SIZE];
	
public:

	void Init();
	U32 GetCauseIndex();
	
};