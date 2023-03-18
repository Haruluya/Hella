#pragma once




#include"base/Status.h"
#include "DataStruct.h"

/*
	@author:Haruluya.
	@function:The abstrcation of linklist.
*/
namespace Hella {
	template <typename ElemType>
	class LinkList : public DataStruct
	{
	public:
		LinkList() { };
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

	};
}

template <typename ElemType>
std::string Hella::LinkList<ElemType>::DataToString()
{
	std::string data = "[ ";
	ElemType e; int len = 0;
	Length(len);
	for (int i = 1; i <= len; i++) {
		GetElem(i, e);
		data += std::to_string(e) + ",";
	}
	data += " ]";
	return data;
}