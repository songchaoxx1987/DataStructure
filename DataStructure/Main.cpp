// Main.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "inc/AVLTree.h"
#include <vector>
#include <time.h>

void AVLTreeTest();
int _tmain(int argc, _TCHAR* argv[])
{
	AVLTreeTest();

	getchar();
	return 0;
}


void AVLTreeTest()
{
	AVLTree<int> *tree = new AVLTree<int>();


	//std::vector<int> v2 = { 1, 9, 7, 6, 8, 5, 3, 0, 2, 4 };
	srand((unsigned)time(NULL));
	std::vector<int> v2;
	std::vector<int> v;
	for (int i = 0; i < 10; ++i)
	{
		v.push_back(i);
	}

	while (!v.empty())
	{
		int i = rand() % v.size();
		v2.push_back(v[i]);
		v.erase(std::begin(v) + i);
	}

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
