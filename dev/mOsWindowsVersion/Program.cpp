#include "X86Port.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE_OF_STACK (1000)
Task arr[10];
Thread arr2[10];

char stack[SIZE_OF_STACK];
int main()
{
	/*
	Thread t(stack,SIZE_OF_STACK);
	Thread& x = t;
	Thread * p = &x;
	*/

	
	int value = Bits<U8>::GetLowestBitSet(0x1);
	value = Bits<U8>::GetLowestBitSet(0xF0);
	value = Bits<U8>::GetLowestBitSet(0xA0);
	value = Bits<U8>::GetLowestBitSet(0x4);

//	t.Start();
	system("pause");
}