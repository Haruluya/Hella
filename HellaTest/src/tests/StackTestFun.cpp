#include"StackTestFun.h"

namespace HellaTS {
	void StackTestFun::TestImpFunction()
	{
		auto stack = CREATE_TEST_IMP(CURRENT_TEST_STACK_IMP);

		//init and push.
		HELLA_STATUS_JUDGE(stack->Init());
		for (int i = 1; i < 100; i++) {
			HELLA_STATUS_JUDGE(stack->Push(i));
		}
		int len; ElemType top;
		stack->Length(len);
		stack->GetTop(top);
		HELLA_CLIENT_INFO("INIT STACK:\n{}\nLENGTH:\n{}\nTOP:\n{}",
			stack->DataToString(), len, top);

		////pop.
		ElemType popValue;
		std::vector<ElemType> popValueVector;
		std::string deleteElStr;
		for (int j = 1; j < 50; j++) {
			HELLA_STATUS_JUDGE(stack->Pop(popValue));
			popValueVector.push_back(popValue);
		}

		deleteElStr += "[ ";
		std::for_each(popValueVector.begin(), popValueVector.end(),
			[&deleteElStr](ElemType e) {deleteElStr += std::to_string(e) + ","; }
		);
		deleteElStr += " ]";

		HELLA_CLIENT_INFO("T&D:\nPop data:\n {0}\nAfter pop:\n {1}\n",
			deleteElStr, stack->DataToString());


		//Traverse.
		HELLA_STATUS_JUDGE(stack->Traverse([](ElemType& e) {e *= 2; }));
		HELLA_CLIENT_INFO("T&D:\nAfter traverse:\n {0}\n",
			stack->DataToString());


		//clear and destory.
		HELLA_STATUS_JUDGE(stack->Clear());
		HELLA_STATUS_JUDGE(stack->Length(len));
		HELLA_CLIENT_INFO("C&D:\nIs stack Empty ?:\n{0} \nLength:\n {1} \n",
			(stack->IsEmpty() == Hella::Status::HELLA_TRUE), len);
		HELLA_STATUS_JUDGE(stack->Destory());

	}
}