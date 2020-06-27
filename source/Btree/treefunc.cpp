/*#include<iostream.h>*/
#include<iostream>
using namespace std;

class BtreeNode
{	int *keys;
	int t; //min degree
	BtreeNode **C;
	int n;
	bool leaf;

	public:
	BtreeNode(int tp, bool leafp);
	void traverse();

	BtreeNode *search(int k);
	void insertnonfull(int k);
	void splitchild(int i, BtreeNode *y);

	friend class Btree; 
};

class Btree
{
	BtreeNode *root;
	int t;
public:
	Btree(int tp)// constructor
	{t=tp; root=NULL; }

	void traverse()
	{ 
	if(root!=NULL)
	root->traverse();
	} 
	BtreeNode* search(int k)
	{ if(root==NULL)
		return NULL;
	else root->search(k);

	}
	void insert(int k);
};
BtreeNode::BtreeNode(int tp, bool leafp)// constructor
{
	t=tp;
	leaf=leafp;

	keys=new int[2*t-1];
	C=new BtreeNode *[2*t];
	n=0;
}
//traverse the node and its childs
void BtreeNode::traverse()
{
	int i;
	for(i=0;i<n;i++)
	{
		if(leaf==false)
	     
		C[i]->traverse();//recursively move down the child nodes
		cout<<" "<<keys[i];		
				

	}
	if(leaf==false)
	C[i]->traverse();

}

BtreeNode* BtreeNode::search(int k)
{
int i=0;
while(i<n && k>keys[i])
i++;

if(keys[i]==k)
return this;

if(leaf==true)
return NULL;

return C[i]->search(k);

}

void Btree::insert(int k)
{
	if(root==NULL)
	{
	root=new BtreeNode(t,true); // original is Btreenode
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

void BtreeNode::insertnonfull(int k)
{
	int i=n-1; 
	if(leaf==true)// check if the node is leaf
{
  	while(i>=0 && keys[i]>k)
	{
	keys[i+1]=keys[i];
	i--;


	}
//found the location where new key is to be inserted
	keys[i+1]=k;
	n=n+1; //update number of keys
}
else //if node is non leaf
{
	while(i>=0 && keys[i] >k)
	i--;
 //obtained the location of child which can have the key
	if(C[i+1]->n ==2*t-1) //check if that child is full
	{
	splitchild(i+1, C[i+1]);
	if(keys[i+1]<k)
	i++;
	}
C[i+1]->insertnonfull(k);
}



}

void BtreeNode::splitchild(int i, BtreeNode *y)
{
	//allocate a new node
	BtreeNode *z = new BtreeNode(y->t, y->leaf);
	z->n=t-1; //split satisfying the minimum condition
	//copy t-1 keys from y to z
	int j;
	for(j=0;j<t-1;j++)
	z->keys[j]=y->keys[j+t];
	if(y->leaf ==false)
	{
	for(j=0;j<t;j++)
	z->C[j]=y->C[j+t];

	}
	y->n =t-1; //update y with number of keys remaining
	for(j=n-1;j>=i;j--)
	C[j+1]=C[j];

	C[i+1]=z;
for (j = n-1; j >= i; j--)
        keys[j+1] = keys[j];
    // Copy the middle key of y to this node
    keys[i] = y->keys[t-1];
 
    // Increment count of keys in this node
    n = n + 1;
 
    

}


