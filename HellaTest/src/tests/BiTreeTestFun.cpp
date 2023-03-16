#include "BiTreeTestFun.h"

namespace HellaTS {
	void BiTreeTestFun::TestImpFunction()
	{
		auto bitTree = CREATE_TEST_IMP(CURRENT_TEST_BI_TREE_IMP);

		//init and create.
		HELLA_STATUS_JUDGE(bitTree->Init());

		Hella::ElemType* e = new int[14]{1,2,3,4,5,6,-2,7,-2,8,9,-2,10,-1};
		HELLA_STATUS_JUDGE(bitTree->CreateByLev(e, -2));

		HELLA_CLIENT_INFO("Create tree:\n{}\n",
			bitTree->DataToString());

		//Depth and length.
		int depth, len,root;
		bitTree->Depth(depth);
		bitTree->Length(len);
		bitTree->Root(root);
		HELLA_CLIENT_INFO("Depth:\n{}\nLength:\n{}\nRoot:\n{}\n",
			depth,len,root);

		//Value and assign.
		int preValue,aftValue;
		bitTree->Value({ 4,3 }, preValue);
		bitTree->Assign({ 4,3 }, 99);
		bitTree->Value({ 4,3 }, aftValue);
		HELLA_CLIENT_INFO("preValue:\n{}\naftValue:\n{}\n",
			preValue, aftValue);

		//Parent, children and silibing.
		int parent,lchi,rchi, lsi, rsi;
		bitTree->Parent(5, parent);
		bitTree->LeftChild(5, lchi);
		bitTree->RightChild(5, rchi);
		bitTree->LeftSibling(5, lsi);
		HELLA_STATUS_JUDGE(bitTree->RightSibling(4, rsi));
		HELLA_CLIENT_INFO("Parent:\n{}\nLeftChild:\n{}\nRightChild:\n{}\nLeftSibling:\n{}\nRightSibling:\n{}\n",
			parent, lchi,rchi,lsi,rsi);


		//Traverse.
		auto visit = [](Hella::ElemType& e) { e *= 2; };
		bitTree->LevelOrderTraverse(visit);
		HELLA_CLIENT_INFO("After LevelOrderTraverse:\n{}\n",
			bitTree->DataToString());

		bitTree->PreOrderTraverse(visit);
		HELLA_CLIENT_INFO("After PreOrderTraverse:\n{}\n",
			bitTree->DataToString());

		bitTree->InOrderTraverse(visit);
		HELLA_CLIENT_INFO("After InOrderTraverse:\n{}\n",
			bitTree->DataToString());

		bitTree->PostOrderTraverse(visit);
		HELLA_CLIENT_INFO("After PostOrderTraverse:\n{}\n",
			bitTree->DataToString());

	}
}