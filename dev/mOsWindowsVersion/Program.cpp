#include "X89Port.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE_OF_STACK (1000)
Task arr[10];
Thread arr2[10];
char stack[SIZE_OF_STACK];
int main()
{
	Thread t(stack,SIZE_OF_STACK);

	UtThread& x = Thread::GetCurrentThread();

	t.Start();
	system("pause");
}