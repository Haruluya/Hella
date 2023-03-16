#include "hlpch.h"
#include "BiTree.h"

std::string Hella::BiTree::DataToString()
{
	std::string data = "[ ";
	int len, e;
	Length(len);
	for (int i = 0; i < len; i++) {
		GetElemByIndex(i,e);
		data += std::to_string(e) + ",";
	}
	data += " ]";
	return data;
}
