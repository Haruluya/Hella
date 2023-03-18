#pragma once

#include "Queue.h"
template <typename ElemType>
struct QNode {
	ElemType data;
	QNode<ElemType>* next;
};

namespace Hella {
	template <typename ElemType>
	class  LinkQueue : public Queue<ElemType> {
	public:
		// Í¨¹ý Queue ¼Ì³Ð
		virtual Status Init() override;
		virtual Status Destory() override;
		virtual Status Clear() override;
		virtual Status IsEmpty() override;
		virtual Status Length(ElemType& len) override;
		virtual Status GetHead(ElemType& e) override;
		virtual Status EnQueue(ElemType e) override;
		virtual Status DeQueue(ElemType& e) override;
		virtual Status Traverse(void(*visit)(ElemType& e)) override;
	private:
		QNode<ElemType>* m_Front;
		QNode<ElemType>* m_Rear;
	};
}


namespace Hella {
    template <typename ElemType>
    Status LinkQueue<ElemType>::Init()
    {
        m_Front = HELLA_MALLOC(1, QNode<ElemType>);
        HELLA_ASSERT_MEMORY_MALLOC(m_Front);

        m_Rear = m_Front;
        m_Front->next = NULL;
        return Status::HELLA_OK;
    }
    template <typename ElemType>
    Status LinkQueue<ElemType>::Destory()
    {
        while (m_Front) {
            m_Rear = m_Front->next;
            HELLA_FREE(m_Front);
            m_Front = m_Rear;
        }
        return Status::HELLA_OK;
    }
    template <typename ElemType>
    Status LinkQueue<ElemType>::Clear()
    {
        m_Rear = m_Front->next;
        while (m_Rear) {
            m_Front->next = m_Rear->next;
            HELLA_FREE(m_Rear);
            m_Rear = m_Front->next;
        }
        m_Rear = m_Front;
        return Status::HELLA_OK;
    }
    template <typename ElemType>
    Status LinkQueue<ElemType>::IsEmpty()
    {
        if (m_Front == m_Rear)
            return Status::HELLA_TRUE;
        return Status::HELLA_FALSE;
    }
    template <typename ElemType>
    Status LinkQueue<ElemType>::Length(ElemType& len)
    {
        int i = 0;
        QNode<ElemType>* p = m_Front;

        //null or rear.
        while (p != m_Rear) {
            i++;
            p = p->next;
        }
        len = i;
        return Status::HELLA_OK;
    }
    template <typename ElemType>
    Status LinkQueue<ElemType>::GetHead(ElemType& e)
    {
        if (m_Front == m_Rear)
            return Status::HELLA_INFEASIBLE;
        e = m_Front->next->data;
        return Status::HELLA_OK;
    }
    template <typename ElemType>
    Status LinkQueue<ElemType>::EnQueue(ElemType e)
    {
        QNode<ElemType>* newNode = HELLA_MALLOC(1, QNode<ElemType>);
        HELLA_ASSERT_MEMORY_MALLOC(newNode);
        newNode->data = e;
        newNode->next = NULL;
        m_Rear->next = newNode;
        m_Rear = newNode;
        return Status::HELLA_OK;
    }
    template <typename ElemType>
    Status LinkQueue<ElemType>::DeQueue(ElemType& e)
    {
        if (m_Front == m_Rear)
            return Status::HELLA_INFEASIBLE;

        QNode<ElemType>* p = m_Front->next;
        e = p->data;
        m_Front->next = p->next;
        if (m_Rear == p)
            m_Rear = m_Front;

        HELLA_FREE(p);
        return Status::HELLA_OK;
    }
    template <typename ElemType>
    Status LinkQueue<ElemType>::Traverse(void(*visit)(ElemType& e))
    {
        QNode<ElemType>* p = m_Front;
        while (p->next) {
            p = p->next;
            visit(p->data);
        }
        return Status::HELLA_OK;

    }

}