#pragma once
#include "LinkList.h"

/*
	@author:Haruluya.
	@function:The implement of single linked list.
*/
namespace Hella {

	template <typename ElemType>
	struct LNode
	{
		ElemType data;
		struct LNode<ElemType>* next;
	};



	template <typename ElemType>
	class SinglyLinkedList : public LinkList<ElemType>
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
		LNode<ElemType>* m_HeadNode{};
	};
}

namespace Hella {
	template <typename ElemType>
	Status Hella::SinglyLinkedList<ElemType>::Init()
	{
		m_HeadNode = HELLA_MALLOC(1, LNode<ElemType>);
		HELLA_ASSERT_MEMORY_MALLOC(m_HeadNode);

		m_HeadNode->next = NULL;
		return Status::HELLA_OK;
	}
	template <typename ElemType>
	Status Hella::SinglyLinkedList<ElemType>::Destroy()
	{
		LNode<ElemType>* p = m_HeadNode;
		while (p) {
			p = p->next;
			HELLA_FREE(m_HeadNode);
			m_HeadNode = p;
		}
		return Status::HELLA_OK;
	}
	template <typename ElemType>
	Status Hella::SinglyLinkedList<ElemType>::Clear()
	{
		LNode<ElemType>* p1, * p2;
		p1 = p2 = m_HeadNode;
		while (p2) {
			p2 = p2->next;
			HELLA_FREE(p2);
			p1 = p2;
		}
		if (m_HeadNode)
			m_HeadNode->next = NULL;
		return Status::HELLA_OK;
	}
	template <typename ElemType>
	Status Hella::SinglyLinkedList<ElemType>::IsEmpty()
	{
		if (!m_HeadNode->next) {
			return Status::HELLA_TRUE;
		}
		return Status::HELLA_FALSE;
	}
	template <typename ElemType>
	Status Hella::SinglyLinkedList<ElemType>::Length(int& len)
	{
		int l = 0;
		LNode<ElemType>* p = m_HeadNode;
		while (p->next)
		{
			p = p->next;
			l++;
		};
		len = l;
		return Status::HELLA_OK;
	}
	template <typename ElemType>
	Status Hella::SinglyLinkedList<ElemType>::GetElem(int i, ElemType& e)
	{
		LNode<ElemType>* p = m_HeadNode;
		while (i-- && p) {
			p = p->next;
		}
		if (!p)
			return Status::HELLA_INFEASIBLE;
		e = p->data;
		return Status::HELLA_OK;
	}
	template <typename ElemType>
	Status Hella::SinglyLinkedList<ElemType>::LocateElem(ElemType e, bool(*compare)(ElemType e1, ElemType e2), int& index)
	{
		LNode<ElemType>* p = m_HeadNode;
		int i = 0;
		while (p->next)
		{
			p = p->next; i++;
			if (compare(p->data, e)) {
				index = i;
				return Status::HELLA_OK;
			}
		}
		return Status::HELLA_NOT_FOUND;

	}
	template <typename ElemType>
	Status Hella::SinglyLinkedList<ElemType>::PriorElem(ElemType cur_e, ElemType& pre_e)
	{
		LNode<ElemType>* p = m_HeadNode;
		LNode<ElemType>* pre_p = p;
		while (p->next)
		{
			p = p->next;
			if (p->data == cur_e) {
				if (p != m_HeadNode) {
					pre_e = pre_p->data;
					return Status::HELLA_OK;
				}
				return Status::HELLA_INFEASIBLE;
			}
			pre_p = p;
		}
		return Status::HELLA_NOT_FOUND;
	}
	template <typename ElemType>
	Status Hella::SinglyLinkedList<ElemType>::NextElem(ElemType cur_e, ElemType& next_e)
	{
		LNode<ElemType>* p = m_HeadNode;
		while (p->next)
		{
			p = p->next;
			if (p->data == cur_e) {
				if (p->next) {
					next_e = p->next->data;
					return Status::HELLA_OK;
				}
				return Status::HELLA_INFEASIBLE;
			}
		}
		return Status::HELLA_NOT_FOUND;
	}
	template <typename ElemType>
	Status Hella::SinglyLinkedList<ElemType>::Insert(int i, ElemType e)
	{
		LNode<ElemType>* p1 = m_HeadNode, * p2 = m_HeadNode;
		while (i-- && p2) {
			p1 = p2;
			p2 = p2->next;
		}
		if (!p1) {
			return Status::HELLA_INFEASIBLE;
		}
		LNode<ElemType>* newNode = HELLA_MALLOC(1, LNode<ElemType>);
		HELLA_ASSERT_MEMORY_MALLOC(newNode);
		newNode->data = e;
		p1->next = newNode;
		if (!p2) {
			newNode->next = NULL;
		}
		else {
			newNode->next = p2;
		}
		return Status::HELLA_OK;
	}
	template <typename ElemType>
	Status Hella::SinglyLinkedList<ElemType>::Delete(int i, ElemType& e)
	{
		LNode<ElemType>* p1 = m_HeadNode, * p2 = m_HeadNode;
		while (i-- && p2) {
			p1 = p2;
			p2 = p2->next;
		}
		if (!p1 || !p2) {
			return Status::HELLA_INFEASIBLE;
		}
		e = p2->data;
		p1->next = p2->next;
		return Status::HELLA_OK;

	}
	template <typename ElemType>
	Status Hella::SinglyLinkedList<ElemType>::Traverse(void(*visit)(ElemType& e))
	{
		LNode<ElemType>* p = m_HeadNode;
		while (p->next) {
			p = p->next;
			visit(p->data);
		}
		return Status::HELLA_OK;
	}



}