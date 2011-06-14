
typedef void(*Constructor)();
void init_constructors(int * ctorsBegin, int* ctorsEnd)
{
	for(;ctorsBegin != ctorsEnd; ctorsBegin++)
	{
		((Constructor)*ctorsBegin)();
	}
}
