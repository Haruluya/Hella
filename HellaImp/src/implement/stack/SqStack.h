#pragma once

#include "Stack.h"

namespace Hella {
	template <typename ElemType>
	class SqStack : public Stack<ElemType>{
	public:
		// 通过 Stack 继承
		virtual Status Init() override;
		virtual Status Destory() override;
		virtual Status Clear() override;
		virtual Status IsEmpty() const override;
		virtual Status Length(int& len)const override;
		virtual Status GetTop(ElemType& e)const override;
		virtual Status Push(ElemType e) override;
		virtual Status Pop(ElemType& e) override;
		virtual Status Traverse(void(*visit)(ElemType& e)) override;
	private:
		ElemType* m_Top;
		ElemType* m_Base;
		int m_Size;
	};

}

namespace Hella {
	template <typename ElemType>
	Status SqStack<ElemType>::Init()
	{
		m_Base = HELLA_MALLOC(HELLA_STACK_INIT_SIZE, ElemType);
		HELLA_ASSERT_MEMORY_MALLOC(m_Base);

		m_Top = m_Base;
		m_Size = HELLA_STACK_INIT_SIZE;
		return Status::HELLA_OK;
	}
	template <typename ElemType>
	Status SqStack<ElemType>::Destory()
	{
		HELLA_FREE(m_Base);

		m_Base = m_Top = NULL;
		m_Size = 0;
		return Status::HELLA_OK;
	}
	template <typename ElemType>
	Status SqStack<ElemType>::Clear()
	{
		m_Top = m_Base;
		return Status::HELLA_OK;
	}
	template <typename ElemType>
	Status SqStack<ElemType>::IsEmpty()const
	{
		if (m_Top == m_Base)
			return Status::HELLA_TRUE;
		return Status::HELLA_FALSE;
	}
	template <typename ElemType>
	Status SqStack<ElemType>::Length(int& len)const
	{
		len = m_Top - m_Base;
		return Status::HELLA_OK;
	}
	template <typename ElemType>
	Status SqStack<ElemType>::GetTop(ElemType& e)const
	{
		if (m_Top == m_Base)
			return Status::HELLA_INFEASIBLE;
		e = *(m_Top - 1);
		return Status::HELLA_OK;
	}
	template <typename ElemType>
	Status SqStack<ElemType>::Push(ElemType e)
	{
		if (m_Top - m_Base >= m_Size) {
			int len = m_Top - m_Base;
			ElemType* newBase = (ElemType*)HELLA_REALLOC(m_Base, m_Size + HELLA_STACK_INCREMENT);
			HELLA_ASSERT_MEMORY_MALLOC(newBase);
			m_Base = newBase;
			//注意realloc 可能返回的新内存。
			m_Top = m_Base + len;
			m_Size += HELLA_STACK_INCREMENT;
		}
		*m_Top = e;
		m_Top++;
		return Status::HELLA_OK;
	}
	template <typename ElemType>
	Status SqStack<ElemType>::Pop(ElemType& e)
	{
		if (m_Top == m_Base) {
			return Status::HELLA_INFEASIBLE;
		}
		e = *(m_Top - 1);
		m_Top--;
		return Status::HELLA_OK;
	}
	template <typename ElemType>
	Status SqStack<ElemType>::Traverse(void(*visit)(ElemType& e))
	{
		ElemType* p = m_Base;
		while (p < m_Top) {
			visit(*p);
			p++;
		}
		return Status::HELLA_OK;
	}

}