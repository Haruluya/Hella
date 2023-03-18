#pragma once
#include "BiTree.h"

#define HELLA_SQBITREE_MAX_SIZE 50

namespace Hella {
	template <typename ElemType>
	class SqBiTree : public BiTree<ElemType>
	{
	public:
		// Í¨¹ý BiTree ¼Ì³Ð
		virtual Status Init() override;

		virtual Status Destroy() override;

		virtual Status Clear() override;

		virtual Status IsEmpty() override;

		virtual Status Depth(int& depth) override;

		virtual Status Length(int& len) override;

		virtual Status Value(Position p, ElemType& e) override;

		virtual Status Assign(Position p, ElemType value) override;

		virtual Status Root(ElemType& e) override;

		virtual Status Parent(ElemType e, ElemType& parent) override;

		virtual Status LeftChild(ElemType e, ElemType& lchild) override;

		virtual Status RightChild(ElemType e, ElemType& rchild) override;

		virtual Status LeftSibling(ElemType e, ElemType& lsibling) override;

		virtual Status RightSibling(ElemType e, ElemType& rsibling) override;

		virtual Status PreOrderTraverse(void(*visit)(ElemType&)) override;

		virtual Status InOrderTraverse(void(*visit)(ElemType&)) override;

		virtual Status PostOrderTraverse(void(*visit)(ElemType&)) override;

		virtual Status LevelOrderTraverse(void(*visit)(ElemType&)) override;

		virtual Status Create(ElemType* e, ElemType format, ElemType type = 0) override;

		virtual Status GetElemByIndex(int,ElemType&) override;
	private:
		ElemType* m_Base;
		int m_Size;

		Status CreateByLev(ElemType* e, ElemType format) override;
		Status CreateByPre(ElemType* e, ElemType format, int index) override;
		Status PreOrderTraverseRec(void(*visit)(ElemType&), const int i);
		Status InOrderTraverseRec(void(*visit)(ElemType&), const int i);
		Status PostOrderTraverseRec(void(*visit)(ElemType&), const int i);

	};
}

/*
	IMPLEMENT.
*/
template <typename ElemType>
Hella::Status Hella::SqBiTree<ElemType>::Init()
{
	m_Base = HELLA_MALLOC(HELLA_SQBITREE_MAX_SIZE, ElemType);
	HELLA_ASSERT_MEMORY_MALLOC(m_Base);
	for (int i = 0; i < HELLA_SQBITREE_MAX_SIZE; i++) {
		m_Base[i] = -1;
	}
	m_Size = HELLA_SQBITREE_MAX_SIZE;
	return Status::HELLA_OK;
}
template <typename ElemType>
Hella::Status Hella::SqBiTree<ElemType>::Destroy()
{
	HELLA_FREE(m_Base);
	return Status::HELLA_OK;
}
template <typename ElemType>
Hella::Status Hella::SqBiTree<ElemType>::Clear()
{
	for (int i = 0; i < m_Size; i++) {
		m_Base[i] = -1;
	}
	return Status::HELLA_OK;
}
template <typename ElemType>
Hella::Status Hella::SqBiTree<ElemType>::IsEmpty()
{
	if (m_Base[0] == -1) {
		return Status::HELLA_TRUE;
	}
	return Status::HELLA_FALSE;
}
template <typename ElemType>
Hella::Status Hella::SqBiTree<ElemType>::Depth(int& depth)
{
	int d = 0, len;
	Length(len);
	while ((static_cast<int>(std::pow(d, 2)) - 1) < len) {
		d++;
	}
	depth = d;
	return Status::HELLA_OK;
}
template <typename ElemType>
Hella::Status Hella::SqBiTree<ElemType>::Length(int& len)
{
	int l = m_Size;
	while (l > 0) {
		l--;
		if (m_Base[l] != -1)
			break;
	}
	if (m_Base[0] == -1) {
		len = 0;
	}
	else {
		len = l + 1;
	}
	return Status::HELLA_OK;
}
template <typename ElemType>
Hella::Status Hella::SqBiTree<ElemType>::Value(Position p, ElemType& e)
{
	int i = static_cast<int>(std::pow(2, p.level - 1)) + p.order - 2;
	if (i > m_Size)
		return Status::HELLA_ERROR;
	e = m_Base[i];
	return Status::HELLA_OK;
}
template <typename ElemType>
Hella::Status Hella::SqBiTree<ElemType>::Assign(Position p, ElemType value)
{
	int i = static_cast<int>(std::pow(2, p.level - 1)) + p.order - 2;
	//out of size.
	if (i > m_Size) {
		return Status::HELLA_INFEASIBLE;
	}
	if (value == -1 && (2 * i + 1) < m_Size) {
		//two child.
		if ((2 * i + 2 < m_Size)) {
			if ((m_Base[2 * i + 1] != -1 || m_Base[2 * i + 2] != -1))
				return Status::HELLA_INFEASIBLE;
		}
		//one.
		else {
			if (m_Base[2 * i + 1] != -1)
				return Status::HELLA_INFEASIBLE;
		}
	}

	if (value != -1 && (m_Base[(i + 1) / 2 - 1] == -1)) {
		return Status::HELLA_INFEASIBLE;
	}

	m_Base[i] = value;
	return Status::HELLA_OK;
}
template <typename ElemType>
Hella::Status Hella::SqBiTree<ElemType>::Root(ElemType& e)
{
	if (m_Base[0] == -1)
		return Status::HELLA_ERROR;
	e = m_Base[0];
	return Status::HELLA_OK;
}
template <typename ElemType>
Hella::Status Hella::SqBiTree<ElemType>::Parent(ElemType e, ElemType& parent)
{
	if (m_Base[0] == -1)
		return Status::HELLA_INFEASIBLE;
	for (int i = 0; i < m_Size; i++) {
		if (m_Base[i] == e) {
			parent = m_Base[(i + 1) / 2 - 1];
			return Status::HELLA_OK;
		}
	}
	return Status::HELLA_NOT_FOUND;
}
template <typename ElemType>
Hella::Status Hella::SqBiTree<ElemType>::LeftChild(ElemType e, ElemType& lchild)
{
	if (m_Base[0] == -1)
		return Status::HELLA_INFEASIBLE;
	for (int i = 0; i < m_Size; i++) {
		if (m_Base[i] == e) {
			if ((i * 2) + 1 < m_Size) {
				lchild = m_Base[i * 2 + 1];
				return Status::HELLA_OK;
			}
			else {
				return Status::HELLA_INFEASIBLE;
			}
		}
	}
	return Status::HELLA_NOT_FOUND;
}
template <typename ElemType>
Hella::Status Hella::SqBiTree<ElemType>::RightChild(ElemType e, ElemType& rchild)
{
	if (m_Base[0] == -1)
		return Status::HELLA_INFEASIBLE;
	for (int i = 0; i < m_Size; i++) {
		if (m_Base[i] == e) {
			if ((i * 2) + 2 < m_Size) {
				rchild = m_Base[i * 2 + 2];
				return Status::HELLA_OK;
			}
			else {
				return Status::HELLA_INFEASIBLE;
			}
		}
	}
	return Status::HELLA_NOT_FOUND;
}
template <typename ElemType>
Hella::Status Hella::SqBiTree<ElemType>::LeftSibling(ElemType e, ElemType& lsibling)
{
	if (m_Base[0] == -1)
		return Status::HELLA_INFEASIBLE;
	for (int i = 0; i < m_Size; i++) {
		if (i % 2 == 0 && m_Base[i] == e) {
			lsibling = m_Base[i - 1];
			return Status::HELLA_OK;
		}
	}
	return Status::HELLA_NOT_FOUND;
}
template <typename ElemType>
Hella::Status Hella::SqBiTree<ElemType>::RightSibling(ElemType e, ElemType& rsibling)
{
	if (m_Base[0] == -1)
		return Status::HELLA_INFEASIBLE;
	for (int i = 0; i < m_Size; i++) {
		if (i % 2 != 0 && m_Base[i] == e) {
			if (i + 1 < m_Size) {
				rsibling = m_Base[i + 1];
				return Status::HELLA_OK;
			}
			else {
				return Status::HELLA_INFEASIBLE;
			}
		}
	}
	return Status::HELLA_NOT_FOUND;
}

template <typename ElemType>
Hella::Status Hella::SqBiTree<ElemType>::PreOrderTraverse(void(*visit)(ElemType&))
{
	return PreOrderTraverseRec(visit, 0);
}
template <typename ElemType>
Hella::Status Hella::SqBiTree<ElemType>::InOrderTraverse(void(*visit)(ElemType&))
{
	return InOrderTraverseRec(visit, 0);
}
template <typename ElemType>
Hella::Status Hella::SqBiTree<ElemType>::PostOrderTraverse(void(*visit)(ElemType&))
{
	return PostOrderTraverseRec(visit, 0);
}
template <typename ElemType>
Hella::Status Hella::SqBiTree<ElemType>::LevelOrderTraverse(void(*visit)(ElemType&))
{
	for (int i = 0; i < m_Size; i++) {
		if (m_Base[i] != -1)
			visit(m_Base[i]);
	}
	return Status::HELLA_OK;
}
template<typename ElemType>
Hella::Status Hella::SqBiTree<ElemType>::Create(ElemType* e, ElemType format, ElemType type)
{
	return CreateByLev(e, format);
}
template <typename ElemType>
Hella::Status Hella::SqBiTree<ElemType>::PreOrderTraverseRec(void(*visit)(ElemType&), const int i)
{
	if (i < m_Size && m_Base[i] != -1) {
		visit(m_Base[i]);
		PreOrderTraverseRec(visit, i * 2 + 1);
		PreOrderTraverseRec(visit, i * 2 + 2);
	}
	return Status::HELLA_OK;
}


template <typename ElemType>
Hella::Status Hella::SqBiTree<ElemType>::InOrderTraverseRec(void(*visit)(ElemType&), const int i)
{
	if (i < m_Size && m_Base[i] != -1) {
		PreOrderTraverseRec(visit, i * 2 + 1);
		visit(m_Base[i]);
		PreOrderTraverseRec(visit, i * 2 + 2);
	}
	return Status::HELLA_OK;
}
template <typename ElemType>
Hella::Status Hella::SqBiTree<ElemType>::PostOrderTraverseRec(void(*visit)(ElemType&), const int i)
{
	if (i < m_Size && m_Base[i] != -1) {
		PreOrderTraverseRec(visit, i * 2 + 1);
		PreOrderTraverseRec(visit, i * 2 + 2);
		visit(m_Base[i]);
	}
	return Status::HELLA_OK;
}

template <typename ElemType>
Hella::Status Hella::SqBiTree<ElemType>::CreateByLev(ElemType* e, ElemType format)
{
	if (!e)
		return Status::HELLA_ERROR;
	int i = 0;
	while (e[i] != -1 && i < m_Size) {
		if (e[i] == format) {
			m_Base[i] = format;
		}
		else {
			m_Base[i] = e[i];
		}
		i++;
	}
	return Status::HELLA_OK;
}
template <typename ElemType>
Hella::Status Hella::SqBiTree<ElemType>::CreateByPre(ElemType* e, ElemType format, int index)
{
	if (!e)
		return Status::HELLA_ERROR;
	if (index < m_Size) {
		if (m_Base[index] == format) {
			m_Base[index] = -1;
		}
		else {
			m_Base[index] = e[index];
			CreateByPre(e, format, 2 * index + 1);
			CreateByPre(e, format, 2 * index + 2);
		}
	}
	return Status::HELLA_OK;

}
template <typename ElemType>
Hella::Status Hella::SqBiTree<ElemType>::GetElemByIndex(int i, ElemType& e)
{
	int len;
	Length(len);
	if (i >= len) {
		return Status::HELLA_INFEASIBLE;
	}
	e = m_Base[i];
	return Status::HELLA_OK;
}


