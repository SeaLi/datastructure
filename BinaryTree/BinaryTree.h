// Author��xiongy
// Date��2018/02/08
// filename:BinaryTree.h
#ifndef _BINARYTREE_
#define _BINARYTREE_
#include "ExportBinaryTree.h"
#include <ostream>
#include <iostream>
#include <string>
#include "BTreeNode.h"

using namespace std;

template<class T> 
class BINARYTREE_LIBRARY_EXPORT BinaryTree
{
public:
	BinaryTree() : m_pRoot(nullptr) {}
	~BinaryTree() {}

	void insert(T);
	void remove(T);
	BTreeNode<T>* search(T);
	void destory();

	void preOrder();
	void inOrder();
	void postOrder();
	void print();

	BTreeNode<T>* minimumNode();//������С�Ľڵ�
	BTreeNode<T>* maximumNode();//�������Ľڵ�

	T minimumKey();//������С�ļ�ֵ
	T maximumKey();//������С�ļ�ֵ

	BTreeNode<T>* predecessor(BTreeNode<T>*);
	BTreeNode<T>* sucessor(BTreeNode<T>*);
private:
	BTreeNode<T>* m_pRoot;     //���ĸ�ָ��  
private:
	void insert(BTreeNode<T>* &, BTreeNode<T>* );
	BTreeNode<T>* search(BTreeNode<T>* &, T);

	void preOrder(BTreeNode<T>* &);
	void inOrder(BTreeNode<T>* &);
	void postOrder(BTreeNode<T>* &);

	BTreeNode<T>* minimumNode(BTreeNode<T> *&);
	BTreeNode<T>* maximumNode(BTreeNode<T> *&);

	void print(BTreeNode<T>* &);
	BTreeNode<T>* remove(BTreeNode<T>* &, BTreeNode<T>*);
	void destory(BTreeNode<T>* &);
};

/*
*�������
*�ǵݹ�ʵ��
*�ڲ�ʹ�ú���
*/
template<typename T>
void BinaryTree<T>::insert(BTreeNode<T>* &pTree, BTreeNode<T>* pNode)
{
	BTreeNode<T>* pParent = nullptr;
	BTreeNode<T>* pTemp = pTree;
	//Ѱ�Ҳ����
	while (pTemp != nullptr)
	{
		pParent = pTemp;
		if (pNode->getData() > pTemp->getData())
			pTemp = pTemp->getRChild();
		else
			pTemp = pTemp->getLChild();
	}
	pNode->getParent() = pParent;
	if (pParent == nullptr) //������������ǿ�������ֱ�Ӱ�z�ڵ������ڵ�
		pTree = pNode;
	else if (pNode->getData() > pParent->getData()) //���z��ֵ������˫�ף���zΪ��˫�׵��Һ�
		pParent->getRChild() = pNode;
	else
		pParent->getLChild() = pNode;
}

/*
*���Ҳ���
*�ǵݹ�ʵ��
*�ڲ�ʹ�ú���
*/
template <typename T>
BTreeNode<T>* BinaryTree<T>::search(BTreeNode<T>* &pTree, T key)
{
	BTreeNode<T>* pTemp = pTree;
	while (pTemp != nullptr)
	{
		if (pTemp->getData() == key)
			return pTemp;
		else if (pTemp->getData() > key)
			pTemp = pTemp->getLChild();
		else
			pTemp = pTemp->getRChild();
	}
	return nullptr;
}

template<typename T>
void BinaryTree<T>::preOrder(BTreeNode<T>*&pTree)
{
	if (pTree)
	{
		cout << pTree->getData() << " ";
		preOrder(pTree->getLChild());
		preOrder(pTree->getRChild());
	}
}

template<typename T>
void BinaryTree<T>::inOrder(BTreeNode<T>*&pTree)
{
	if (pTree)
	{
		inOrder(pTree->getLChild());
		cout << pTree->getData() << " ";
		inOrder(pTree->getRChild());
	}
}

template<typename T>
void BinaryTree<T>::postOrder(BTreeNode<T>*&pTree)
{
	if (pTree)
	{
		postOrder(pTree->getLChild());
		postOrder(pTree->getRChild());
		cout << pTree->getData() << " ";
	}
}

/*
*
*������С�Ľ��
*�ڲ����ú���
*
*/
template <typename T>
BTreeNode<T>* BinaryTree<T>::minimumNode(BTreeNode<T>*&pTree)
{
	BTreeNode<T>* pTemp = pTree;
	while (pTemp->getLChild())
	{
		pTemp = pTemp->getLChild();
	}
	return pTemp;
}
/*
*
*�������Ľ��
*�ڲ����ú���
*
*/
template <typename T>
BTreeNode<T>* BinaryTree<T>::maximumNode(BTreeNode<T>*&pTree)
{
	BTreeNode<T>* pTemp = pTree;
	while (pTemp->getRChild())
	{
		pTemp = pTemp->getRChild();
	}
	return pTemp;
}

/*
*
*ɾ�����
*BSTree���ڲ����ú���
*
*/
template <class T>
BTreeNode<T>* BinaryTree<T>::remove(BTreeNode<T>* &pTree, BTreeNode<T> *pNode)
{
	BTreeNode<T> *pX = nullptr;
	BTreeNode<T> *pY = nullptr;
	if ((pNode->getLChild() == nullptr) || (pNode->getRChild() == nullptr))
		pY = pNode;
	else
		pY = sucessor(pNode);
	if (pY->getLChild() != nullptr)
		pX = pY->getLChild();
	else
		pX = pY->getRChild();
	if (pX != nullptr)
		pX->getParent() = pY->getParent();
	if (pY->getParent() == nullptr)
		pTree = pX;
	else if (pY == pY->getParent()->getLChild())
		pY->getParent()->getLChild() = pX;
	else
		pY->getParent()->getRChild() = pX;
	if (pY != pNode)
		pNode->setData(pY->getData());
	return pY;
}

template <typename T>
BTreeNode<T>* BinaryTree<T>::predecessor(BTreeNode<T>* pNode)
{
	if(pNode->getData() == minimumNode(m_pRoot)->getData())//���x����С�Ľ�㣬����û��ǰ��
		return nullptr;
	BTreeNode <T> *pY = nullptr;
	pY = search(m_pRoot, pNode->getData());
	if (pY == nullptr) return nullptr;
	//���y�����ӣ���x��ǰ��Ϊ����x����Ϊ��������������㡱
	if (pY->getLChild() != nullptr)
		return maximumNode(pY->getLChild());
	//���yû�����ӣ���x�����ֿ��ܣ�
	//1.y��һ���Һ��ӣ���ʱx��ǰ��Ϊ��˫�׽ڵ�
	BTreeNode<T>* pParent = pY->getParent();
	if (pParent->getRChild() == pY)
		return pParent;
	//2.y��һ�����ӣ�����ǰ��Ϊ��˫�׽���С���һ��ӵ���Һ��ӽ�㡱�Ľ��
	while (pParent != nullptr && pParent->getRChild() == nullptr)
	{
		pParent = pParent->getParent();
	}
	return pParent;
}

template <typename T>
BTreeNode<T>* BinaryTree<T>::sucessor(BTreeNode<T>* pNode)
{
	//���x�Ǽ�ֵ���ģ���xû�к�̽��
	if (pNode->getData() == maximumNode(m_pRoot)->getData())
		return nullptr;
	//��ȡx�ڶ������еĽ��y
	BTreeNode<T>* pY = nullptr;
	pY = search(m_pRoot, pNode->getData());
	if (pY == nullptr) return nullptr;
	//���y���Һ��ӣ���y�ĺ��Ϊ���Һ��ӵ���С���
	if (pY->getRChild() != nullptr)
		return minimumNode(pY->getRChild());
	//���yû���Һ��ӣ���ɷ�Ϊ���������
	//1.y �����ӡ���ʱy�ĺ��Ϊy�ĸ����
	BTreeNode<T>* pParent = pY->getParent();
	if (pY->getParent()->getLChild() == pY)
		return pParent;

	//2.y���Һ��ӡ���ʱy�ĺ�̽��Ϊ����һ��ӵ�����Ҳ���y��ֱ��˫�ס��Ľ��
	while (pParent != nullptr)
	{
		if (pParent->getLChild() != nullptr && pParent != pY->getParent())
			return pParent;
		pParent = pParent->getParent();
	}
	return nullptr;
}

/*
*
*��ӡ����
*��ӡ��ƽ�������
*BStree�ڲ�����
*/
template<typename T>
void BinaryTree<T>::print(BTreeNode<T>* &pTree)
{
	if (pTree) //���tree��Ϊ��
	{
		if (pTree->getLChild()) //���������
		{
			cout << "Node" << pTree->getData() << "L Child:" << pTree->getLChild()->getData() << endl;
		}
		else
			cout << "Node" << pTree->getData() << "do not has L Child" << endl;
		if (pTree->getRChild())
		{
			cout << "Node" << pTree->getData() << "R Child" << pTree->getRChild()->getData() << endl;
		}
		else
			cout << "Node" << pTree->getData() << "do not has R Child" << endl;
		print(pTree->getLChild());
		print(pTree->getRChild());
	}
}

/*
*
*���ٲ��Ҷ�����
*�ڲ����ú���
*
*/
template<typename T>
void BinaryTree<T>::destory(BTreeNode<T>*& pTree)
{
	if (pTree->getLChild() != nullptr)
		destory(pTree->getLChild());
	if (pTree->getRChild() != nullptr)
		destory(pTree->getRChild());
	if (pTree->getLChild() == nullptr && pTree->getRChild() == nullptr)
	{
		delete(pTree);
		pTree = nullptr;
	}
}

template <typename T>
void BinaryTree<T>::insert(T key)
{
	BTreeNode<T> *pNode = new BTreeNode<T>(key);
	if(pNode != nullptr)
		insert(m_pRoot, pNode);
}

template <typename T>
BTreeNode<T> * BinaryTree<T>::search(T key)
{
	return search(m_pRoot, key);
}

template<typename T>
void BinaryTree<T>::preOrder()
{
	preOrder(m_pRoot);
}

template<typename T>
void BinaryTree<T>::inOrder()
{
	inOrder(m_pRoot);
}

template<typename T>
void BinaryTree<T>::postOrder()
{
	postOrder(m_pRoot);
}

template<typename T>
BTreeNode<T>* BinaryTree<T>::minimumNode()
{
	return minimumNode(m_pRoot);
}

template<typename T>
BTreeNode<T>* BinaryTree<T>::maximumNode()
{
	return maximumNode(m_pRoot);
}

template<typename T>
T BinaryTree<T>::minimumKey()
{
	BTreeNode<T> *pNode = minimumNode(m_pRoot);
	if (pNode != nullptr)
		return pNode->getData();
}

template<typename T>
T BinaryTree<T>::maximumKey()
{
	BTreeNode<T> *pNode = maximumNode(m_pRoot);
	if (pNode != nullptr)
		return pNode->getData();
}

template<typename T>
void BinaryTree<T>::print()
{
	print(m_pRoot);
}

template<typename T>
void BinaryTree<T>::remove(T key)
{
	BTreeNode<T> *pZ, *pNode;
	if ((pZ = search(m_pRoot, key)) != nullptr)
		if ((pNode = remove(m_pRoot, pZ)) != nullptr)
			delete pNode;
}


template<typename T>
void BinaryTree<T>::destory()
{
	destory(m_pRoot);
}
#endif // !_BINARYTREE_


