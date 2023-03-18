#include "QueueTestFun.h"

namespace HellaTS {
	void QueueTestFun::TestImpFunction()
	{
		auto queue = CREATE_TEST_IMP(CURRENT_TEST_QUEUE_IMP);

		//init and push.
		HELLA_STATUS_JUDGE(queue->Init());
		for (int i = 1; i < 100; i++) {
			HELLA_STATUS_JUDGE(queue->EnQueue(i));
		}
		int len; ElemType top;
		queue->Length(len);
		queue->GetHead(top);
		HELLA_CLIENT_INFO("INIT QUEUE:\n{}\nLENGTH:{}\HEAD:{}",
			queue->DataToString(), len, top);

		////Dequeue.
		ElemType dequeueValue;
		std::vector<ElemType> dequeueValueVector;
		std::string deleteElStr;
		for (int j = 1; j < 50; j++) {
			HELLA_STATUS_JUDGE(queue->DeQueue(dequeueValue));
			dequeueValueVector.push_back(dequeueValue);
		}

		deleteElStr += "[ ";
		std::for_each(dequeueValueVector.begin(), dequeueValueVector.end(),
			[&deleteElStr](ElemType e) {deleteElStr += std::to_string(e) + ","; }
		);
		deleteElStr += " ]";

		HELLA_CLIENT_INFO("T&D:\ndequeue data: {0}\nAfter dequeue: {1}\n",
			deleteElStr, queue->DataToString());


		//Traverse.
		HELLA_STATUS_JUDGE(queue->Traverse([](ElemType& e) {e *= 2; }));
		HELLA_CLIENT_INFO("T&D:\nAfter traverse: {0}\n",
			queue->DataToString());


		//clear and destory.
		HELLA_STATUS_JUDGE(queue->Clear());
		HELLA_STATUS_JUDGE(queue->Length(len));
		HELLA_CLIENT_INFO("C&D:\nIs queue Empty ?:{0} \nLength: {1} \n",
			(queue->IsEmpty() == Hella::Status::HELLA_TRUE), len);
		HELLA_STATUS_JUDGE(queue->Destory());
	}

}
