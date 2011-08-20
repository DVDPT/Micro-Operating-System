//
#include <Threading.h>
#include <Interrupts.h>
#include <System.h>
#include <SystemTimer.h>

#define SIZE_OF_STACK (1024 * 4 * 4)
char stack3[SIZE_OF_STACK];
char stack2[SIZE_OF_STACK];
char stack[SIZE_OF_STACK];

volatile U32 counter;

Mutex mux;

Thread t(stack,SIZE_OF_STACK);
Thread t2(stack2,SIZE_OF_STACK );
Thread t3(stack3,SIZE_OF_STACK );

struct TestThreadArgs
{
	char print;
	U32 time;
	U32 count;
};

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

void Func(TestThreadArgs* arg)
{

	IOutputStream& c = System::GetStandardOutput();
	for(int i = 0; i<arg->time; ++i)
	{

		DebugAssertTrue(mux.Acquire());

		counter++;
		mux.Release();

		U64 time = System::GetTickCount();
		time+=10;
		while(System::GetTickCount() >= time);

	}
}
//*/
int main()
{

	TestThreadArgs arg1 = {'a',10,0};
	TestThreadArgs arg2 = {'b',10,0};
	TestThreadArgs arg3 = {'M',1000,0};
	TestThreadArgs arg4 = {'_',10 ,0};


	t.Start((ThreadFunction)Func,(ThreadArgument)&arg1);

	t2.Start((ThreadFunction)Func,(ThreadArgument)&arg2);

	t3.Start((ThreadFunction)Func,(ThreadArgument)&arg4);

	System::GetStandardOutput().Write('S');

	Func(&arg3);

	int val = counter;
	val++;
	//*/
	return 0;
}

