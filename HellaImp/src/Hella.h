#pragma once

#include"base/Log.h"


#include"DataStruct.h"
#include"base/HellaException.h"
#include"base/utils.h"

//LinkList.
#include"implement/linkList/SqList.h"
#include"implement/linkList/SinglyLinkedList.h"

//Stack.
#include"implement/stack/SqStack.h"

//Queue.
#include"implement/queue/LinkQueue.h"

//String.

//Tree.
#include "implement/tree/SqBiTree.h"

//Graph.


namespace Hella {
	void InitCore();
	void ShutdownCore();
}