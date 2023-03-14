#pragma once
#include "hlpch.h"
#include "SqList.h"

namespace Hella {

	//初始化顺序列表。
	Status SqList::Init()
	{
		//分配内存并检查。
		m_Elem = HELLA_MALLOC(HELLA_LIST_INIT_SIZE, ElemType);
		HELLA_ASSERT_MEMORY_MALLOC(m_Elem);

		m_Length = 0;
		m_ListSize = HELLA_LIST_INIT_SIZE;

		return Status::HELLA_OK;
	}

	Status SqList::Destroy()
	{
		HELLA_FREE(m_Elem);
		m_Length = 0;
		m_ListSize = 0;
		return Status::HELLA_OK;
	}

	Status SqList::Clear()
	{
		m_Length = 0;
		return Status::HELLA_OK;
	}

	Status SqList::IsEmpty()
	{
		return (m_Length == 0)? Status::HELLA_TRUE : Status::HELLA_FALSE;
	}

	Status SqList::Length(int& len)
	{
		len = m_Length;
		return Status::HELLA_OK;
	}

	Status SqList::GetElem(int i, ElemType& e)
	{
		if (i <1 || i >m_Length) return Status::HELLA_ERROR;
		e = m_Elem[i-1];
		return Status::HELLA_OK;
	}

	Status SqList::LocateElem(ElemType e, bool(*compare)(ElemType e1, ElemType e2),int& index)
	{
		int i = 1;
		while (i <= m_Length && !(compare(e,m_Elem[i-1]))) {
			i++;
		}
		if (i <= m_Length) {
			index = i; return Status::HELLA_OK;
		}
	
		index = -1; return Status::HELLA_NOT_FOUND;

	}

	Status SqList::PriorElem(ElemType cur_e, ElemType& pre_e)
	{
		int i = 1;
		while (i <= m_Length && cur_e != m_Elem[i - 1]) {
			i++;
		}
		if (i <= m_Length && i >= 2) {
			pre_e = m_Elem[i - 2];
			return Status::HELLA_OK;
		}
		pre_e = NULL;
		return Status::HELLA_NOT_FOUND;
	}

	Status SqList::NextElem(ElemType cur_e, ElemType& next_e)
	{
		int i = 1;
		while (i <= m_Length && cur_e != m_Elem[i - 1]) {
			i++;
		}
		if (i < m_Length) {
			next_e = m_Elem[i];
			return Status::HELLA_OK;
		}
		next_e = NULL;
		return Status::HELLA_NOT_FOUND;
	}

	Status SqList::Insert(int i, ElemType e)
	{
		HELLA_ASSERT_INDEX_INFEASIBLE(i, 1, m_Length+1);

		ElemType* p, *q;

		if (m_Length >= m_ListSize) {
			ElemType* newBase = (ElemType*)HELLA_REALLOC(m_Elem, m_Length + HELLA_LIST_INCREMENT);
			HELLA_ASSERT_MEMORY_MALLOC(newBase);
			m_Elem = newBase;
			m_ListSize += HELLA_LIST_INCREMENT;
		}

		p = &m_Elem[i - 1];

		if (m_Length != 0)
		{
			for (q = &m_Elem[m_Length - 1]; q >= p; q--) {
				*(q + 1) = *q;
			}
		}
		*p = e;

		m_Length++;

		return Status::HELLA_OK;
	}

	Status SqList::Delete(int i, ElemType& e)
	{
		HELLA_ASSERT_INDEX_INFEASIBLE(i, 1, m_Length);
		ElemType* q;
		e = m_Elem[i - 1];

		for (q = &m_Elem[i - 1 + 1]; q <= &m_Elem[m_Length - 1]; q++) {
			*(q - 1) = *q;
		}

		m_Length--;
		return Status::HELLA_OK;

	}

	Status SqList::Traverse(void(*visit)(ElemType& e))
	{
		if (IsEmpty() == Status::HELLA_TRUE)
			return Status::HELLA_OK;
		for (int i = 1; i <= m_Length; i++)
			visit(m_Elem[i - 1]);
		return Status::HELLA_OK;
	}


}