#pragma once

#include "AVR32A.h"

struct AVR32Context
{


	union AVR32Flags
	{
		U32 status_register;
		struct
		{
			unsigned carry	:1;
			unsigned zero	:1;
			unsigned negative:1;
			unsigned overflow:1;
			unsigned saturation:1;
			unsigned lock:1;
			unsigned reserved:8;
			unsigned scratch:1;
			unsigned register_remap_enable:1;
			unsigned global_interrupt_mask:1;
			unsigned interrupt_level_0_mask:1;
			unsigned interrupt_level_1_mask:1;
			unsigned interrupt_level_2_mask:1;
			unsigned interrupt_level_3_mask:1;
			unsigned exception_mask:1;
			unsigned mode	:3;
			unsigned reserved2:1;
			unsigned debug_state:1;
			unsigned debug_state_mask:1;
			unsigned java_state:1;
			unsigned java_handle:1;
			unsigned reserved3:1;
			unsigned secure_state:1;
		};
	};

	U32 r7,r6,r5,r4,r3,r2,r1,r0;
	AVR32Flags sr;
	U32 pc;
	U32 lr,r12,r11,r10,r9,r8;
	
	
	
	void SetThreadStartFunction(void (*ThreadStart)())
	{
		sr.status_register = (AVR32_MODE_SUPERVISOR << AVR32_STATUS_REGISTER_MODE_POSITION) | (1 << AVR32_STATUS_REGISTER_GLOBAL_INTERRUPT_MASK_POSITION) ;
		r0  = 0x0101010;
		r1  = 0x1111000;
		r2  = 0x2222000;
		r3  = 0x3333000; 
		r4  = 0x1111111;
		r5  = 0x2222222;
		r6  = 0x3333333;
		r7  = 0x4444444;
		r8  = 0x5555555;
		r9  = 0x6666666;
		r10 = 0x7777777;
		r11 = 0x8888888;
		r12 = 0x9999999;
		lr = (U32)ThreadStart;
		pc = (U32)ThreadStart;
	}
};

void avr32_context_switch(void* oldThread, void* newThread);
