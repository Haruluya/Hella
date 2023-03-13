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
			columns = 80;  // Ĭ�Ͽ��Ϊ80��
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
	// �����߿�
	output += "\u250C"; // ���Ͻ�
	for (int i = 0; i < len + 2; i++)
	{
		output += "\u2500"; // ˮƽ��
	}
	output += "\u2510\n"; // ���Ͻ�

	// �м䲿��
	output += "\u2502 " + str + " \u2502\n";

	// �ײ��߿�
	output += "\u2514"; // ���½�
	for (int i = 0; i < len + 2; i++)
	{
		output += "\u2500"; // ˮƽ��
	}
	output += "\u2518\n"; // ���½�

	return output;
}
