#include <iostream>
using namespace std;
class Node
	{
	public:
		int val;
		Node *left;
		Node *right;
		Node(int VAL, Node *l, Node *r)
		{
			val = VAL;
			left = l;
			right = r;
		}
};
class BTree
	{
	public:
		Node *root;
		bool search(int target, Node **& ptr)
		{
			ptr = &root;
			while(*ptr != NULL && target != (*ptr)->val)
			{
				if(target > (*ptr)->val)
				{
					ptr = &(*ptr)->right;
				}
				else
					ptr = &(*ptr)->left;
			}
			return *ptr && (*ptr)->val == target;
		}
		bool insert(int target)
		{
			Node **ptr;
			if(search(target, ptr)) return 0;
		}
};
int main(int argc, char *argv[]) {
	BTree tree;
	Node n0(0,NULL,NULL);
	Node n2(2,NULL,NULL);
	Node n1(1,&n0,&n2);
	Node n4(4,NULL,NULL);
	Node n3(3,&n1,&n4);
	tree.root = &n3;
	Node **ptr;
	cout << tree.search(0, ptr);
	return 0;
}

