#pragma once

#include "Tree.h"

namespace Hella {
	template <typename ElemType>
	class BiTree : public Tree<ElemType>
	{
	public:
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

		virtual Status Create(ElemType* e, ElemType format, ElemType type) = 0;

		virtual Status LeftChild(ElemType e, ElemType& lchild) = 0;
		virtual Status RightChild(ElemType e, ElemType& rchild) = 0;
		virtual Status LeftSibling(ElemType e, ElemType& lsibling) = 0;
		virtual Status RightSibling(ElemType e, ElemType& rsibling) = 0;
		virtual Status PreOrderTraverse(void(*visit)(ElemType&)) = 0;
		virtual Status InOrderTraverse(void(*visit)(ElemType&)) = 0;
		virtual Status PostOrderTraverse(void(*visit)(ElemType&)) = 0;
		virtual Status LevelOrderTraverse(void(*visit)(ElemType&)) = 0;
		virtual std::string DataToString() override;

	private:
		virtual Status GetElemByIndex(int, ElemType&) = 0;


	};
}


template <typename ElemType>
std::string Hella::BiTree<ElemType>::DataToString()
{
	std::string data = "[ ";

	int len, e;
	Length(len);
	for (int i = 0; i < len; i++) {
		GetElemByIndex(i, e);
		data += std::to_string(e) + ",";
	}
	data += " ]";
	return data;
}

