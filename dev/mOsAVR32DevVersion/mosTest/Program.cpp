/*
 * Program1.cpp
 *
 * Created: 07-10-2011 11:08:18
 *  Author: DVD
 */ 
#include "AVR32Context.h"
#include "UC3A3256.h"


AVR32Context mainthread;

AVR32Context * maint;
AVR32Context * secondt;

U32 someStack[1024*2];

extern "C" void ContextSwitch(AVR32Context ** first, AVR32Context ** second);

extern  void initialize();
extern U32 getTickCount();

void init()
{
	INTC->Init();
	initialize();
}

void somefunc()
{
	int i = 0;
	i++;
	i+=4;
	ContextSwitch(&secondt, &maint);
	i++;
	ContextSwitch(&secondt, &maint);
}

int main()
{
	int tc = 0;
	init();
	maint = &mainthread;
	secondt = (AVR32Context *)((&someStack[1023]) - sizeof(AVR32Context));
	while(1)
	{
		tc = getTickCount();
		tc++;
	}
	
	/*/
	secondt->SetThreadStartFunction(somefunc);
	ContextSwitch(&maint, &secondt);
	AVR32Context::AVR32Flags flags = maint->sr;
	ContextSwitch(&maint, &secondt);
	int i = flags.mode;
	i++;
	i+=4;
	//*/
	return 0;
}