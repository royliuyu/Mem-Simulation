#include "Btree.h"
#include "BtreeNode.h"
#include<string>
#include<iostream>

using namespace std;

Btree::Btree(int tp)
{t=tp; root=NULL; }
void Btree::insert(int k)
{
	if(root==NULL)
	{
		root=new BtreeNode(t,true);
		root->keys[0]=k;
		root->n=1;
	}
	else
	{
		if(root->n ==2*t-1)//if root already full
		{
			BtreeNode *s=new BtreeNode(t,false);
			s->C[0] =root;
			s->splitchild(0,root);
			int i=0;
			if(s->keys[0]<k)
			i++;
			s->C[i]->insertnonfull(k);

			root=s;

		}
			else root->insertnonfull(k); //if there is some space in root

	}
}
void Btree::traverse()
{
	if(root!=NULL)
		root->traverse();
}


BtreeNode* Btree::search(int k)
	{ if(root==NULL)
		return NULL;
		else root->search(k);

	}

void Btree::remove(int k)
{
    if (!root)
    {
        cout << "The tree is empty\n";
        return;
    }
 
    // Call the remove function for root
    root->remove(k);
 
    // If the root node has 0 keys, make its first child as the new root
    //  if it has a child, otherwise set root as NULL
    if (root->n==0)
    {
        BtreeNode *tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->C[0];
 
        // Free the old root
        delete tmp;
    }
    return;
}
