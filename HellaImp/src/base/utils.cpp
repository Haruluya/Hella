#pragma once
#include"hlpch.h"
#include "utils.h"


std::string Hella::Util::GetStatusMsg(Hella::Status sta)
{
	switch (sta)
	{
	case Hella::Status::HELLA_TRUE:
		return "TRUE";
	case Hella::Status::HELLA_FALSE:
		return "FALSE";
	case Hella::Status::HELLA_OK:
		return "OK";
	case Hella::Status::HELLA_ERROR:
		return "ERROR";
	case Hella::Status::HELLA_INFEASIBLE:
		return "INFEASIBLE";
	case Hella::Status::HELLA_OVERFLOW:
		return "OVERFLOW";
	case Hella::Status::HELLA_NOT_FOUND:
		return "NOT_FOUND";
	}
	return "status invalid";
}

std::string Hella::Util::LetStrConsoleCenter(const std::string& text, const char frameChar)
{
	int consoleWidth = []() -> int {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		int columns;
		if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		{
			columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		}
		else
		{
			columns = 80;  // 默认宽度为80列
		}
		return columns;
	}();

	int textWidth = static_cast<int>(text.length());
	int paddingWidth = (consoleWidth - textWidth) / 2;

	std::string padding(paddingWidth, frameChar);
	return padding + text + padding + "\n";
}

std::string Hella::Util::LetStrConsoleInBox(const std::string& str)
{
	std::string output;
	int len = str.length();
	// 顶部边框
	output += "\u250C"; // 左上角
	for (int i = 0; i < len + 2; i++)
	{
		output += "\u2500"; // 水平线
	}
	output += "\u2510\n"; // 右上角

	// 中间部分
	output += "\u2502 " + str + " \u2502\n";

	// 底部边框
	output += "\u2514"; // 左下角
	for (int i = 0; i < len + 2; i++)
	{
		output += "\u2500"; // 水平线
	}
	output += "\u2518\n"; // 右下角

	return output;
}
