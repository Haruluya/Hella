#pragma once

#include "TestConfig.h"

#include "tests/ListLinkTestFun.h"
#include "tests/StackTestFun.h"
#include "tests/QueueTestFun.h"
#include "tests/BiTreeTestFun.h"


/*
	@author:Haruluya
	@function:²âÊÔÈë¿Ú¡£
*/
int main(int argc, char** argv)
{
	//init hella.
	Hella::InitCore();

	//test begin.
	HELLA_CLIENT_WARN("{}",
		Hella::Util::LetStrConsoleCenter("HELLA "+ CURRENT_TEST_NAME +" TEST BEGIN",'-')
	);

	try
	{
		//create and testing.
		auto test = CREATE_TEST(CURRENT_TEST);
		test->TestImpFunction();
	}
	catch (Hella::HellaException& e)
	{
		//if error.
		HELLA_CLIENT_ERROR("TEST ERROR: {}",e.ToString());
	}

	//test end.
	HELLA_CLIENT_WARN("{}",
		Hella::Util::LetStrConsoleCenter("HELLA " + CURRENT_TEST_NAME + " TEST END",'-')
	);

	Hella::ShutdownCore();

	return 0;
}

