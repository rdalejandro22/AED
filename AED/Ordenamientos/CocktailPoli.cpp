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

void print(int *array, int tam)
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

class CocktailPoli
{
public:
	virtual bool comp(int a, int b) = 0; 
	void sort(int *p, int *q)
	{
		int *temp=p;
		bool intercambio=1;
		while(intercambio==1&&q>p){
			intercambio=0;
			for(;p<q;p++){
				if(comp(*p,*(p+1))){
					swap(p,p+1);
					intercambio=1;
				}
			}
			for(;q>temp;q--){
				if(comp(*(q-1),*q)){
					swap(q-1,q);
					intercambio=1;
				}
			}
			temp=q;
			q=p;
			temp++;
			p=temp;
			q--;
		}
	};
};

class Mayor: public CocktailPoli
{
public:
	bool comp(int a, int b)
	{
		return a > b;
	}
};

class Menor: public CocktailPoli
{
public:
	bool comp(int a, int b)
	{
		return a < b;
	}
};


int main(int argc, char *argv[]) 
{
	int tam = 1000000;
	clock_t t1,t2;
	Mayor a;
	int *array = gen_array(tam);
	
	//print(array, tam);
	
	t1=clock();
	//code goes here
	a.sort(array, array + tam - 1);
	//code goes here
	t2=clock();
	
	float diff ((float)t2-(float)t1);
	
	//print(array, tam);
	cout<< "Time Polimorfismo: " << diff << endl;
	
	delete [] array;
}

