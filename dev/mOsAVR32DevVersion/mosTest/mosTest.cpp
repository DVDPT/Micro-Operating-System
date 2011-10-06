/*
 * mosTest.cpp
 *
 * Created: 03-10-2011 18:25:44
 *  Author: DVD
 */ 



class Cenas
{
	int x;
public:

	Cenas(int i)
	{
		
		i++;
		x = i;
	}

	
	int getT()
	{
		int val = x;
		val++;
	 return val; 
	 }	
};

	Cenas c(10) ;
	Cenas d(1);

int main(void)
{

	int i = c.getT();
	i+= d.getT();
    while(1)
    {
        i++;
    }
}