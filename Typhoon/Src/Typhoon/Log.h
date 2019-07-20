#pragma once

#include "spdlog/spdlog.h"
#include "glm/fwd.hpp"

namespace TyphoonEngine
{
	/// 
	///  Default logger
	/// 
	class Log
	{

	public:

		///  Create loggers and set format
		static void Init( glm::int32 logLevel = 0, const std::string& logFormat = "%^[%T] %n: %v%$" );

		///  Engine and client loggers
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_clientLogger; }

	private:

		///  Loggers
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;

	};
}

///  MACROS
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

#define TE_ENGINE_LOG_ERROR(...)   ::TyphoonEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TE_ENGINE_LOG_WARNING(...) ::TyphoonEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TE_ENGINE_LOG_INFO(...)    ::TyphoonEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TE_ENGINE_LOG_TRACE(...)   ::TyphoonEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TE_ENGINE_LOG_FATAL(...)   ::TyphoonEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define TE_ERROR(...)   ::TyphoonEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define TE_WARNING(...) ::TyphoonEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TE_INFO(...)    ::TyphoonEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define TE_TRACE(...)   ::TyphoonEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TE_FATAL(...)   ::TyphoonEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)

#endif

