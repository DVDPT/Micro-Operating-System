
#include <Threading.h>

#define SIZE_OF_STACK (1024 * 4)


char stack[SIZE_OF_STACK];
char stack2[SIZE_OF_STACK];


Thread t2();

void Func()
{
	Thread::Yield();
}

int main()
{
	unsigned int i = 0;

	Interlocked::Decrement(&i);
	//::CompareExchange((volatile unsigned int*)&i,123,123);

	Thread t(stack,SIZE_OF_STACK);
	t.Start((ThreadFunction)Func,NULL);

	Thread::Yield();
	//*/
	return 0;
}
