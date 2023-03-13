#pragma once
#include "LinkList.h"

/*
	@author:Haruluya.
	@function:The implement of single linked list.
*/
namespace Hella {
	typedef struct LNode
	{
		ElemType data;
		struct LNode* next;
	}LNode;


	class SinglyLinkedList : public LinkList
	{
	public:
		SinglyLinkedList() {};
		~SinglyLinkedList() {};

		// Í¨¹ý LinkList ¼Ì³Ð
		virtual Status Init() override;
		virtual Status Destroy() override;
		virtual Status Clear() override;
		virtual Status IsEmpty() override;
		virtual Status Length(int& len) override;
		virtual Status GetElem(int i, ElemType& e) override;
		virtual Status LocateElem(ElemType e, bool(*compare)(ElemType e1, ElemType e2), int& index) override;
		virtual Status PriorElem(ElemType cur_e, ElemType& pre_e) override;
		virtual Status NextElem(ElemType cur_e, ElemType& next_e) override;
		virtual Status Insert(int i, ElemType e) override;
		virtual Status Delete(int i, ElemType& e) override;
		virtual Status Traverse(void(*visit)(ElemType& e)) override;

	private:
		LNode* m_HeadNode{};
	};
}