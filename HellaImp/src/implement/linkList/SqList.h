#pragma once
#include "LinkList.h"

/*
	@author:Haruluya.
	@function:The implement of sequence table.
*/

#define HELLA_LIST_INIT_SIZE 50
#define HELLA_LIST_INCREMENT 50

//顺序表定义。
namespace Hella {
	class SqList : public LinkList
	{
	public:
		SqList() {};
		~SqList() {};

	public:
		// 通过 LinkList 继承
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
		int m_Length;
		int m_ListSize{};
		ElemType* m_Elem{};


	};

}

