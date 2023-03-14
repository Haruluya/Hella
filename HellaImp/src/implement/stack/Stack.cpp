#include "hlpch.h"
#include "Stack.h"

std::string Hella::Stack::DataToString()
{
	std::string data = "[ ";
	ElemType e; int len = 0;
	std::vector<ElemType> tempValueVector;
	Length(len);
	for (int i = 1; i <= len; i++) {
		Pop(e);
		data += std::to_string(e) + ",";
		tempValueVector.push_back(e);
	}
	for (int j = 1; j <= len; j++) {
		Push(tempValueVector[len - j]);
	}
	data += " ]";
	return data;
}
