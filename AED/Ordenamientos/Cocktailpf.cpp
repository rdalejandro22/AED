#include <iostream>
#include <stdlib.h>     
#include <time.h>
using namespace std;
template <class T>
T *gen_array(int num)
{
	T *array = new T[num];
	srand (time(NULL));
	for(int i = 0; i < num; i++)
	{
		*(array + i) = rand()%1000; 
	}
	return array;
}
template <class T>
void swap(T *a, T *b)
{
	T temp = *a;
	*a = *b;
	*b = temp;
}
template <class T>
void print(T *array, int tam)
{
	for(int i = 0; i < tam; i++)
	{
		cout << *array << ",";
		array++;
	}
	cout << endl;
}
template <class T>
bool mayor(T a, T b)
{
	return a > b;
}
template <class T>
bool menor(T a, T b)
{
	return a < b;
}
template <class T>
void mango(T *inicio, T *final, bool (*pf)(T a, T b))
{
	bool cambio = true;
	T *inicio_act = inicio;
	T *final_act = final;
	while(cambio)
	{
		cambio = false;
		while(inicio < final_act)
		{
			if(pf(*(inicio + 1), *inicio))
			{
				swap(inicio, (inicio + 1));
				cambio = true;
			}
			inicio++;
		}
		inicio = inicio_act + 1;
		while(final > inicio_act)
		{
			if(pf(*final, *(final - 1)))
			{
				swap(final, (final - 1));
				cambio = true;
			}
			final--;
		}
		final = final_act - 1;
	}
	
}
int main(int argc, char *argv[]) {
	int *array = gen_array<int>(10000);
	mango<int>(array, (array+9), menor);
	//print<int>(array, 10000);
	return 0;
}

