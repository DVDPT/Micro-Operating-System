//
#include <Threading.h>
#include <Interrupts.h>
#include <System.h>
#include <SystemTimer.h>

#define SIZE_OF_STACK (1024 * 4 * 4)


char stack[SIZE_OF_STACK];



void Func()
{
	int i = 0;
	while(true)
	{
		System::GetStandardOutput().Write('b');
		while(i++ < 100000);
		i=0;

	}
}
//*/
int main()
{
	unsigned int i = 0;
	Thread t(stack,SIZE_OF_STACK);
	while(i++ <100000);
	System::GetStandardOutput().Write('S');
	//t.Start((ThreadFunction)Func,NULL);

	while(true)
	{
		System::GetStandardOutput().Write('_');
		while(i++ < 100000);
		i=0;

	}
	//*/
	return 0;
}

