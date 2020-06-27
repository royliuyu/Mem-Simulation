#ifndef BTREENODE_H
#define BTREENODE_H

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
		// procs for deletion
		int findKey(int k);
		void remove(int k);
		void removeFromLeaf(int idx);
		void removeFromNonLeaf(int idx);
		int getPred(int idx);
		int getSucc(int idx);
		void fill(int idx);
		void borrowFromPrev(int idx);
		void borrowFromNext(int idx);
		void merge(int idx);

		friend class Btree; 
};
#endif
