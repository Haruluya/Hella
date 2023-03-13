#pragma once
#include<string>
/*
	@author:Haruluya.
	@function:abstraction of datastruct.
*/
namespace Hella {
	class DataStruct
	{
	public:
		DataStruct() {};
		~DataStruct() {};
		virtual std::string DataToString() = 0;
	};

}