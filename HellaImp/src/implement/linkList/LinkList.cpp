#include "hlpch.h"
#include "LinkList.h"

std::string Hella::LinkList::DataToString()
{
	std::string data = "[ ";
	ElemType e; int len = 0;
	Length(len);
	for (int i = 1; i <= len; i++) {
		GetElem(i, e);
		data += std::to_string(e) + ",";
	}
	data += " ]";
	return data;
}
