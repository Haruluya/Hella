

#pragma once

#include"base/Status.h"
#include "DataStruct.h"

/*
	@author:Haruluya.
	@function:The abstrcation of Stack.
*/
namespace Hella {
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

