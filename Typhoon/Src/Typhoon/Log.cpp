#include "TyphoonPCH.h"

#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace TyphoonEngine
{

	std::shared_ptr<spdlog::logger> Log::s_coreLogger;
	std::shared_ptr<spdlog::logger> Log::s_clientLogger;

	void Log::Init( glm::int32 logLevel, const std::string& logFormat )
	{
		// Set output format
		spdlog::set_pattern( logFormat );

		// Create loggers
		s_coreLogger = spdlog::stderr_color_mt( "EngineLog" );
		s_coreLogger->set_level( static_cast<spdlog::level::level_enum>( logLevel ) );

		s_clientLogger = spdlog::stdout_color_mt( "AppLog" );
		s_clientLogger->set_level( static_cast<spdlog::level::level_enum>( logLevel ) );
	}

}
