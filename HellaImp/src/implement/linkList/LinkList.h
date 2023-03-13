#pragma once




#include"base/Status.h"
#include "DataStruct.h"

/*
	@author:Haruluya.
	@function:The abstrcation of linklist.
*/
namespace Hella {
	class LinkList : public DataStruct
	{
	public:
		LinkList() { m_Length = 0; };
		virtual ~LinkList() {};
		virtual Status Init() = 0;
		virtual Status Destroy() = 0;
		virtual Status Clear() = 0;
		virtual Status IsEmpty() = 0;
		virtual Status Length(int& len) = 0;
		virtual Status GetElem(int i, ElemType& e) = 0;
		virtual Status LocateElem(ElemType e, bool (*compare)(ElemType e1, ElemType e2), int& index) = 0;
		virtual Status PriorElem(ElemType cur_e, ElemType& pre_e) = 0;
		virtual Status NextElem(ElemType cur_e, ElemType& next_e) = 0;
		virtual Status Insert(int i, ElemType e) = 0;
		virtual Status Delete(int i, ElemType& e) = 0;
		virtual Status Traverse(void (*visit)(ElemType& e)) = 0;
		virtual std::string DataToString();
	protected:
		int m_Length;
	};
}

