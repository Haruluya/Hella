#pragma once


#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

/*
	@author:Haruluya.
	@function:log stystem of hella.
*/
namespace Hella {

	class Log
	{
	public:
		static void Init();
		static void Shutdown();
		inline static std::shared_ptr<spdlog::logger>& GetHellaLogger() { return s_HellaLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetHellaClinentLogger() { return s_HellaClientLogger; }
	public:
		static std::shared_ptr<spdlog::logger> s_HellaLogger;
		static std::shared_ptr<spdlog::logger> s_HellaClientLogger;
	};
}



// Core log macros
#define HELLA_CORE_TRACE(...)    ::Hella::Log::GetHellaLogger()->trace(__VA_ARGS__)
#define HELLA_CORE_INFO(...)     ::Hella::Log::GetHellaLogger()->info(__VA_ARGS__)
#define HELLA_CORE_WARN(...)     ::Hella::Log::GetHellaLogger()->warn(__VA_ARGS__)
#define HELLA_CORE_ERROR(...)    ::Hella::Log::GetHellaLogger()->error(__VA_ARGS__)
#define HELLA_CORE_FATAL(...)    ::Hella::Log::GetHellaLogger()->fatal(__VA_ARGS__)



// Client log macros
#define HELLA_CLIENT_TRACE(...)	      ::Hella::Log::GetHellaClinentLogger()->trace(__VA_ARGS__)
#define HELLA_CLIENT_INFO(...)	      ::Hella::Log::GetHellaClinentLogger()->info(__VA_ARGS__)
#define HELLA_CLIENT_WARN(...)	      ::Hella::Log::GetHellaClinentLogger()->warn(__VA_ARGS__)
#define HELLA_CLIENT_ERROR(...)	      ::Hella::Log::GetHellaClinentLogger()->error(__VA_ARGS__)
#define HELLA_CLIENT_FATAL(...)	      ::Hella::Log::GetHellaClinentLogger()->fatal(__VA_ARGS__)