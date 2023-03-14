#include "hlpch.h"
#include "SqStack.h"


namespace Hella {

	Status SqStack::Init()
	{
		m_Base = HELLA_MALLOC(HELLA_STACK_INIT_SIZE, ElemType);
		HELLA_ASSERT_MEMORY_MALLOC(m_Base);
	
		m_Top = m_Base;
		m_Size = HELLA_STACK_INIT_SIZE;
		return Status::HELLA_OK;
	}

	Status SqStack::Destory()
	{
		HELLA_FREE(m_Base);

		m_Base = m_Top = NULL;
		m_Size = 0;
		return Status::HELLA_OK;
	}

	Status SqStack::Clear()
	{
		m_Top = m_Base;
		return Status::HELLA_OK;
	}

	Status SqStack::IsEmpty()const
	{
		if (m_Top == m_Base)
			return Status::HELLA_TRUE;
		return Status::HELLA_FALSE;
	}

	Status SqStack::Length(int& len)const
	{
		len = m_Top - m_Base;
		return Status::HELLA_OK;
	}

	Status SqStack::GetTop(ElemType& e)const
	{
		if (m_Top == m_Base)
			return Status::HELLA_INFEASIBLE;
		e = *(m_Top - 1);
		return Status::HELLA_OK;
	}

	Status SqStack::Push(ElemType e)
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

	Status SqStack::Pop(ElemType& e)
	{
		if (m_Top == m_Base) {
			return Status::HELLA_INFEASIBLE;
		}
		e = *(m_Top - 1);
		m_Top--;
		return Status::HELLA_OK;
	}

	Status SqStack::Traverse(void(*visit)(ElemType& e))
	{
		ElemType* p = m_Base;
		while (p < m_Top) {
			visit(*p);
			p++;
		}
		return Status::HELLA_OK;
	}

}