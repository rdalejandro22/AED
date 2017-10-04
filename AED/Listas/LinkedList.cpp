#include "iostream"
using namespace std;
class Nodo
{
public:
	int val;
	Nodo *next;
	Nodo(int val, Nodo* sig)
	{
		this->val = val;
		next = sig;
	}
};
class LinkedList
{
public:
	Nodo *head;
	LinkedList()
	{
		head = NULL;
	};
	LinkedList(int tam)
	{
		Nodo *aux = new Nodo(1, NULL);
		head = aux;
		for (int i = 3; i <= tam; i=i+2)
		{
			aux->next = new Nodo(i, NULL);
			aux = aux->next;
		}
		aux->next = NULL;
	};
	void print()
	{
		Nodo *temp;
		temp = head;
		while(temp)
		{
			cout << temp->val << ",";
			temp = temp->next;
		}
		cout << endl;
	}
	
	
	bool find_simple(int x, Nodo *&ptr)
	{
		ptr = head;
		///Lista Vacia
		if(ptr == NULL)
		{
			return 0;
		}
		while(ptr->next != NULL && ptr->next->val < x)
		{
			ptr = ptr->next;
		}
		return ptr->next && ptr->next->val == x;
	}
	bool insert_simple(int x)
	{
		Nodo *ptr;
		if(find_simple(x, ptr))
		{
			return 0;
		}
		///Insert Lista Vacia
		if(ptr == NULL)
		{
			Nodo *temp = new Nodo(x, head);
			head = temp;
			return 1;
		}
		///Insert Lista 1er elemento
		if(x < ptr->val)
		{
			Nodo *temp = new Nodo(x, head);
			head = temp;
			return 1;
		}
		Nodo *temp = new Nodo(x, ptr->next);
		ptr->next = temp;
		return 1;
	}
	bool del_simple(int x)
	{
		Nodo *ptr;
		if(!find_simple(x, ptr))
		{
			if(ptr == head)
			{
				Nodo *temp = head;
				head = head->next;
				delete temp;
				return 1;
			}
			return 0;
		}
		Nodo *temp = ptr->next;
		ptr->next = ptr->next->next;
		delete temp;
		return 1;
	}
	bool find_doble(int x, Nodo **&ptr)
	{
		ptr = &head;
		while(*ptr != NULL && (*ptr)->val < x)
		{
			ptr = &((*ptr)->next);
		}
		return *ptr && (*ptr)->val == x;
	}
	bool insert_doble(int x)
	{
		Nodo **ptr;
		if (find_doble(x, ptr))
		{
			return 0;
		}
		Nodo *temp = new Nodo(x, NULL);
		temp->next = *ptr;
		*ptr = temp;
	}
	bool del_doble(int x)
	{
		Nodo **ptr;
		if(!find_doble(x, ptr))
		{
			return 0;
		}
		Nodo *del = *ptr;
		*ptr = (*ptr)->next;
		delete ptr;
		return 1;
	}
};
int main()
{
	LinkedList list;
	list.head = NULL;
	list.insert_simple(1);
	list.insert_simple(2);
	list.insert_simple(4);
	list.insert_simple(3);
	list.insert_simple(0);
	list.insert_simple(10);
	list.insert_simple(9);
	list.insert_simple(-1);
	list.print();
	list.del_simple(-1);
	list.del_simple(0);
	list.del_simple(10);
	list.del_simple(4);
	list.print();
	return 0;
}
