#pragma once
#include<string>
/*
	@author:Haruluya.
	@function:util functions.
*/
namespace Hella
{
	namespace Util {

		std::string GetStatusMsg(Hella::Status sta);
		std::string LetStrConsoleCenter(const std::string& text, const char frameChar=' ');
		std::string LetStrConsoleInBox(const std::string& str);

	}

}