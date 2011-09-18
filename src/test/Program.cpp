//
#include <Threading.h>
#include <Interrupts.h>
#include <System.h>
#include <Mutex.h>
#include <SystemTimer.h>
#include <Timer.h>
#include <Peripherals.h>


struct TestThreadArgs
{
	char print;
	U32 time;
	U32 count;
};

Timer hardTimer(LPC2xxx_TIMER1);

void Func2(TestThreadArgs* arg)
{

	if(true)
	{

		System::GetStandardOutput().Write(arg->print);
		for(int i = 0; i<10;++i)
			Thread::Yield();
		arg->count++;
		Thread::Sleep(arg->time);
		System::DisableInterrupts();
	}
}

#define NR_OF_LOOPS (1000)

void Func(TestThreadArgs* arg)
{
/*/
	System::DisableInterrupts();
	volatile U64 time = System::GetTickCount();
	volatile U64 time2;
	U32 nrOfYields = NR_OF_LOOPS;
	U32 timea = hardTimer.GetTimerCount();
	//for(int i = 0; i<arg->time; ++i)
	while(nrOfYields-- != 0)
	{

		Thread::Yield();
	}

	hardTimer.Disable();
	System::DisableInterrupts();

	System::GetStandardOutput().Write("hard->");
	System::GetStandardOutput().Write((hardTimer.GetTimerCount() - timea) / NR_OF_LOOPS);
/*/
	while(true)
		Thread::Yield();

}
//*/
int main()
{

	TestThreadArgs arg1 = {'a',10,0};
	TestThreadArgs arg2 = {'b',10,0};
	TestThreadArgs arg3 = {'M',1000,0};
	TestThreadArgs arg4 = {'_',10 ,0};
	TestThreadArgs arg5 = {'O',10 ,0};
	TestThreadArgs arg6 = {'W',10 ,0};
	///
	///	timer in micros.
	///
	hardTimer.SetClock(60);

	System::DisableInterrupts();

	GPIO& gpio = PeripheralContainer::GetInstance().GetGpio();
	int * port0 = (int*)0xe0028008;
	*port0 |= 1<<10;
	port0 = (int*)0xe0028004;
	*port0 = (1<<10);
	port0 = (int*)0xe002800C;
	*port0 = (1<<10);

	System::DisableInterrupts();
	//t.Start((ThreadFunction)Func,(ThreadArgument)&arg1);
/*/
	t2.Start((ThreadFunction)Func,(ThreadArgument)&arg2);

	t3.Start((ThreadFunction)Func,(ThreadArgument)&arg4);

	t4.Start((ThreadFunction)Func,(ThreadArgument)&arg5);
	t5.Start((ThreadFunction)Func,(ThreadArgument)&arg6);
//*/
	//System::GetStandardOutput().Write('S');
	hardTimer.Enable();
	Func(&arg3);

	//int val = counter;
	//val++;
	//*/
	return 0;
}

