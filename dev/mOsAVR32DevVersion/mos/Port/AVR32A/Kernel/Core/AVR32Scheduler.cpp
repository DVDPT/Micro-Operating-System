#include "Threading.h"




//extern "C" avr32_context_switch(Thread* oldThread, Thread* newThread);


NAKED void UScheduler::ContextSwitch(Thread* oldThread, Thread* newThread)
{
	avr32_context_switch(oldThread,newThread);
}


