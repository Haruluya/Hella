#pragma once
#include "TestConfig.h"



/*
	@author:Haruluya.
	@function:各数据结构的各种实现的测试类。
*/
namespace HellaTS {

	//测试类接口。
	class ImpTestFun
	{
	public:
		ImpTestFun() {};
		~ImpTestFun() {};
		virtual void TestImpFunction() = 0;
	};

}



namespace HellaTS {


	/*
		链表测试类。
	*/
	class ListLinkTestFun : public ImpTestFun
	{
	public:
		virtual void TestImpFunction() override;
	};


}