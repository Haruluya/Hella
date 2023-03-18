
#pragma once

#include"base/Status.h"
#include "DataStruct.h"

#define HELLA_STACK_INIT_SIZE 50
#define HELLA_STACK_INCREMENT 50
/*
	@author:Haruluya.
	@function:The abstrcation of Stack.
*/
namespace Hella {
	template <typename ElemType>
	class Stack : public DataStruct
	{
	public:
		Stack() { };
		virtual ~Stack() {};
		virtual Status Init() = 0;
		virtual Status Destory() = 0;
		virtual Status Clear() = 0;
		virtual Status IsEmpty() const = 0;
		virtual Status Length(int& len) const = 0;
		virtual Status GetTop(ElemType& e) const= 0;
		virtual Status Push(ElemType e) = 0;
		virtual Status Pop(ElemType& e) = 0;
		virtual Status Traverse( void(*visit)(ElemType& e)) = 0;
		virtual std::string DataToString();
	protected:
	};
}


template <typename ElemType>
std::string Hella::Stack<ElemType>::DataToString()
{
	std::string data = "[ ";
	ElemType e; int len = 0;
	std::vector<ElemType> tempValueVector;
	Length(len);
	for (int i = 1; i <= len; i++) {
		Pop(e);
		data += std::to_string(e) + ",";
		tempValueVector.push_back(e);
	}
	for (int j = 1; j <= len; j++) {
		Push(tempValueVector[len - j]);
	}
	data += " ]";
	return data;
}