#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace TyphooEngine
{

	std::shared_ptr<spdlog::logger> Log::s_coreLogger;
	std::shared_ptr<spdlog::logger> Log::s_clientLogger;

	void Log::Init()
	{
		// Set output format
		spdlog::set_pattern( "%^[%T] %n: %v%$" );

		// Create loggers
		s_coreLogger = spdlog::stderr_color_mt( "EngineLog" );
		s_coreLogger->set_level( spdlog::level::trace );

		s_clientLogger = spdlog::stdout_color_mt( "AppLog" );
		s_clientLogger->set_level( spdlog::level::trace );
	}

}
