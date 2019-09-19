// Main.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "inc/AVLTree.h"
#include "inc/PriorityQueue.h"
#include <vector>
#include <time.h>

void AVLTreeTest();
void PrioirtyQueueTest();
int _tmain(int argc, _TCHAR* argv[])
{
	//AVLTreeTest();
	PrioirtyQueueTest();
	getchar();
	return 0;
}

void randomArray(int size, std::vector<int> *pV)
{
	pV->clear();
	srand((unsigned)time(NULL));	
	std::vector<int> v;
	for (int i = 0; i < size; ++i)
	{
		v.push_back(i);
	}
	while (!v.empty())
	{
		int i = rand() % v.size();
		pV->push_back(v[i]);
		v.erase(std::begin(v) + i);
	}	
}

class PNode
{
public:
	PNode(int data) :_data(data){}
	PNode():_data(-9999){}
	int _data;
};

void PrioirtyQueueTest()
{
	PriorityQueue<PNode, int> pQueue;
	std::vector<int> v2;
	randomArray(10, &v2);
	std::vector<PNode*> v;
	for (int i = 0; i < v2.size(); ++i)
	{
		v.push_back(new PNode(v2[i]));
	}

// 	for (int i = 0; i < v.size(); ++i)
// 	{
// 		printf("push %d\n", v[i]->_data);
// 		pQueue.Push(v[i],v[i]->_data);
// 		pQueue.Print();
// 		printf("\n**********************\n");
// 	}
// 
// 	for (int i = 0; i < v.size()+5; ++i)
// 	{		
// 		PNode *p = pQueue.Pop();
// 		if (p == NULL)
// 			printf("pop null");
// 		else
// 			printf("pop %d\n", p->_data);
// 		pQueue.Print();
// 		printf("\n**********************\n");
// 	}

	PriorityQueue<int, int> pQueue2;
	for (int i = 0; i < v2.size(); ++i)
	{
		printf("push %d\n", v2[i]);
		pQueue2.Push(&v2[i], v2[i]);
		pQueue2.Print();
		printf("\n**********************\n");
	}

	for (int i = 0; i < v2.size()+5; ++i)
	{
		int *p = pQueue2.Pop();
		if (p == NULL)
			printf("pop null");
		else
			printf("pop %d\n", *p);
		pQueue2.Print();
		printf("\n**********************\n");
	}
}

void AVLTreeTest()
{
	AVLTree<int> *tree = new AVLTree<int>();


	//std::vector<int> v2 = { 1, 9, 7, 6, 8, 5, 3, 0, 2, 4 };
	srand((unsigned)time(NULL));
	std::vector<int> v2;
	randomArray(10, &v2);
	// insert
	for (int i = 0; i < 10; ++i)
	{
		printf("insert %d\n", v2[i]);
		tree->Insert(v2[i]);
		tree->Print();
		printf("\n**********************\n");
	}
	// search
	for (int i = 0; i < 10; ++i)
	{
		if (tree->Find(i))
			printf("%d find!\n", i);
		else
			printf("%d not find!\n", i);
	}
	printf("\n**********************\n");
	//to do remove
	for (int i = 0; i < 10; ++i)
	{
		printf("%d remove!\n", v2[i]);
		if (tree->Remove(v2[i]))
			printf("ok!\n");
		else
			printf("failed!\n");
		tree->Print();
		printf("\n**********************\n");
	}

	SAFE_DELETE(tree);
}
