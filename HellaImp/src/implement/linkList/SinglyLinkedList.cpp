#include"hlpch.h"
#include "SinglyLinkedList.h"

namespace Hella {
	Status Hella::SinglyLinkedList::Init()
	{
		m_HeadNode = HELLA_MALLOC(1, LNode);
		HELLA_ASSERT_MEMORY_MALLOC(m_HeadNode);
		
		m_HeadNode->next = NULL;
		return Status::HELLA_OK;
	}

	Status Hella::SinglyLinkedList::Destroy()
	{
		LNode* p = m_HeadNode;
		while (p) {
			p = p->next;
			HELLA_FREE(m_HeadNode);
			m_HeadNode = p;
		}
		return Status::HELLA_OK;
	}

	Status Hella::SinglyLinkedList::Clear()
	{
		LNode* p1, *p2;
		p1 = p2 = m_HeadNode;
		while (p2) {
			p2 = p2->next;
			HELLA_FREE(p2);
			p1 = p2;
		}
		if(m_HeadNode)
			m_HeadNode->next = NULL;
		return Status::HELLA_OK;
	}

	Status Hella::SinglyLinkedList::IsEmpty()
	{	
		if (!m_HeadNode->next) {
			return Status::HELLA_TRUE;
		}
		return Status::HELLA_FALSE;
	}

	Status Hella::SinglyLinkedList::Length(int& len)
	{
		int l = 0;
		LNode* p = m_HeadNode;
		while (p->next) 
		{
			p = p->next;
			l++;
		} ;
		len = l;
		return Status::HELLA_OK;
	}

	Status Hella::SinglyLinkedList::GetElem(int i, ElemType& e)
	{
		LNode* p = m_HeadNode;
		while (i-- && p) {
			p = p->next;
		}
		if (!p)
			return Status::HELLA_INFEASIBLE;
		e = p->data;
		return Status::HELLA_OK;
	}

	Status Hella::SinglyLinkedList::LocateElem(ElemType e, bool(*compare)(ElemType e1, ElemType e2), int& index)
	{
		LNode* p = m_HeadNode;
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

	Status Hella::SinglyLinkedList::PriorElem(ElemType cur_e, ElemType& pre_e)
	{
		LNode* p = m_HeadNode;
		LNode* pre_p = p;
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

	Status Hella::SinglyLinkedList::NextElem(ElemType cur_e, ElemType& next_e)
	{
		LNode* p = m_HeadNode;
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

	Status Hella::SinglyLinkedList::Insert(int i, ElemType e)
	{
		LNode* p1 = m_HeadNode, * p2 = m_HeadNode;
		while (i-- && p2) {
			p1 = p2;
			p2 = p2->next;
		}
		if (!p1) {
			return Status::HELLA_INFEASIBLE;
		}
		LNode* newNode = HELLA_MALLOC(1, LNode);
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

	Status Hella::SinglyLinkedList::Delete(int i, ElemType& e)
	{
		LNode* p1 = m_HeadNode, * p2 = m_HeadNode;
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

	Status Hella::SinglyLinkedList::Traverse(void(*visit)(ElemType& e))
	{
		LNode* p = m_HeadNode;
		while (p->next) {
			p = p->next;
			visit(p->data);
		}
		return Status::HELLA_OK;
	}



}