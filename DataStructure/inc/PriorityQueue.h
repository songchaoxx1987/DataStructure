#pragma once
#include "define.h"
#include <vector>

template<class T, class K>
class PriorityQueueNode
{
public:
	PriorityQueueNode(T* data, K key) :_pData(data), _key(key){}
	~PriorityQueueNode(){ _pData = NULL; }
	K _key;
	T *_pData;
};

template<class T, class K>
class PriorityQueue
{
private:
	std::vector<PriorityQueueNode<T, K>*> _heap;		
	int _count;
public:
	PriorityQueue()
	{			
		_heap.resize(10);		
		_count = 0;
	}

	T *Top();
	T *Pop();
	void Push(T *data, K key);
	void Print();
private:
	void ShiftDown(int n);
	void ShiftUp(int n);

	int Compare(PriorityQueueNode<T, K> *x, PriorityQueueNode<T, K> *y)
	{
		if (x->_key == y->_key)
			return 0;
		return x->_key > y->_key ? 1 : -1;
	}

};
template<class T, class K>
T *PriorityQueue<T,K>::Top()
{
	if (_count == 0)
		return 0;
	return _heap[0]->_pData;
}

template<class T, class K>
T *PriorityQueue<T, K>::Pop()
{
	if (_count == 0)
		return 0;
	PriorityQueueNode<T, K> *pNode = _heap[0];
	T* ret = pNode->_pData;

	_heap[0] = _heap[--_count];
	if (_count > 0)
		ShiftDown(0);

	return ret;
}

template<class T, class K>
void PriorityQueue<T, K>::Push(T *data, K key)
{
	PriorityQueueNode<T, K> *pNode = new PriorityQueueNode<T, K>(data, key);
	if (_count >= _heap.size())
		_heap.push_back(pNode);
	else
		_heap[_count] = pNode;
	ShiftUp(_count++);
}

template<class T, class K>
void PriorityQueue<T, K>::ShiftDown(int n)
{
	PriorityQueueNode<T, K>* v = _heap[n];
	for (int n2 = n * 2; n2 < _count; n = n2, n2 *= 2)
	{
		if (n2 + 1 < _count && Compare(_heap[n2 + 1], _heap[n2]) > 0)
			++n2;
		if (Compare(v, _heap[n2]) >= 0)
			break;
		_heap[n] = _heap[n2];
	}
	_heap[n] = v;
}

template<class T, class K>
void PriorityQueue<T, K>::ShiftUp(int n)
{
	PriorityQueueNode<T, K>* v = _heap[n];
	for (int n2 = n / 2; n > 0 && Compare(v, _heap[n2]) > 0; n = n2, n2 /= 2)
	{
		_heap[n] = _heap[n2];
	}
	_heap[n] = v;
}

template<class T, class K>
void PriorityQueue<T, K>::Print()
{
	printf("count: %d\n", _count);
	for (int i = 0; i < _count;++i)
	{
		printf("%d\t", _heap[i]->_key);
	}
	printf("\n");
}