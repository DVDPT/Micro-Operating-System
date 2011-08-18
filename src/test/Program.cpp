//
#include <Threading.h>
#include <Interrupts.h>
#include <System.h>
#include <SystemTimer.h>

#define SIZE_OF_STACK (1024 * 4 * 4)
char stack2[SIZE_OF_STACK];
char stack[SIZE_OF_STACK];



Thread t2(stack2,SIZE_OF_STACK );
struct TestThreadArgs
{
	char print;
	U32 time;
};

void Func(TestThreadArgs* arg)
{

	System::DisableInterrupts();
	while(true)
	{

		System::GetStandardOutput().Write(arg->print);
		Thread::Sleep(arg->time);

	}
}
//*/
int main()
{
	Thread t(stack,SIZE_OF_STACK);
	TestThreadArgs arg1 = {'a',2000};
	TestThreadArgs arg2 = {'b',5000};
	TestThreadArgs arg3 = {'M',1000};

	System::DisableInterrupts();
	t.Start((ThreadFunction)Func,(ThreadArgument)&arg1);

	t2.Start((ThreadFunction)Func,(ThreadArgument)&arg2);

	System::GetStandardOutput().Write('S');

	Func(&arg3);
	//*/
	return 0;
}

