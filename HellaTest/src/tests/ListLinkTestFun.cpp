#include"ListLinkTestFun.h"


namespace HellaTS {
	void ListLinkTestFun::TestImpFunction()
	{
		auto linklist = CREATE_TEST_IMP(CURRENT_TEST_LINK_LIST_IMP);

		//Init and insert.
		// 初始化为[1,...99].
		HELLA_STATUS_JUDGE(linklist->Init());
		for (int i = 1; i < 100; i++) {
			HELLA_STATUS_JUDGE(linklist->Insert(i, i));
		}
		HELLA_CLIENT_INFO("INIT LINKLIST:\n{}\n", linklist->DataToString());


		//locate , pre and next.
		//list中找到toFindEl并找前驱后驱。
		ElemType toFindEl = 3;

		ElemType cur, pre, next;
		int index;
		HELLA_STATUS_JUDGE(linklist->LocateElem(toFindEl,
			[](ElemType e1, ElemType e2) {return e1 == e2; },
			index));
		HELLA_STATUS_JUDGE(linklist->GetElem(index, cur));
		HELLA_STATUS_JUDGE(linklist->PriorElem(cur, pre));
		HELLA_STATUS_JUDGE(linklist->NextElem(cur, next));
		HELLA_CLIENT_INFO("L&P&N:\nCurrend element:{0}\nprior element: {1} \nnest element: {2} \n",
			cur, pre, next);


		//Traverse and delete.
		//删除前49项，然后全部乘2.
		ElemType e;
		std::vector<ElemType> ev;
		std::string deleteElStr;


		for (int j = 1; j < 50; j++) {
			HELLA_STATUS_JUDGE(linklist->Delete(1, e));
			ev.push_back(e);
		}

		deleteElStr += "[ ";
		std::for_each(ev.begin(), ev.end(),
			[&deleteElStr](ElemType e) {deleteElStr += std::to_string(e) + ","; }
		);
		deleteElStr += " ]";

		HELLA_STATUS_JUDGE(linklist->Traverse([](ElemType& e) {e *= 2; }));

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