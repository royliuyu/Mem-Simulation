#include<iostream>
#include "Btree.h"
#include "BtreeNode.h"
#include <windows.h>   
#include <fstream>
#include <string>	//run in windows
//#include <cstring>  //run in linux
extern "C"{
#include "sha3.h" 
} 

#define CPU_FREQUENCY 3300000000 //3.33G
#define SOURCE_FILE "protein.info.v11.0_1M.txt"
#define OUTLEN 24 
#define TOP_SIZE 1000

using namespace std;

// Timer by counting cycles
inline unsigned __int64 GetCycleCount()
{
	__asm
	{
		_emit 0x0F;
		_emit 0x31;
	}
}

int main()
{
	//transData(); //for transfering the data from dat to h

	Btree t(13); // t is the min degree of tree
	int i, j;
	double timeCount=0.0;
	int sha3Num;
	//char * sha3Code;
	string str;
	ifstream sourceFile(SOURCE_FILE);
	//int inLenByte;
	int count;
	unsigned long t1, t2, time, shTime, longTime;

	cout << endl << "****** Bit width of sha3 dataset is: " << OUTLEN <<" ******" << endl << endl;

//// insert data to b-btree
	count = 0;
	timeCount = 0;
	cout << "Test 1. Insert starts ..." << endl;
	while (getline(sourceFile, str))
		{
			count++;
			char strIn[1024];
			strcpy(strIn,str.c_str());
			sha3Num= GenSha3(strIn, OUTLEN);
			//cout << count<<":"<<sha3Num<< endl; 		

			t1 = (unsigned long)GetCycleCount();

			t.insert(sha3Num);
	
			t2 = (unsigned long)GetCycleCount();
			timeCount += (double)(t2 - t1);
		}

	cout << "        Total items inserted :" << count << endl;
	cout << "        Total runtime of whole insert is: " << timeCount*1000.0 / CPU_FREQUENCY << " milliseconds !" << endl <<endl << endl;
	sourceFile.clear();

////traverse all data in b-tree
	//cout << "\n\n Traversal of the constucted tree is \n\n ";
	timeCount = 0;
	cout << "Test 2. Traverse starts ..." ;

	t1 = (unsigned long)GetCycleCount();

	t.traverse();

	t2 = (unsigned long)GetCycleCount();
	timeCount += (double)(t2 - t1);

	cout << endl<<"        ... Traverse ends !" << endl;
	cout << "        Total runtime of whole traverse is: " << timeCount*1000.0 / CPU_FREQUENCY << " milliseconds !" << endl << endl << endl;

////search all data in b-tree
	count = 0;
	timeCount = 0;
	shTime = 0;
	longTime = 0;
	unsigned long shortestTime[TOP_SIZE];
	unsigned long longestTime[TOP_SIZE] = { 0 };
	for (i = 0; i < TOP_SIZE; i++) shortestTime[i] = 999999;
	sourceFile.seekg(0, ios::beg);
	cout << "Test 3. Search starts ..." << endl;
	while (getline(sourceFile, str))
		{
			count++;
			char strIn[1024];
			strcpy(strIn, str.c_str());
			sha3Num = GenSha3(strIn, OUTLEN);
			//cout << count<<":"<<sha3Num<< endl; 

			t1 = (unsigned long)GetCycleCount();

			t.search(sha3Num);

			t2 = (unsigned long)GetCycleCount();
			time = t2 - t1;
			timeCount += (double)time;

			//count top longest runtime
			if (time > longestTime[TOP_SIZE - 1])
			{
				for (i = TOP_SIZE - 1; i > 0; i--)	{
					if (time < longestTime[i]) break;
				}
				for (j = TOP_SIZE - 1; j > i ; j--) {
					longestTime[j] = longestTime[j - 1];
					longestTime[i] = time;
				}
			}

			//count top shortest runtime
			if (time < shortestTime[TOP_SIZE - 1])
			{
				for (i = TOP_SIZE - 1; i > 0; i--) {
					if (time > shortestTime[i]) break;
				}
				for (j = TOP_SIZE - 1; j > i; j--) {
					shortestTime[j] = shortestTime[j - 1];
					shortestTime[i] = time;
				}
			} //end of if

		}//end of while
	for (i = 0; i < TOP_SIZE; i++)	shTime += shortestTime[i];
	shTime /= TOP_SIZE;
	for (i = 0; i < TOP_SIZE; i++)	longTime += longestTime[i];
	longTime /= TOP_SIZE;

	cout << "        Total items searched :" << count << endl;
	cout << "        Total runtime of whole searching is: " << timeCount*1000.0 / CPU_FREQUENCY << " milliseconds !" << endl;
	cout << "        Average of top " <<TOP_SIZE<< " shortest runtime for each search is: " << shTime*1000.0 / CPU_FREQUENCY << " milliseconds !" << endl;
	cout << "        Average of top " << TOP_SIZE << " longest runtime for each search is: " << longTime*1000.0 / CPU_FREQUENCY << " milliseconds !" << endl << endl << endl;
	sourceFile.clear();

////remove data from b-tree
	count = 0;
	timeCount = 0;
	shTime = 0;
	longTime = 0;
	time = 0;
	for (i = 0; i < TOP_SIZE; i++) longestTime[i] = 0;
	for (i = 0; i < TOP_SIZE; i++) shortestTime[i] = 999999;
	sourceFile.seekg(0, ios::beg);
	cout << "Test 4. Remove starts ..." << endl;
	while (getline(sourceFile, str))
	{
		count++;
		char strIn[1024];
		strcpy(strIn, str.c_str());
		sha3Num = GenSha3(strIn, OUTLEN);
		//cout << count<<":"<<sha3Num<< endl; 
		t1 = (unsigned long)GetCycleCount();

		t.remove(sha3Num);

		t2 = (unsigned long)GetCycleCount();
		time = t2 - t1;
		timeCount += (double)time;

		//count top longest runtime
		if (time > longestTime[TOP_SIZE - 1])
		{
			for (i = TOP_SIZE - 1; i > 0; i--) {
				if (time < longestTime[i]) break;
			}
			for (j = TOP_SIZE - 1; j > i; j--) {
				longestTime[j] = longestTime[j - 1];
				longestTime[i] = time;
			}
		}

		//count top shortest runtime
		if (time < shortestTime[TOP_SIZE - 1])
		{
			for (i = TOP_SIZE - 1; i > 0; i--) {
				if (time > shortestTime[i]) break;
			}
			for (j = TOP_SIZE - 1; j > i; j--) {
				shortestTime[j] = shortestTime[j - 1];
				shortestTime[i] = time;
			}
		} //end of if
	} //end of while
	
	for (i = 0; i < TOP_SIZE; i++)	shTime += shortestTime[i];
	shTime /= TOP_SIZE;
	for (i = 0; i < TOP_SIZE; i++)	longTime += longestTime[i];
	longTime /= TOP_SIZE;

	cout << "        Total items removed :" << count << endl;
	cout << "        Total runtime of whole removing is: " << timeCount*1000.0/CPU_FREQUENCY << " milliseconds !" << endl << endl;
	cout << "        Average of top " << TOP_SIZE << " shortest runtime for each remove is: " << shTime*1000.0 / CPU_FREQUENCY << " milliseconds !" << endl;
	cout << "        Average of top " << TOP_SIZE << " longest runtime for each remove is: " << longTime*1000.0 / CPU_FREQUENCY << " milliseconds !" << endl << endl << endl;
	sourceFile.close();

////traverse all data in b-tree
	//cout << "\n\n Traversal of the constucted tree is \n\n ";
	cout << "        Traverse after removing starts ...";
	t1 = (unsigned long)GetCycleCount();
	t.traverse();
	t2 = (unsigned long)GetCycleCount();
	time = t2 - t1;
	cout << endl << "        ... Traverse ends !" << endl;
	cout << "        Total runtime of whole traverse is: " << time*1000.0 / CPU_FREQUENCY << " milliseconds !" << endl;
    return 0;
}

