#pragma once
#include "TestConfig.h"


/*
	@author:Haruluya.
	@function:�����ݽṹ�ĸ���ʵ�ֵĲ����ࡣ
*/
namespace HellaTS {

	//������ӿڡ�
	class ImpTestFun
	{
	public:
		ImpTestFun() {};
		~ImpTestFun() {};
		virtual void TestImpFunction() = 0;
	};

}



