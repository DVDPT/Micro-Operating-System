/*
 * demo.c
 *
 * Created: 04-10-2011 18:22:45
 *  Author: DVD
 */ 



int somefunc2(int i, int j, int h, int f)
{
	//for(int i = 0; i < 32; ++i)
	return 10;	
}


int somefunc(int i, int j, int h, int f)
{
	for(int i = 0; i < 32; ++i)
	somefunc2(4,3,2,1);
	return 10;	
}

int main(void)
{
	int stack = 2;
	for(int i = 0; i < 32; ++i)
	{

		stack = somefunc(1,2,3,4);
	}	
	return 1;
}