#pragma once
#include "TreeNode.h"
#include "define.h"
#include <queue>
#include <stack>

template<class T>
class AVLTree
{
public:
	AVLTree() :m_pRootNode(NULL){}
	~AVLTree(){ Clear(); }
	void Clear()
	{
		deleteNodeRecursive(m_pRootNode);
		m_pRootNode = NULL;
	}

	bool Remove(T key)
	{
		bool ret = false;
		DelNode(m_pRootNode, key, ret);
		return ret;
	}
	TreeNode<T>* Insert(T key);
	TreeNode<T>* Find(T key);
	void Print();		
protected:
	TreeNode<T> *m_pRootNode;
	TreeNode<T>* r_rotate(TreeNode<T> *pNode);
	TreeNode<T>* l_rotate(TreeNode<T> *pNode);
	TreeNode<T>* leftBalance(TreeNode<T>* pParent);
	TreeNode<T>* rightBalance(TreeNode<T>* pParent);
	TreeNode<T>* newNode(T key)
	{
		TreeNode<T>* p = new TreeNode<T>();
		p->m_key = key;
		return p;
	}
	void deleteNodeRecursive(TreeNode<T> *pNode);

	TreeNode<T>* goFarLeft(TreeNode<T>* p);
	TreeNode<T>* goFarRight(TreeNode<T>* p);
	TreeNode<T>* DelNode(TreeNode<T>*p, T key, bool &removed);
	TreeNode<T>* DelLeftCase(TreeNode<T> *p, int bfChild);
	TreeNode<T>* DelRightCase(TreeNode<T> *p, int bfChild);

};

template<class T>
TreeNode<T>* AVLTree<T>::Insert(T key)
{
	if (!m_pRootNode)
	{
		m_pRootNode = newNode(key);
		return m_pRootNode;
	}

	TreeNode<T> *p = m_pRootNode;
	TreeNode<T> *pParent = p;
	while (p)
	{
		pParent = p;
		if (p->m_key > key)
			p = p->m_pLChild;
		else if (p->m_key < key)
			p = p->m_pRChild;
		else
			return p;
	}
	p = newNode(key);
	p->m_pParent = pParent;
	if (key < pParent->m_key)
	{
		pParent->m_pLChild = p;
	}
	else
	{
		pParent->m_pRChild = p;
	}
	bool taller = pParent->EH();
	if (taller)
	{
		while (pParent)
		{
			bool isLeft = key < pParent->m_key;
			if (pParent->EH())
			{
				pParent->m_balanceFactor = isLeft ? _LH : _RH;
			}
			else if (pParent->LH())
			{
				if (isLeft)
					pParent = leftBalance(pParent);
				else
					pParent->m_balanceFactor = _EH;
				break;
			}
			else if (pParent->RH())
			{
				if (!isLeft)
					pParent = rightBalance(pParent);
				else
					pParent->m_balanceFactor = _EH;
				break;
			}
			pParent = pParent->m_pParent;
		}
	}
	else
	{
		pParent->m_balanceFactor = 0;
	}
	return p;
}

template<class T>
TreeNode<T>* AVLTree<T>::Find(T key)
{
	if (!m_pRootNode)
		return NULL;
	TreeNode<T> *p = m_pRootNode;
	while (p)
	{
		if (p->m_key == key)
			break;
		else if (p->m_key > key)
			p = p->m_pLChild;
		else if (p->m_key < key)
			p = p->m_pRChild;
	}
	return p;
}

template<class T>
void AVLTree<T>::Print()
{
	if (m_pRootNode == NULL)
	{
		printf("empty\n");
		return;
	}
	std::queue<TreeNode<T>*> q;
	q.push(m_pRootNode);
	while (!q.empty())
	{
		TreeNode<T>*p = q.front();
		q.pop();

		printf("%d(%d) \t", p->m_key, p->m_balanceFactor);

		if (p->m_pLChild)
		{
			q.push(p->m_pLChild);
			printf("%d(%d) \t", p->m_pLChild->m_key, p->m_pLChild->m_balanceFactor);
		}
		if (p->m_pRChild)
		{
			q.push(p->m_pRChild);
			printf("*%d(%d) \t", p->m_pRChild->m_key, p->m_pRChild->m_balanceFactor);
		}
		printf("\n");

	}
}

template<class T>
TreeNode<T>* AVLTree<T>::r_rotate(TreeNode<T> *pNode)
{
	if (!pNode)
		return NULL;
	TreeNode<T> *pL = pNode->m_pLChild;
	pNode->m_pLChild = pL->m_pRChild;
	pL->m_pRChild = pNode;
	if (pNode->m_pLChild)
		pNode->m_pLChild->m_pParent = pNode;
	pL->m_pParent = pNode->m_pParent;
	pNode->m_pParent = pL;
	if (pL->m_pParent)
	{
		if (pL->m_pParent->m_key > pL->m_key)
			pL->m_pParent->m_pLChild = pL;
		else
			pL->m_pParent->m_pRChild = pL;
	}
	return pL;
}

template<class T>
TreeNode<T>* AVLTree<T>::l_rotate(TreeNode<T> *pNode)
{
	if (!pNode)
		return NULL;
	TreeNode<T> *pR = pNode->m_pRChild;
	pNode->m_pRChild = pR->m_pLChild;
	pR->m_pLChild = pNode;
	if (pNode->m_pRChild)
		pNode->m_pRChild->m_pParent = pNode;
	pR->m_pParent = pNode->m_pParent;
	pNode->m_pParent = pR;
	if (pR->m_pParent)
	{
		if (pR->m_pParent->m_key > pR->m_key)
			pR->m_pParent->m_pLChild = pR;
		else
			pR->m_pParent->m_pRChild = pR;
	}
	return pR;
}

template<class T>
TreeNode<T>* AVLTree<T>::leftBalance(TreeNode<T>* pParent)
{
	TreeNode<T> *newParent = NULL;
	switch (pParent->m_pLChild->m_balanceFactor)
	{
	case _EH:
		pParent->m_balanceFactor = _LH;
		pParent->m_pLChild->m_balanceFactor = _RH;
		newParent = r_rotate(pParent);
		break;
	case _LH:
		pParent->m_balanceFactor = _EH;
		pParent->m_pLChild->m_balanceFactor = _EH;
		newParent = r_rotate(pParent);
		break;
	case _RH:
	{
				TreeNode<T> * rchild = pParent->m_pLChild->m_pRChild;
				switch (rchild->m_balanceFactor)
				{
				case _LH:
					pParent->m_balanceFactor = _RH;
					pParent->m_pLChild->m_balanceFactor = _EH;
					break;
				case _RH:
					pParent->m_balanceFactor = _EH;
					pParent->m_pLChild->m_balanceFactor = _LH;
					break;
				case _EH:
					pParent->m_balanceFactor = _EH;
					pParent->m_pLChild->m_balanceFactor = _EH;
					break;
				}
				rchild->m_balanceFactor = _EH;
				l_rotate(pParent->m_pLChild);
				newParent = r_rotate(pParent);
				break;
	}
	}
	if (!newParent->m_pParent)
		m_pRootNode = newParent;
	return newParent;
}

template<class T>
TreeNode<T>* AVLTree<T>::rightBalance(TreeNode<T>* pParent)
{
	TreeNode<T> *newParent = NULL;
	switch (pParent->m_pRChild->m_balanceFactor)
	{
	case _RH:
		pParent->m_balanceFactor = pParent->m_pRChild->m_balanceFactor = _EH;
		newParent = l_rotate(pParent);
		break;
	case _EH:
		pParent->m_balanceFactor = _RH;
		pParent->m_pRChild->m_balanceFactor = _LH;
		newParent = l_rotate(pParent);
		break;
	case _LH:
	{
				TreeNode<T> * lchild = pParent->m_pRChild->m_pLChild;
				switch (lchild->m_balanceFactor)
				{
				case _LH:
					pParent->m_pRChild->m_balanceFactor = _RH;
					pParent->m_balanceFactor = _EH;
					break;
				case _RH:
					pParent->m_pRChild->m_balanceFactor = _EH;
					pParent->m_balanceFactor = _LH;
					break;
				case _EH:
					pParent->m_pRChild->m_balanceFactor = _EH;
					pParent->m_balanceFactor = _EH;
					break;
				}
				lchild->m_balanceFactor = _EH;
				r_rotate(pParent->m_pRChild);
				newParent = l_rotate(pParent);
				break;
	}
	}	
	if (!newParent->m_pParent)
		m_pRootNode = newParent;
	return newParent;
}

template<class T>
void AVLTree<T>::deleteNodeRecursive(TreeNode<T> *pNode)
{
	if (pNode == NULL)
		return;
	deleteNodeRecursive(pNode->m_pLChild);
	deleteNodeRecursive(pNode->m_pRChild);
	SAFE_DELETE(pNode);
}

template<class T>
TreeNode<T>* AVLTree<T>::goFarLeft(TreeNode<T>* p)
{
	TreeNode<T>* q = p;
	while (p)
	{
		q = p;
		p = p->m_pLChild;
	}
	return q;
}

template<class T>
TreeNode<T>* AVLTree<T>::goFarRight(TreeNode<T>* p)
{
	TreeNode<T>* q = p;
	while (p)
	{
		q = p;
		p = p->m_pRChild;
	}
	return q;
}

template<class T>
TreeNode<T>* AVLTree<T>::DelLeftCase(TreeNode<T> *p, int bfChild)
{
	//当bf为-1或1变为0，或者孩子为空时说明子树高降低     
	if ((!p->m_pLChild) || (_EH != bfChild && _EH == p->m_pLChild->m_balanceFactor))
	{
		switch (p->m_balanceFactor)//左子树树高降低
		{
		case _EH:
			p->m_balanceFactor = _RH;
			break;
		case _LH:
			p->m_balanceFactor = _EH;
			break;
		case _RH:        //原本右子树比较高   
			p = rightBalance(p);
			break;
		}
	}
	return p;
}

template<class T>
TreeNode<T>* AVLTree<T>::DelRightCase(TreeNode<T> *p, int bfChild)
{
	//当bf为LH或RH变为EH，或者孩子为空时说明子树高降低
	if ((!p->m_pRChild) || (_EH != bfChild && _EH == p->m_pRChild->m_balanceFactor))
	{
		switch (p->m_balanceFactor)
		{
		case _EH:
			p->m_balanceFactor = _LH;
			break;
		case _RH:
			p->m_balanceFactor = _EH;
			break;
		case _LH:    //原本左子树比较高    
			p = leftBalance(p);
			break;
		}
	}
	return p;
}

template<class T>
TreeNode<T>* AVLTree<T>::DelNode(TreeNode<T>*pRoot, T key, bool &removed)
{
	if (!pRoot)
		return NULL;
	int bf = 0;
	if (key < pRoot->m_key)
	{
		bf = pRoot->m_pLChild->m_balanceFactor;
		pRoot->m_pLChild = DelNode(pRoot->m_pLChild, key, removed);
		if (pRoot->m_pLChild)
			pRoot->m_pLChild->m_pParent = pRoot;
		pRoot = DelLeftCase(pRoot, bf);
	}
	else if (key > pRoot->m_key)
	{
		bf = pRoot->m_pRChild->m_balanceFactor;
		pRoot->m_pRChild = DelNode(pRoot->m_pRChild, key, removed);
		if (pRoot->m_pRChild)
			pRoot->m_pRChild->m_pParent = pRoot;
		pRoot = DelRightCase(pRoot, bf);
	}
	else
	{
		if (pRoot->m_pLChild)
		{
			TreeNode<T>* r = goFarRight(pRoot->m_pLChild);
			pRoot->m_key = r->m_key;
			pRoot->m_pLChild = DelNode(pRoot->m_pLChild, r->m_key, removed);
			if (pRoot->m_pLChild)
				pRoot->m_pLChild->m_pParent = pRoot;
			pRoot = DelLeftCase(pRoot, bf);
		}
		else if (pRoot->m_pRChild)
		{
			TreeNode<T> *l = goFarLeft(pRoot->m_pRChild);
			pRoot->m_key = l->m_key;
			pRoot->m_pRChild = DelNode(pRoot->m_pRChild, l->m_key, removed);
			if (pRoot->m_pRChild)
				pRoot->m_pRChild->m_pParent = pRoot;
			pRoot = DelRightCase(pRoot, bf);
		}
		else
		{						
			removed = true;
			if (pRoot == m_pRootNode)
				m_pRootNode = NULL;
			SAFE_DELETE(pRoot);
			return NULL;
		}
	}
	return pRoot;
}