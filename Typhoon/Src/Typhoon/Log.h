#pragma once

#include <memory>

#include "spdlog/spdlog.h"

namespace TyphooEngine
{
	class Log
	{

	public:

		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_clientLogger; }

	private:

		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;

	};
}


#ifdef TE_BUILD_SHIPPING

#define TE_LOG_ERROR
#define TE_LOG_WARNING
#define TE_LOG_INFO
#define TE_LOG_TRACE
#define TE_LOG_FATAL

#else

#define TE_LOG_ERROR(...)   ::TyphooEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TE_LOG_WARNING(...) ::TyphooEngine::Log::GetCoreLogger()->warning(__VA_ARGS__)
#define TE_LOG_INFO(...)    ::TyphooEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TE_LOG_TRACE(...)   ::TyphooEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TE_LOG_FATAL(...)   ::TyphooEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#endif

