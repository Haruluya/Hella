#pragma once
#include "BiTree.h"

#define HELLA_SQBITREE_MAX_SIZE 50

namespace Hella {
	class SqBiTree : public BiTree
	{
	public:
		// Í¨¹ý BiTree ¼Ì³Ð
		virtual Status Init() override;

		virtual Status Destroy() override;

		virtual Status Clear() override;

		virtual Status IsEmpty() override;

		virtual Status Depth(int& depth) override;

		virtual Status Length(int& len) override;

		virtual Status Value(Position p, ElemType& e) override;

		virtual Status Assign(Position p, ElemType value) override;

		virtual Status Root(ElemType& e) override;

		virtual Status Parent(ElemType e, ElemType& parent) override;

		virtual Status LeftChild(ElemType e, ElemType& lchild) override;

		virtual Status RightChild(ElemType e, ElemType& rchild) override;

		virtual Status LeftSibling(ElemType e, ElemType& lsibling) override;

		virtual Status RightSibling(ElemType e, ElemType& rsibling) override;

		virtual Status PreOrderTraverse(void(*visit)(ElemType&)) override;

		virtual Status InOrderTraverse(void(*visit)(ElemType&)) override;

		virtual Status PostOrderTraverse(void(*visit)(ElemType&)) override;

		virtual Status LevelOrderTraverse(void(*visit)(ElemType&)) override;

		virtual Status CreateByLev(ElemType* e, ElemType format) override;
		virtual Status CreateByPre(ElemType* e, ElemType format, int index) override;

		virtual Status GetElemByIndex(int,ElemType&) override;
	private:
		ElemType* m_Base;
		int m_Size;

		virtual Status PreOrderTraverseRec(void(*visit)(ElemType&), const int i);

		virtual Status InOrderTraverseRec(void(*visit)(ElemType&), const int i);

		virtual Status PostOrderTraverseRec(void(*visit)(ElemType&), const int i);




	};
}