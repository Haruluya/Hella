#pragma once

#include "Stack.h"

namespace Hella {
	class SqStack : public Stack{
	public:
		// Í¨¹ý Stack ¼Ì³Ð
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