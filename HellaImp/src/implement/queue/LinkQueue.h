#pragma once

#include "Queue.h"

typedef struct QNode {
	Hella::ElemType data;
	QNode* next;
}QNode;

namespace Hella {
	class  LinkQueue : public Queue {
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
		QNode* m_Front;
		QNode* m_Rear;
	};
}