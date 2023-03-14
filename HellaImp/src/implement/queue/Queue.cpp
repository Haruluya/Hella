#include "hlpch.h"
#include "Queue.h"

std::string Hella::Queue::DataToString()
{
	std::string data = "[ ";
	ElemType e; int len = 0;
	std::vector<ElemType> tempValueVector;
	Length(len);
	for (int i = 1; i <= len; i++) {
		DeQueue(e);
		data += std::to_string(e) + ",";
		tempValueVector.push_back(e);
	}
	for (int j = 1; j <= len; j++) {
		EnQueue(tempValueVector[j-1]);
	}
	data += " ]";
	return data;
}
