//
#include <Threading.h>
#include <Interrupts.h>
#include <System.h>
#include <SystemTimer.h>

#define SIZE_OF_STACK (1024 * 4 * 4)
char stack2[SIZE_OF_STACK];
char stack[SIZE_OF_STACK];



Thread t2(stack2,SIZE_OF_STACK );


void Func(char c)
{

	while(true)
	{
		System::GetStandardOutput().Write(c);
		Thread::Sleep(1000);

	}
}
//*/
int main()
{
	//Thread t(stack,SIZE_OF_STACK);

	//t.Start((ThreadFunction)Func,(ThreadArgument)'b');

	//t2.Start((ThreadFunction)Func,(ThreadArgument)'c');
	System::DisableInterrupts();
	System::GetStandardOutput().Write('S');

	Func('_');
	//*/
	return 0;
}

