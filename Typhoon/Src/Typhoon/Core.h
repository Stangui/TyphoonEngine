#pragma once

#include "Log.h"

//
// Provides scoped timing and logs via the default log system
//
struct ScopedTimer
{
	std::chrono::time_point<std::chrono::steady_clock> m_start, m_end;
	std::string m_title;

	ScopedTimer( const std::string& title ) :
		m_title( title )
		, m_start( std::chrono::steady_clock::now() )
		, m_end( std::chrono::steady_clock::now() )
	{
	}

	~ScopedTimer()
	{
		m_end = std::chrono::steady_clock::now();
		TE_ENGINE_LOG_INFO( "ScopedTimer({0}) = {1}ms", m_title, std::chrono::duration_cast<std::chrono::milliseconds>( m_end - m_start ).count() );
	}
};

//------------------- MACROS ----------------------//

// Safe delete of raw pointers
#define TE_DELETE(x) if ( x ) { delete x; x = nullptr; }
// Scoped timing
#define SCOPED_TIMER(x) ScopedTimer x(#x)

// Flags
#define BIT(x) (1 << x)

// Asserts
#ifdef TE_ASSERTS
	#define TE_ASSERT( x, ... ) { if ( (!x) ) { TE_ERROR( "Assertion Failed {0}", __VA_ARGS__ ); __debugbreak(); } }
	#define TE_VERIFY( x, ... ) { if ( (!x) ) { TE_ERROR( "Assertion Failed {0}", __VA_ARGS__ ); __debugbreak(); } }
#else
	#define TE_ASSERT( x, ... ) 
	#define TE_VERIFY( x, ... ) x 
#endif	//TE_ENABLE_ASSERTS

// Callbacks
#define BIND_CB_FUNC(x) std::bind(x, this, std::placeholders::_1)

//------------------- MACROS ----------------------//
