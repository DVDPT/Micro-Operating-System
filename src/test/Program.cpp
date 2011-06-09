#include <System.h>


#define SIZE_OF_STACK (1024 * 4)
Task arr[10];
Thread arr2[10];

char stack[SIZE_OF_STACK];

void Func()
{
	Thread::Yield();
}

void main()
{

	Thread t(stack,SIZE_OF_STACK);

	t.SetThreadPriority(4);
	t.Start((ThreadFunction)Func,NULL);

	Thread::Yield();
}
