#include <iostream>
using namespace std;
class Node
{
public:
	int val;
	Node *next;
	Node *prev;
	Node(int val, Node *next, Node *prev)
	{
		this->val = val;
		this->next = next;
		this->prev = prev;
	}
};
class DoublyLL
{
public:
	Node *head;
	Node *tail;
	DoublyLL(){}
	DoublyLL(int tam)
	{
		Node *newNode = new Node(1,NULL,NULL);
		head = newNode;
		for(int i = 3; i <= tam; i=i+2)
		{
			newNode->next = new Node(i, NULL, newNode);
			newNode = newNode->next;
		}
		tail = newNode;
	}
	void head_print()
	{
	    Node *temp = head;
	    while(temp!=NULL)
        {
            cout << temp->val << ",";
            temp = temp->next;
        }
		cout << endl;
	}
	void tail_print()
	{
	    Node *temp = tail;
	    while(temp!=NULL)
        {
            cout << temp->val << ",";
            temp = temp->prev;
        }
		cout << endl;
	}
	bool doubly_search(int x, Node *&ptr)
	{
	    ptr = head;
	    while(ptr != NULL && ptr->val < x && ptr != tail)
        {
            ptr = ptr->next;
        }
        return ptr && ptr->val == x;
	}
	bool doubly_insert(int x)
	{
	    Node *ptr;
	    if(doubly_search(x, ptr))
        {
            return 0;
        }
		if(ptr == head)
		{
			Node *temp = new Node(x, ptr, NULL);
			ptr->prev = temp;
			head = temp;
			return 1;
		}
		if(ptr == tail)
		{
			Node *temp = new Node(x, NULL, ptr);
			ptr->next = temp;
			tail = temp;
			return 1;
		}
        Node *temp = new Node(x, ptr, ptr->prev);
        ptr->prev->next = temp;
        ptr->prev = temp;
		return 1;
	}
	bool doubly_del(int x)
	{
	    Node *ptr;
	    if(!doubly_search(x, ptr))
        {
            return 0;
        }
		if(ptr == head)
		{
			Node *temp = ptr;
			head = ptr->next;
			ptr->next->prev = ptr->prev;
			delete temp;
			return 1;
		}
		if(ptr == tail)
		{
			Node *temp = ptr;
			tail = ptr->prev;
			ptr->prev->next = ptr->next;
			delete temp;
			return 1;
		}
        Node *temp = ptr;
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
        delete temp;
		return 1;
	}
};
int main(int argc, char *argv[])
{
	DoublyLL dl;
	dl.head = NULL;
	dl.tail = NULL;
	dl.doubly_insert(1);
	dl.head_print();
	dl.tail_print();
	
	
	/*DoublyLL dll = DoublyLL(10);
	dll.head_print();
	dll.tail_print();
	
	dll.doubly_insert(0);
	dll.head_print();
    dll.tail_print();
    
    dll.doubly_insert(10);
    dll.head_print();
    dll.tail_print();
	
	dll.doubly_del(0);
	dll.head_print();
	dll.tail_print();
	
	dll.doubly_del(10);
	dll.head_print();
	dll.tail_print();*/
	return 0;
}

