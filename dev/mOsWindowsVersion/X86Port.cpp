#include "X86Port.h"

X86Scheduler _scheduler;


///
///	Send to Base Scheduler this port ContextSwitch
///
X86Scheduler::X86Scheduler() : BaseUScheduler<X86Context>(X86ContextSwitch)
{

}

NAKED Void FASTCALL X86Scheduler::X86ContextSwitch(Thread* oldThread, Thread* newThread)
{
	__asm
	{
		///
		///	Store ebp, ebx, esi and edi on the current thread stack
		///
		push    ebp
		push    ebx
		push    esi
		push    edi
		
		///
		///	Save the position of the context on oldThread->_context
		///
		mov dword ptr [ecx + Thread::_context],esp 
		
		///
		///	Get back the old Context to pop it
		/// esp = newThread->_context
		///
		mov esp,dword ptr [edx + Thread::_context]
		
		///
		///	Replace the onde context
		///
		pop edi
		pop esi
		pop ebx
		pop ebp

		ret
	}
}
