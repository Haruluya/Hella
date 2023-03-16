#pragma once 
#include "Hella.h"


/*
	@author:Haruluya.
	@function:测试配置。
*/

//创建test。
#define CREATE_TEST( test_class ) \
         std::unique_ptr<test_class>(new test_class()); 
#define CREATE_TEST_IMP(test_imp_class) CREATE_TEST(test_imp_class);



/*
	@设置当前测试数据结构和各数据结构默认实现。
*/
//________________________________________________________________________
//current test.															  |
#define CURRENT_TEST HellaTS::BiTreeTestFun							    //|
//________________________________________________________________________|

//________________________________________________________________________
//configuration of each test.											  |
#define CURRENT_TEST_LINK_LIST_IMP Hella::SqList
#define CURRENT_TEST_STACK_IMP Hella::SqStack
#define CURRENT_TEST_QUEUE_IMP Hella::LinkQueue
#define CURRENT_TEST_BI_TREE_IMP Hella::SqBiTree
//________________________________________________________________________|


//get name of current test.
#define CURRENT_TEST_NAME (std::string(typeid(CURRENT_TEST).name()).substr(15,-1) + '&') //+ \
	//std::string(typeid(CURRENT_TEST_IMP).name()).substr(13,-1))

