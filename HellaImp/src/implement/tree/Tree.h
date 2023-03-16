#pragma once
#include"base/Status.h"
#include"DataStruct.h"
#include <utility>
typedef struct Position {
	int level;
	int order;
}Position;

namespace Hella {
	class Tree :public DataStruct
	{
		virtual Status Init() = 0;
		virtual Status Destroy() = 0;
		virtual Status Clear() = 0;
		virtual Status IsEmpty() = 0;
		virtual Status Depth(int& depth) = 0;
		virtual Status Length(int& len) = 0;
		virtual Status Value(Position p, ElemType& e) = 0;
		virtual Status Assign(Position p, ElemType value) = 0;
		virtual Status Root(ElemType& e) = 0;
		virtual Status Parent(ElemType e, ElemType& parent) = 0;
	};
}