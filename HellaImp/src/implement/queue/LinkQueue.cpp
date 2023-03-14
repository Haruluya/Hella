#include "hlpch.h"

#include "LinkQueue.h"
namespace Hella {
    Status LinkQueue::Init()
    {
        m_Front = HELLA_MALLOC(1, QNode);
        HELLA_ASSERT_MEMORY_MALLOC(m_Front);

        m_Rear = m_Front;
        m_Front->next = NULL;
        return Status::HELLA_OK;
    }

    Status LinkQueue::Destory()
    {
        while (m_Front) {
            m_Rear = m_Front->next;
            HELLA_FREE(m_Front);
            m_Front = m_Rear;
        }
        return Status::HELLA_OK;
    }

    Status LinkQueue::Clear()
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

    Status LinkQueue::IsEmpty()
    {
        if (m_Front == m_Rear)
            return Status::HELLA_TRUE;
        return Status::HELLA_FALSE;
    }

    Status LinkQueue::Length(ElemType& len)
    {
        int i = 0;
        QNode* p = m_Front;

        //null or rear.
        while (p != m_Rear) {
            i++;
            p = p->next;
        }
        len = i;
        return Status::HELLA_OK;
    }

    Status LinkQueue::GetHead(ElemType& e)
    {
        if (m_Front == m_Rear)
            return Status::HELLA_INFEASIBLE;
        e = m_Front->next->data;
        return Status::HELLA_OK;
    }

    Status LinkQueue::EnQueue(ElemType e)
    {
        QNode* newNode = HELLA_MALLOC(1, QNode);
        HELLA_ASSERT_MEMORY_MALLOC(newNode);
        newNode->data = e;
        newNode->next = NULL;
        m_Rear->next = newNode;
        m_Rear = newNode;
        return Status::HELLA_OK;
    }

    Status LinkQueue::DeQueue(ElemType& e)
    {
        if(m_Front == m_Rear)
            return Status::HELLA_INFEASIBLE;

        QNode* p = m_Front->next;
        e = p->data;
        m_Front->next = p->next;
        if (m_Rear == p)
            m_Rear = m_Front;
        
        HELLA_FREE(p);
        return Status::HELLA_OK;
    }

    Status LinkQueue::Traverse(void(*visit)(ElemType& e))
    {
        QNode* p = m_Front;
        while (p->next) {
            p = p->next;
            visit(p->data);
        }
        return Status::HELLA_OK;

    }

}