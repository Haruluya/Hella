#pragma once
#include "hlpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/ansicolor_sink.h"

namespace Hella {

	std::shared_ptr<spdlog::logger> Log::s_HellaLogger;
	std::shared_ptr<spdlog::logger> Log::s_HellaClientLogger;
	void Log::Init()
	{
		//// 获取标准输出句柄
		//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		//// 设置控制台字体大小
		//CONSOLE_FONT_INFOEX font = { sizeof(CONSOLE_FONT_INFOEX) };
		//font.dwFontSize.X = 10;
		//font.dwFontSize.Y = 18;
		//SetCurrentConsoleFontEx(hConsole, FALSE, &font);

		spdlog::set_pattern("\033[1;31m[%T] [%n]\033[0m:\n%^%v%$");
		s_HellaLogger = spdlog::stdout_color_mt("Hella");
		s_HellaLogger->set_level(spdlog::level::trace);

		s_HellaClientLogger = spdlog::stdout_color_mt("Client");
		s_HellaClientLogger->set_level(spdlog::level::trace);
	}

	void Log::Shutdown()
	{
		s_HellaLogger.reset();
		s_HellaClientLogger.reset();
		spdlog::drop_all();
	}

}