#include "hlpch.h"
#include "SqBiTree.h"


Hella::Status Hella::SqBiTree::Init()
{
	m_Base = HELLA_MALLOC(HELLA_SQBITREE_MAX_SIZE, ElemType);
	HELLA_ASSERT_MEMORY_MALLOC(m_Base);
	for (int i = 0; i < HELLA_SQBITREE_MAX_SIZE; i++) {
		m_Base[i] = -1;
	}
	m_Size = HELLA_SQBITREE_MAX_SIZE;
	return Status::HELLA_OK;
}

Hella::Status Hella::SqBiTree::Destroy()
{
	HELLA_FREE(m_Base);
	return Status::HELLA_OK;
}

Hella::Status Hella::SqBiTree::Clear()
{
	for (int i = 0; i < m_Size; i++) {
		m_Base[i] = -1;
	}
	return Status::HELLA_OK;
}

Hella::Status Hella::SqBiTree::IsEmpty()
{
	if (m_Base[0] == -1) {
		return Status::HELLA_TRUE;
	}
	return Status::HELLA_FALSE;
}

Hella::Status Hella::SqBiTree::Depth(int& depth)
{
	int d = 0, len;
	Length(len);
	while ((static_cast<int>(std::pow(d, 2)) - 1) < len) {
		d++;
	}
	depth = d;
	return Status::HELLA_OK;
}

Hella::Status Hella::SqBiTree::Length(int& len)
{
	int l = m_Size;
	while (l > 0) {
		l--;
		if (m_Base[l] != -1)
			break;
	}
	len = l+1;
	return Status::HELLA_OK;
}

Hella::Status Hella::SqBiTree::Value(Position p, ElemType& e)
{
	int i = static_cast<int>(std::pow(2, p.level - 1)) + p.order - 2;
	if (i > m_Size)
		return Status::HELLA_ERROR;
	e = m_Base[i];
	return Status::HELLA_OK;
}

Hella::Status Hella::SqBiTree::Assign(Position p, ElemType value)
{
	int i = static_cast<int>(std::pow(2, p.level - 1)) + p.order - 2;
	//out of size.
	if (i > m_Size) {
		return Status::HELLA_INFEASIBLE;
	}
	if (value == -1 && (2*i+1) < m_Size) {
		//two child.
		if ((2*i+2 < m_Size)) {
			if((m_Base[2 * i + 1] != -1 || m_Base[2 * i + 2] != -1))
				return Status::HELLA_INFEASIBLE;
		}
		//one.
		else {
			if(m_Base[2*i+1] != -1)
				return Status::HELLA_INFEASIBLE;
		}
	}

	if (value != -1 && (m_Base[(i + 1) / 2 - 1] == -1)) {
		return Status::HELLA_INFEASIBLE;
	}

	m_Base[i] = value;
	return Status::HELLA_OK;
}

Hella::Status Hella::SqBiTree::Root(ElemType& e)
{
	if (m_Base[0] == -1)
		return Status::HELLA_ERROR;
	e = m_Base[0];
	return Status::HELLA_OK;
}

Hella::Status Hella::SqBiTree::Parent(ElemType e, ElemType& parent)
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

Hella::Status Hella::SqBiTree::LeftChild(ElemType e, ElemType& lchild)
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

Hella::Status Hella::SqBiTree::RightChild(ElemType e, ElemType& rchild)
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

Hella::Status Hella::SqBiTree::LeftSibling(ElemType e, ElemType& lsibling)
{
	if (m_Base[0] == -1)
		return Status::HELLA_INFEASIBLE;
	for (int i = 0; i < m_Size; i++) {
		if (i%2 == 0 && m_Base[i] == e) {
			lsibling = m_Base[i - 1];
			return Status::HELLA_OK;
		}
	}
	return Status::HELLA_NOT_FOUND;
}

Hella::Status Hella::SqBiTree::RightSibling(ElemType e, ElemType& rsibling)
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


Hella::Status Hella::SqBiTree::PreOrderTraverse(void(*visit)(ElemType&))
{
	return PreOrderTraverseRec(visit, 0);
}

Hella::Status Hella::SqBiTree::InOrderTraverse(void(*visit)(ElemType&))
{
	return InOrderTraverseRec(visit, 0);
}

Hella::Status Hella::SqBiTree::PostOrderTraverse(void(*visit)(ElemType&))
{
	return PostOrderTraverseRec(visit, 0);
}

Hella::Status Hella::SqBiTree::LevelOrderTraverse(void(*visit)(ElemType&))
{
	for (int i = 0; i < m_Size; i++) {
		if (m_Base[i] != -1)
			visit(m_Base[i]);
	}
	return Status::HELLA_OK;
}

Hella::Status Hella::SqBiTree::PreOrderTraverseRec(void(*visit)(ElemType&), const int i)
{
	if (i < m_Size && m_Base[i] != -1) {
		visit(m_Base[i]);
		PreOrderTraverseRec(visit, i * 2 + 1);
		PreOrderTraverseRec(visit, i * 2 + 2);
	}
	return Status::HELLA_OK;
}



Hella::Status Hella::SqBiTree::InOrderTraverseRec(void(*visit)(ElemType&), const int i)
{
	if (i < m_Size && m_Base[i] != -1) {
		PreOrderTraverseRec(visit, i * 2 + 1);
		visit(m_Base[i]);
		PreOrderTraverseRec(visit, i * 2 + 2);
	}
	return Status::HELLA_OK;
}

Hella::Status Hella::SqBiTree::PostOrderTraverseRec(void(*visit)(ElemType&), const int i)
{
	if (i < m_Size && m_Base[i] != -1) {
		PreOrderTraverseRec(visit, i * 2 + 1);
		PreOrderTraverseRec(visit, i * 2 + 2);
		visit(m_Base[i]);
	}
	return Status::HELLA_OK;
}


Hella::Status Hella::SqBiTree::CreateByLev(ElemType* e, ElemType format)
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

Hella::Status Hella::SqBiTree::CreateByPre(ElemType* e, ElemType format, int index)
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

Hella::Status Hella::SqBiTree::GetElemByIndex(int i,ElemType& e)
{
	int len;
	Length(len);
	if (i >= len) {
		return Status::HELLA_INFEASIBLE;
	}
	e = m_Base[i];
	return Status::HELLA_OK;
}


