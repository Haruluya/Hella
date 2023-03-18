#include "BiTreeTestFun.h"

namespace HellaTS {
	void BiTreeTestFun::TestImpFunction()
	{
		auto biTree = CREATE_TEST_IMP(CURRENT_TEST_BI_TREE_IMP);

		//init and create.
		HELLA_STATUS_JUDGE(biTree->Init());

		/*
		@:ÏÈÐòÐòÁÐ¡£
						1
					2		8
				  3   5   9	  -1	
				4 -1 6 7-1 10 -1 -1
		*/
		ElemType* e = new int[21]{1,2,3,4,-2,-2,-2,5,6,-2,-2,7,-2,-2,8,9,-2,10,-2,-2,-2};
		HELLA_STATUS_JUDGE(biTree->Create(e, -2));
		HELLA_CLIENT_INFO("Create tree:\n{}\n",
			biTree->DataToString());


		//Depth and length.
		int depth, len,root;
		HELLA_STATUS_JUDGE(biTree->Depth(depth));
		HELLA_STATUS_JUDGE(biTree->Length(len));
		HELLA_STATUS_JUDGE(biTree->Root(root));
		HELLA_CLIENT_INFO("Depth:\n{}\nLength:\n{}\nRoot:\n{}\n",
			depth,len,root);

		//Value and assign.
		int preValue = 0,aftValue = 0;
		HELLA_STATUS_JUDGE(biTree->Value({ 4,3 }, preValue));
		HELLA_STATUS_JUDGE(biTree->Assign({ 4,3 }, 99));
		HELLA_STATUS_JUDGE(biTree->Value({ 4,3 }, aftValue));
		HELLA_CLIENT_INFO("preValue:\n{}\naftValue:\n{}\n",
			preValue, aftValue);

		//Parent, children and silibing.
		int parent,lchi,rchi, lsi, rsi;
		HELLA_STATUS_JUDGE(biTree->Parent(5, parent));
		HELLA_STATUS_JUDGE(biTree->LeftChild(5, lchi));
		HELLA_STATUS_JUDGE(biTree->RightChild(5, rchi));
		HELLA_STATUS_JUDGE(biTree->LeftSibling(5, lsi));
		HELLA_STATUS_JUDGE(biTree->RightSibling(3, rsi));
		HELLA_CLIENT_INFO("Parent:\n{}\nLeftChild:\n{}\nRightChild:\n{}\nLeftSibling:\n{}\nRightSibling:\n{}\n",
			parent, lchi,rchi,lsi,rsi);


		//Traverse.
		auto visit = [](ElemType& e) { e *= 2; };
		HELLA_STATUS_JUDGE(biTree->LevelOrderTraverse(visit));
		HELLA_CLIENT_INFO("After LevelOrderTraverse:\n{}\n",
			biTree->DataToString());

		HELLA_STATUS_JUDGE(biTree->PreOrderTraverse(visit));
		HELLA_CLIENT_INFO("After PreOrderTraverse:\n{}\n",
			biTree->DataToString());

		HELLA_STATUS_JUDGE(biTree->InOrderTraverse(visit));
		HELLA_CLIENT_INFO("After InOrderTraverse:\n{}\n",
			biTree->DataToString());

		HELLA_STATUS_JUDGE(biTree->PostOrderTraverse(visit));
		HELLA_CLIENT_INFO("After PostOrderTraverse:\n{}\n",
			biTree->DataToString());


		//Destory.
		HELLA_STATUS_JUDGE(biTree->Clear());
		HELLA_STATUS_JUDGE(biTree->Length(len));
		HELLA_CLIENT_INFO("After clear:\n{}\nLength:{}\nIsEmpty:\n{}\n",
			biTree->DataToString(), len, biTree->IsEmpty() == Hella::Status::HELLA_TRUE);
		HELLA_STATUS_JUDGE(biTree->Destroy());


	}
}