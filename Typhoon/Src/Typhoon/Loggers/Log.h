#pragma once

#include "Typhoon/Core.h"
#include "spdlog/spdlog.h"

namespace TyphooEngine
{
	// Default logger
	class Log
	{

	public:

		// Create loggers and set format
		static void Init( int32 logLevel, const std::string& logFormat = "%^[%T] %n: %v%$" );

		// Getters
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_clientLogger; }

	private:

		// Loggers
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;

	};
}

// MACROS
#ifdef TE_BUILD_SHIPPING

#define TE_ENGINE_LOG_ERROR
#define TE_ENGINE_LOG_WARNING
#define TE_ENGINE_LOG_INFO
#define TE_ENGINE_LOG_TRACE
#define TE_ENGINE_LOG_FATAL

#define TE_ERROR
#define TE_WARNING
#define TE_INFO
#define TE_TRACE
#define TE_FATAL

#else

#define TE_ENGINE_LOG_ERROR(...)   ::TyphooEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TE_ENGINE_LOG_WARNING(...) ::TyphooEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TE_ENGINE_LOG_INFO(...)    ::TyphooEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TE_ENGINE_LOG_TRACE(...)   ::TyphooEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TE_ENGINE_LOG_FATAL(...)   ::TyphooEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define TE_ERROR(...)   ::TyphooEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define TE_WARNING(...) ::TyphooEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TE_INFO(...)    ::TyphooEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define TE_TRACE(...)   ::TyphooEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TE_FATAL(...)   ::TyphooEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)

#endif

