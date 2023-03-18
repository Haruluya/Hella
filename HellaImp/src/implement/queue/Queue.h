

#pragma once

#include"base/Status.h"
#include "DataStruct.h"

/*
	@author:Haruluya.
	@function:The abstrcation of Stack.
*/
namespace Hella {
	template <typename ElemType>
	class Queue : public DataStruct
	{
	public:
		Queue() { };
		virtual ~Queue() {};
		virtual Status Init() = 0;
		virtual Status Destory() = 0;
		virtual Status Clear() = 0;
		virtual Status IsEmpty() = 0;
		virtual Status Length(ElemType& len) = 0;
		virtual Status GetHead(ElemType& e) = 0;
		virtual Status EnQueue(ElemType e) = 0;
		virtual Status DeQueue(ElemType& e) = 0;
		virtual Status Traverse(void (*visit)(ElemType& e)) = 0;
		virtual std::string DataToString();
	protected:
	};
}

template <typename ElemType>
std::string Hella::Queue<ElemType>::DataToString()
{
	std::string data = "[ ";
	ElemType e; int len = 0;
	std::vector<ElemType> tempValueVector;
	Length(len);
	for (int i = 1; i <= len; i++) {
		DeQueue(e);
		data += std::to_string(e) + ",";
		tempValueVector.push_back(e);
	}
	for (int j = 1; j <= len; j++) {
		EnQueue(tempValueVector[j - 1]);
	}
	data += " ]";
	return data;
}
