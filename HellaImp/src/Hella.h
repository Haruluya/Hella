#pragma once

#include"base/Log.h"


#include"DataStruct.h"
#include"base/HellaException.h"
#include"base/utils.h"

#include"implement/linkList/SqList.h"
#include"implement/linkList/SinglyLinkedList.h"

#include"implement/stack/SqStack.h"

#include"implement/queue/LinkQueue.h"

namespace Hella {
	void InitCore();
	void ShutdownCore();
}