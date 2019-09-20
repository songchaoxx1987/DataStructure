// Main.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "inc/AVLTree.h"
#include "inc/PriorityQueue.h"
#include "inc/Algorithm.h"
#include <vector>
#include <time.h>

void AVLTreeTest();
void PrioirtyQueueTest();
void Sort_Test();
int _tmain(int argc, _TCHAR* argv[])
{
	//AVLTreeTest();
	//PrioirtyQueueTest();
	Sort_Test();
	getchar();
	return 0;
}



void Sort_Test()
{
	std::vector<int> v;
	randomArray(10, &v);
	PrintVector(&v);

 	std::vector<int> v2 = v;	
 	bubble_sort(&v2);
 	printf("after bubble\n");
 	PrintVector(&v2);
 
 
 	v2 = v;
 	q_sort(&v2, 0, v2.size() - 1);
 	printf("after q_sort\n");
 	PrintVector(&v2);

	v2 = v;
	insert_sort(&v2);
	printf("after insert_sort\n");
	PrintVector(&v2);
	printf("\n");

	v2 = v;
	shell_sort(&v2,v2.size()/2);
	printf("after shell_sort\n");
	PrintVector(&v2);

	v2 = v;
	select_sort(&v2);
	printf("after select_sort\n");
	PrintVector(&v2);

	printf("\n");
	v2 = v;
	heap_sort(&v2);
	printf("after heap_sort\n");
	PrintVector(&v2);
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
