// Author��xiongw	
// Date��2018-03-16
// filename:MinHeap.h

#ifndef _PQUEUE_H_
#define _PQUEUE_H_

#include <iostream>
#include <stdlib.h>

const int knDefaultPQSize = 50;

template<class E>
class PQueue
{
protected:
	E * m_pElemets; //����洢��ʽ
	int m_nCount;	//Ԫ�ظ���
	int m_nMaxSize;	//���

protected:
	// ���� 
	// tmp ����β Ԫ��
	// ��Ϊ ÿ�ε���ǰ �����һ��Ԫ�� ������Ϊ���ȶ��з�ʽ ����ֻ��Ϊ���һ��Ԫ���ҵ�����λ�ü���
	void adjust()
	{
		E tmp = m_pElemets[m_nCount - 1];
		int j = 0;
		for (j = m_nCount - 2; j >= 0; --j)
		{
			if (m_pElemets[j] < tmp) break;
			else m_pElemets[j + 1] = m_pElemets[j];
		}
		m_pElemets[j + 1] = tmp;
	}

public:
	PQueue(int size = knDefaultPQSize)
		: m_pElemets(nullptr)
		, m_nCount(0)
		, m_nMaxSize(-1)
	{
		m_nMaxSize = size;
		m_pElemets = new T[m_nMaxSize];
	}

	virtual ~PQueue()
	{
		if (m_pElemets != nullptr)
		{
			delete m_pElemets;
			m_pElemets = nullptr;
		}
	}

	// ��ӵ������ ����
	bool Insert(const E& x)
	{
		if (m_nCount == m_nMaxSize) return false;
		m_pElemets[m_nCount++] = x;
		adjust();
		return true;
	}

	// 
	bool RemoveMin(E& x)
	{
		if (m_nCount == 0) return false;
		x = m_pElemets[0];
		for (int i = 1; i < m_nCount; ++i)
		{
			m_pElemets[i - 1] = m_pElemets[i];
		}
		--m_nCount;
		return true;
	}
	
	bool GetFront(E& x)const
	{
		if (m_nCount == 0) return false;
		x = m_pElemets[0];
		return true;
	}

	void MakeEmpty() { m_nCount = 0; }

	bool IsEmpty() const
	{
		return (0 == m_nCount) ? true : false;
	}

	bool IsFull() const
	{
		return (m_nCount == m_nMaxSize) ? true : false;
	}

	int GetSize() const { return m_nCount; }
};

#endif // !_PQUEUE_H_

