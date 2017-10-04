#include <iostream>
#include <stdlib.h>     
#include <time.h>
using namespace std;

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
void imprimir(int *array, int tam)
{
	for(int i = 0; i < tam; i++)
	{
		cout << *array << ",";
		array++;
	}
	cout << endl;
}

int *gen_array(int num)
{
	int *array = new int[num];
	srand (time(NULL));
	for(int i = 0; i < num; i++)
	{
		*(array + i) = rand()%1000; 
	}
	return array;
}
class Mayor
{
public:
	inline bool operator()(int a , int b){
		return a > b;
	}
};

class Menor
{
public:
	inline bool operator()(int a , int b){
		return a < b;
	}
};

template <class Type, class Comp>
class Cocktail
{
	Type *inicio, *final;
	Comp cmp;
public:
	Cocktail(Type *ini, Type *fin):inicio(ini),final(fin){}
	void sort();
	void print(Type *array, int tam);
};

template <class Type, class Comp>
void Cocktail<Type,Comp>::sort()
{
	bool cambio = true;
	Type *inicio_act = inicio;
	Type *final_act = final;
	while(cambio)
	{
		cambio = false;
		while(inicio < final_act)
		{
			if(cmp(*(inicio + 1), *inicio))
			{
				swap(inicio, (inicio + 1));
				cambio = true;
			}
			inicio++;
		}
		inicio = inicio_act + 1;
		while(final > inicio_act)
		{
			if(cmp(*final, *(final - 1)))
			{
				swap(final, (final - 1));
				cambio = true;
			}
			final--;
		}
		final = final_act - 1;
	}
}

template <class Type, class Comp>
void Cocktail<Type,Comp>::print(Type *array, int tam)
{
	cout << "[";
	for(int i = 0; i < tam; i++)
	{
		cout << *array << ",";
		array++;
	}
	cout << "]" << endl;
}

int main(int argc, char *argv[]) {
	int tam = 100000;
	clock_t t1,t2;
	int *longarray = gen_array(tam);
	//imprimir(longarray,tam);
	Cocktail <int,Menor> ck(longarray, (longarray+tam-1));
	t1=clock();
	//code goes here
	ck.sort();
	t2=clock();
	float diff ((float)t2-(float)t1);
	//ck.print(longarray,tam);
	cout<< "Time Functor: " << diff << endl;
	delete [] longarray;
	return 0;
}

