//
#include <Threading.h>
#include <Interrupts.h>
#include <System.h>
#include <Mutex.h>
#include <SystemTimer.h>

#define SIZE_OF_STACK (1024 * 4 * 4)
char stack5[SIZE_OF_STACK];
char stack4[SIZE_OF_STACK];
char stack3[SIZE_OF_STACK];
char stack2[SIZE_OF_STACK];
char stack[SIZE_OF_STACK];

volatile U32 counter;

Mutex mux;

Thread t(stack,SIZE_OF_STACK);
Thread t2(stack2,SIZE_OF_STACK );
Thread t3(stack3,SIZE_OF_STACK );
Thread t4(stack4,SIZE_OF_STACK );
Thread t5(stack5,SIZE_OF_STACK );

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
	U64 time = System::GetTickCount() + 1000;
	//for(int i = 0; i<arg->time; ++i)
	while(true)
	{

		DebugAssertTrue(mux.Acquire());

		Thread::Yield();
		Thread::Sleep(1);
		counter++;

		mux.Release();
		if(System::GetTickCount() >= time)
		{
			time = System::GetTickCount() + 1000;
			System::GetStandardOutput().Write(arg->print);
		}



	}
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


	t.Start((ThreadFunction)Func,(ThreadArgument)&arg1);

	t2.Start((ThreadFunction)Func,(ThreadArgument)&arg2);

	t3.Start((ThreadFunction)Func,(ThreadArgument)&arg4);

	t4.Start((ThreadFunction)Func,(ThreadArgument)&arg5);
	t5.Start((ThreadFunction)Func,(ThreadArgument)&arg6);

	System::GetStandardOutput().Write('S');

	Func(&arg3);

	int val = counter;
	val++;
	//*/
	return 0;
}

