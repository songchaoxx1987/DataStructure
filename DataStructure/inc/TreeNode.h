#pragma once
#include "define.h"
template<class T>
class TreeNode
{
public:
	int m_balanceFactor;
	TreeNode<T> *m_pLChild;
	TreeNode<T> *m_pRChild;
	TreeNode<T> *m_pParent;

	TreeNode() :
		m_pRChild(NULL),
		m_pLChild(NULL),
		m_pParent(NULL),
		m_balanceFactor(0)
		{}
	~TreeNode()
	{
		m_pRChild = m_pLChild = m_pParent = NULL;
	}

	T m_key;
	bool LH(){ return m_balanceFactor == _LH; }
	bool EH(){ return m_balanceFactor == _EH; }
	bool RH(){ return m_balanceFactor == _RH; }
};