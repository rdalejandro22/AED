#include <iostream>
#include <iomanip>
#include <stack>
#include <vector>
#include <stdlib.h>

using namespace std;

template <class T>
class C_Node
{

public:
    T value;
    C_Node <T> *leafs[2];
    int h_r;
    int h_l;

public:
    C_Node(T value, C_Node <T> *left, C_Node <T> *right)
    {
        this->value = value;
        leafs[0] = left;
        leafs[1] = right;
        h_r = 0;
        h_l = 0;
    }
};

template <class T>
class AVL_Tree
{

public:
    C_Node <T> *root = NULL;

public:
    void update_high(C_Node <T> *&node)
    {
        if(node->leafs[0])
        {
            if(node->leafs[0]->h_l < node->leafs[0]->h_r)
            {
                node->h_l = node->leafs[0]->h_r + 1;
            }
            else
            {
                node->h_l = node->leafs[0]->h_l + 1;
            }
        }
        else
        {
            node->h_l = 0;
        }
        if(node->leafs[1])
        {
            if(node->leafs[1]->h_l < node->leafs[1]->h_r)
            {
                node->h_r = node->leafs[1]->h_r + 1;
            }
            else
            {
                node->h_r = node->leafs[1]->h_l + 1;
            }
        }
        else
        {
            node->h_r = 0;
        }
    }
    bool search_node(T target, C_Node <T> **& ptr, vector <C_Node <T> **> &path)
    {
        ptr = &root;
        while(*ptr != NULL && target != (*ptr)->value)
        {
            path.push_back(ptr);
            if(target > (*ptr)->value)
            {
                ptr = &(*ptr)->leafs[1];
            }
            else
                ptr = &(*ptr)->leafs[0];
        }
        return *ptr && (*ptr)->value == target;
    }
    bool rotation_RR(C_Node <T> *&root)
    {
        C_Node <T> *newroot = root->leafs[1];
        root->leafs[1] = newroot->leafs[0];
        newroot->leafs[0] = root;
        root = newroot;
        return 1;
    }
    bool rotation_LL(C_Node <T> *&root)
    {
        C_Node <T> *newroot = root->leafs[0];
        root->leafs[0] = newroot->leafs[1];
        newroot->leafs[1] = root;
        root = newroot;
        return 1;
    }
    bool rotation_RL(C_Node <T> *&root)
    {
        C_Node <T> *newroot = root->leafs[1]->leafs[0];
        root->leafs[1]->leafs[0] = newroot->leafs[1];
        newroot->leafs[1] = root->leafs[1];
        root->leafs[1] = newroot->leafs[0];
        newroot->leafs[0] = root;
        root = newroot;
        return 1;
    }
    bool rotation_LR(C_Node <T> *&root)
    {
        C_Node <T> *newroot = root->leafs[0]->leafs[1];
        root->leafs[0]->leafs[1] = newroot->leafs[0];
        newroot->leafs[0] = root->leafs[0];
        root->leafs[0] = newroot->leafs[1];
        newroot->leafs[1] = root;
        root = newroot;
        return 1;
    }
    bool balance(C_Node <T> **&root)
    {
        if((*root)->h_r - (*root)->h_l == -2)
        {
            if((*root)->leafs[0]->h_l >= (*root)->leafs[0]->h_r)
            {
                rotation_LL((*root));
                return 1;
            }
            else
                rotation_LR((*root));
                return 1;
        }
        else if((*root)->h_r - (*root)->h_l == 2)
        {
            if((*root)->leafs[1]->h_r >= (*root)->leafs[1]->h_l)
            {
                rotation_RR((*root));
                return 1;
            }
            else
                rotation_RL((*root));
                return 1;
        }
        return 0;
    }
    bool insert_node(T target)
    {
        C_Node <T> **ptr;
        vector <C_Node <T> **> path;
        if(search_node(target, ptr, path)) return 0;
        C_Node <T> *newNode = new C_Node <T> (target, NULL , NULL);
        *ptr = newNode;
        for(int i = path.size() - 1; i >= 0; i--)
        {
            update_high(*path[i]);
            if(balance(path[i]))
            {
                update_high((*path[i])->leafs[0]);
                update_high((*path[i])->leafs[1]);
                update_high(*path[i]);
            }
        }
        return 1;
    }
    bool delete_node(T target)
    {
        C_Node <T> **ptr;
        vector <C_Node <T> **> path;
        if(!search_node(target, ptr, path)) return 0;
        if((*ptr)->leafs[0] && (*ptr)->leafs[1])
        {
            C_Node<T> **q = ptr;
            q = &((*q)->leafs[1]);
            while((*q)->leafs[0])
            {
                q = &((*q)->leafs[0]);
            }
            (*ptr)->value = (*q)->value;
            ptr = q;
        }
        C_Node<T> *t = *ptr;
        *ptr = (*ptr)->leafs[(*ptr)->leafs[1] != 0];
        delete t;
        for(int i = path.size() - 1; i >= 0; i--)
        {
            update_high(*path[i]);
            if(balance(path[i]))
            {
                update_high((*path[i])->leafs[0]);
                update_high((*path[i])->leafs[1]);
                update_high(*path[i]);
            }
        }
        return 1;
    }
    void print(C_Node <T> *p, int indent = 0)
    {
        if(p != NULL) {
            if(p->leafs[1])
            {
                print(p->leafs[1], indent + 4);
            }
            if(indent)
            {
                cout << setw(indent) << ' ';
            }
            if(p->leafs[1]) cout <<" /\n" << setw(indent) << ' ';
            cout << p->value << "\n ";
            //cout << p->value << "(" << p->h_l << "," << p->h_r << ")" << "\n ";
            if(p->leafs[0])
            {
                cout << setw(indent) << ' ' << " \\\n";
                print(p->leafs[0], indent + 4);
            }
        }
    }
};

int main()
{
    AVL_Tree <int> tree;
    tree.insert_node(1);
    tree.insert_node(8);
    tree.insert_node(3);
    tree.insert_node(7);
    tree.insert_node(2);
    tree.insert_node(9);
    tree.insert_node(4);
    tree.insert_node(5);
    tree.insert_node(6);
    tree.print(tree.root);
    cout << "---------------------" << endl;
    tree.delete_node(3);
    tree.print(tree.root);
    cout << "---------------------" << endl;
    tree.delete_node(4);
    tree.print(tree.root);
    return 0;
}
