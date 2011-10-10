
typedef void(*Constructor)();
void init_constructors(Constructor * ctorsBegin, Constructor * ctorsEnd)
{
	for(;ctorsBegin != ctorsEnd; ctorsBegin++)
	{
		(*ctorsBegin)();
	}
}

void init_bss(char * startBss, char* endBss)
{
	for( ; startBss != endBss; ++startBss)
	{
		*startBss = 0;
	}
}
