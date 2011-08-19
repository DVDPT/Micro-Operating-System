//
#include <Threading.h>
#include <Interrupts.h>
#include <System.h>
#include <SystemTimer.h>

#define SIZE_OF_STACK (1024 * 4 * 4)
char stack3[SIZE_OF_STACK];
char stack2[SIZE_OF_STACK];
char stack[SIZE_OF_STACK];



Thread t2(stack2,SIZE_OF_STACK );
Thread t3(stack3,SIZE_OF_STACK );

struct TestThreadArgs
{
	char print;
	U32 time;
	U32 count;
};

void Func(TestThreadArgs* arg)
{

	while(true)
	{

		System::GetStandardOutput().Write(arg->print);
		for(int i = 0; i<10;++i)
			Thread::Yield();
		arg->count++;
		Thread::Sleep(arg->time);

	}
}
//*/
int main()
{

	Thread t(stack,SIZE_OF_STACK);
	TestThreadArgs arg1 = {'a',1,0};
	TestThreadArgs arg2 = {'b',1,0};
	TestThreadArgs arg3 = {'M',1,0};
	TestThreadArgs arg4 = {'_',1 ,0};


	t.Start((ThreadFunction)Func,(ThreadArgument)&arg1);

	t2.Start((ThreadFunction)Func,(ThreadArgument)&arg2);

	t3.Start((ThreadFunction)Func,(ThreadArgument)&arg4);

	System::GetStandardOutput().Write('S');

	Func(&arg3);
	//*/
	return 0;
}

