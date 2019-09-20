#include "stdafx.h"
#include "inc/Algorithm.h"
#include "inc/define.h"

// √∞≈›
void bubble_sort(sortArray v)
{
	for (int i = 0; i < v->size(); ++i)
	{
		for (int j = i; j < v->size(); ++j)
		{
			if ((*v)[i] >(*v)[j])
			{
				int t = (*v)[i];
				(*v)[i] = (*v)[j];
				(*v)[j] = t;
			}
		}
	}
}

//øÏ≈≈
void q_sort(sortArray v, int start, int end)
{
	if (start >= end)
		return;
	int i = start;
	int j = end;
	int t = (*v)[start];
	while (i < j)
	{
		while (i < j && (*v)[j] > t)		
			--j;
		if (i < j)
		{
			(*v)[i] = (*v)[j];
			++i;
		}
		while (i < j && (*v)[i] < t)		
			++i;
		if (i < j)
		{
			(*v)[j] = (*v)[i];
			--j;
		}
	}
	(*v)[i] = t;
	q_sort(v, start, i - 1);
	q_sort(v, i + 1, end);
}

// ÷±Ω”≤Â»Î≈≈–Ú
void insert_sort(sortArray v)
{	
	int cnt = 0;
	int temp;
	for (int i = 1; i < v->size(); ++i)
	{
		temp = (*v)[i];
		int j = i - 1;		
		while ((j >= 0) && ((*v)[j] > temp))
		{
			(*v)[j + 1] = (*v)[j];
			--j;
			++cnt;
		}		
		if (j != i - 1)
			(*v)[j + 1] = temp;
	}
	printf("insert_sort %d\n", cnt);
}

// œ£∂˚≈≈–Ú
void shell_sort(sortArray v, int dk)
{
	int cnt = 0;
	while (dk > 0)
	{	
		for (int i = dk; i < v->size(); ++i)
		{
			int t = (*v)[i];
			int j = i - dk;
			while (j >= 0 && (*v)[j] > t)
			{
				(*v)[j + dk] = (*v)[j];
				j -= dk;
				++cnt;
			}
			if (j != i - dk)
				(*v)[j + dk] = t;				
		}
		dk /= 2;
	}
	printf("shell_sort %d\n", cnt);
}

// —°‘Ò≈≈–Ú
void select_sort(sortArray v)
{
	for (int i = 0; i < v->size();++i)
	{
		int min = (*v)[i];
		for (int j = i + 1; j < v->size(); ++j)
		{
			if ((*v)[j] < min)
			{
				int t = (*v)[j];
				(*v)[j] = min;
				min = t;
			}
		}
		(*v)[i] = min;
	}
}

void heapAdjust(sortArray v, int s, int m)
{
	int t = (*v)[s];
	for (int i = 2 * s + 1; i <= m; i=2*i+1)
	{
		if (i < m && (*v)[i] < (*v)[i + 1])	// »°◊Ó¥Û∫¢◊”œ¬±Í
			++i;
		if (t > (*v)[i])
			break;
		(*v)[s] = (*v)[i];
		s = i;
	}
	(*v)[s] = t;
}

// ∂—≈≈–Ú
void heap_sort(sortArray v)
{
	for (int i = v->size() / 2; i >= 0;--i)
	{
		heapAdjust(v, i, v->size()-1);		
	}
	
	for (int i = v->size() - 1; i > 0; --i)
	{
		int t = (*v)[i];
		(*v)[i] = (*v)[0];
		(*v)[0] = t;
		heapAdjust(v, 0, i - 1);
	}
}
