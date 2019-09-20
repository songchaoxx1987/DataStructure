#pragma once
#include <vector>
#include "time.h"
#define SAFE_DELETE(p) if (p) {delete p; p = NULL;}
#define _EH 0
#define _LH 1
#define _RH -1

inline void randomArray(int size, std::vector<int> *pV)
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

inline void PrintVector(std::vector<int> *v)
{
	for (int i = 0; i < v->size(); ++i)
	{
		printf("%d ", (*v)[i]);
	}
	printf("\n");
}