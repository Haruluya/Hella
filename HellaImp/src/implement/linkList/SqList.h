#pragma once
#include "LinkList.h"

/*
	@author:Haruluya.
	@function:The implement of sequence table.
*/

#define HELLA_LIST_INIT_SIZE 50
#define HELLA_LIST_INCREMENT 50

//顺序表定义。
namespace Hella {
	template <typename ElemType>
	class SqList : public LinkList<ElemType>
	{
	public:
		SqList() {};
		~SqList() {};

	public:
		// 通过 LinkList 继承
		virtual Status Init() override;

		virtual Status Destroy() override;

		virtual Status Clear() override;

		virtual Status IsEmpty() override;

		virtual Status Length(int& len) override;

		virtual Status GetElem(int i, ElemType& e) override;

		virtual Status LocateElem(ElemType e, bool(*compare)(ElemType e1, ElemType e2), int& index) override;

		virtual Status PriorElem(ElemType cur_e, ElemType& pre_e) override;

		virtual Status NextElem(ElemType cur_e, ElemType& next_e) override;

		virtual Status Insert(int i, ElemType e) override;

		virtual Status Delete(int i, ElemType& e) override;

		virtual Status Traverse(void(*visit)(ElemType& e)) override;


	private:
		int m_Length;
		int m_ListSize{};
		ElemType* m_Elem{};


	};

}


namespace Hella {

	//初始化顺序列表。
	template <typename ElemType>
	Status SqList<ElemType>::Init()
	{
		//分配内存并检查。
		m_Elem = HELLA_MALLOC(HELLA_LIST_INIT_SIZE, ElemType);
		HELLA_ASSERT_MEMORY_MALLOC(m_Elem);

		m_Length = 0;
		m_ListSize = HELLA_LIST_INIT_SIZE;

		return Status::HELLA_OK;
	}

	template <typename ElemType>
	Status SqList<ElemType>::Destroy()
	{
		HELLA_FREE(m_Elem);
		m_Length = 0;
		m_ListSize = 0;
		return Status::HELLA_OK;
	}

	template <typename ElemType>
	Status SqList<ElemType>::Clear()
	{
		m_Length = 0;
		return Status::HELLA_OK;
	}

	template <typename ElemType>
	Status SqList<ElemType>::IsEmpty()
	{
		return (m_Length == 0) ? Status::HELLA_TRUE : Status::HELLA_FALSE;
	}

	template <typename ElemType>
	Status SqList<ElemType>::Length(int& len)
	{
		len = m_Length;
		return Status::HELLA_OK;
	}

	template <typename ElemType>
	Status SqList<ElemType>::GetElem(int i, ElemType& e)
	{
		if (i <1 || i >m_Length) return Status::HELLA_ERROR;
		e = m_Elem[i - 1];
		return Status::HELLA_OK;
	}

	template <typename ElemType>
	Status SqList<ElemType>::LocateElem(ElemType e, bool(*compare)(ElemType e1, ElemType e2), int& index)
	{
		int i = 1;
		while (i <= m_Length && !(compare(e, m_Elem[i - 1]))) {
			i++;
		}
		if (i <= m_Length) {
			index = i; return Status::HELLA_OK;
		}

		index = -1; return Status::HELLA_NOT_FOUND;

	}

	template <typename ElemType>
	Status SqList<ElemType>::PriorElem(ElemType cur_e, ElemType& pre_e)
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

	template <typename ElemType>
	Status SqList<ElemType>::NextElem(ElemType cur_e, ElemType& next_e)
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

	template <typename ElemType>
	Status SqList<ElemType>::Insert(int i, ElemType e)
	{
		HELLA_ASSERT_INDEX_INFEASIBLE(i, 1, m_Length + 1);

		ElemType* p, * q;

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

	template <typename ElemType>
	Status SqList<ElemType>::Delete(int i, ElemType& e)
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


	template <typename ElemType>
	Status SqList<ElemType>::Traverse(void(*visit)(ElemType& e))
	{
		if (IsEmpty() == Status::HELLA_TRUE)
			return Status::HELLA_OK;
		for (int i = 1; i <= m_Length; i++)
			visit(m_Elem[i - 1]);
		return Status::HELLA_OK;
	}


}

