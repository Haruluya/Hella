#pragma once 
#include "Hella.h"

/*
	@author:Haruluya.
	@function:≤‚ ‘≈‰÷√°£
*/

//¥¥Ω®test°£
#define CREATE_TEST( test_class ) \
         std::unique_ptr<test_class>(new test_class()); 
#define CREATE_TEST_IMP(test_imp_class) CREATE_TEST(test_imp_class);

//________________________________________________________________________
//current test options.													  |
#define CURRENT_TEST HellaTS::ListLinkTestFun							//|
#define CURRENT_TEST_IMP Hella::SinglyLinkedList						//|
//________________________________________________________________________|



//get name of current test.
#define CURRENT_TEST_NAME (std::string(typeid(CURRENT_TEST).name()).substr(15,-1) + '&'+ \
	std::string(typeid(CURRENT_TEST_IMP).name()).substr(13,-1))