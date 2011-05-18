#include "X86Port.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE_OF_STACK (1024 * 4)
Task arr[10];
Thread arr2[10];

char stack[SIZE_OF_STACK];

void Func()
{
	Thread::Yield();
}

int main()
{

	Thread t(stack,SIZE_OF_STACK);
	
	t.SetThreadPriority(4);
	t.Start((ThreadFunction)Func,NULL);

	Thread::Yield();

//	t.Start();
	system("pause");
}