#ifndef BTREE_H
#define BTREE_H
#include "BtreeNode.h"
class Btree
{
	BtreeNode *root;
	int t;
public:
	Btree(int tp);// constructor
	

	void traverse();
	
	BtreeNode* search(int k);
	
	void insert(int k);
	void remove(int k);
};
#endif
