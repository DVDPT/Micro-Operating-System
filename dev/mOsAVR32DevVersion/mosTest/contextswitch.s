/*
 * contextswitch.cpp
 *
 * Created: 07-10-2011 11:25:37
 *  Author: DVD
 */ 

 .equ R12_TO_R9_LR_REGISTERS_SIZE, (4*5)
 .equ STATUS_REGISTER_ADDRESS, (0)
 .text
 .global ContextSwitch

 ///
 ///	R12 have the current thread pointer, R11 the next thread pointer.
 ///
 ContextSwitch:

///
///	Store r8
///
	stm --sp, r8

///
///	Sub stack pointer 4 registers down, R12-R9 don't need to be saved,
///	because they were saved on the call to this function.
///
	sub sp,R12_TO_R9_LR_REGISTERS_SIZE

///
///	Store the lr as the context program counter.
///
	st.w --sp, lr

///
///	Save the status register.
///
	mfsr r8,STATUS_REGISTER_ADDRESS
	st.w --sp, r8

///
///	Store the final registers.
///
	stm --sp, r0-r7

///
///	Set the stack point on the thread context.
///
	st.w r12,sp

///
///	Get the next thread context
///
	ld.w sp,r11

///
///	load the first registers
///
	ldm sp++, r0-r7

///
///	load the status register
///
	ld.w r8,sp++
	mtsr STATUS_REGISTER_ADDRESS,r8

///
///	Store the other registers
///
	ldm sp++, r8-r12,lr,pc

