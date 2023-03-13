#include "ImpTestFun.h"


/*
	@author:Haruluya.
*/
namespace HellaTS {

	//&& sta != Hella::Status::HELLA_TRUE
	void HellaTS::ListLinkTestFun::TestImpFunction()
	{
		auto linklist = CREATE_TEST_IMP(CURRENT_TEST_IMP);

		//Init and insert.
		// 初始化为[1,...99].
		HELLA_STATUS_JUDGE(linklist->Init());
		for (int i = 1; i < 100; i++) {
			HELLA_STATUS_JUDGE(linklist->Insert(i, i));
		}
		HELLA_CLIENT_INFO("INIT LINKLIST:\n{}\n", linklist->DataToString());


		//locate , pre and next.
		//list中找到toFindEl并找前驱后驱。
		Hella::ElemType toFindEl = 3;

		Hella::ElemType cur, pre, next;
		int index;
		HELLA_STATUS_JUDGE(linklist->LocateElem(toFindEl,
			[](Hella::ElemType e1, Hella::ElemType e2) {return e1 == e2; }, 
			index));
		HELLA_STATUS_JUDGE(linklist->GetElem(index, cur));
		HELLA_STATUS_JUDGE(linklist->PriorElem(cur, pre));
		HELLA_STATUS_JUDGE(linklist->NextElem(cur, next));
		HELLA_CLIENT_INFO("L&P&N:\nCurrend element:{0}\nprior element: {1} \nnest element: {2} \n",
			cur,pre,next);


		//Traverse and delete.
		//删除前49项，然后全部乘2.
		Hella::ElemType e;
		std::vector<Hella::ElemType> ev;
		std::string deleteElStr;


		for (int j = 1; j < 50; j++) {
			HELLA_STATUS_JUDGE(linklist->Delete(1, e));
			ev.push_back(e);
		}

		deleteElStr += "[ ";
		std::for_each(ev.begin(), ev.end(),
			[&deleteElStr](Hella::ElemType e) {deleteElStr += std::to_string(e) + ","; }
		);
		deleteElStr += " ]";

		HELLA_STATUS_JUDGE(linklist->Traverse([](Hella::ElemType& e) {e *= 2; }));

		HELLA_CLIENT_INFO("T&D:\nDeleted data: {0} \nAfter visited: {1}\n ", 
				deleteElStr, linklist->DataToString());


		//clear and destory.
		//清空并销毁。
		HELLA_STATUS_JUDGE(linklist->Clear());
		int len;
		HELLA_STATUS_JUDGE(linklist->Length(len));
		HELLA_CLIENT_INFO("C&D:\nIs list Empty ?:{0} \nLength: {1} \n",
			(linklist->IsEmpty() == Hella::Status::HELLA_TRUE), len);
		HELLA_STATUS_JUDGE(linklist->Destroy());

	}


}
