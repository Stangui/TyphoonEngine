#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include <vector>
#include <algorithm>
#include <chrono>

#include "Typhoon/Log.h"
#include "glm/glm.hpp"

struct ScopedTimer
{
	std::chrono::time_point<std::chrono::steady_clock> m_start, m_end;
	std::string m_title;

	ScopedTimer( const std::string& title ) :
		 m_title( title )
		,m_start( std::chrono::steady_clock::now() )
		,m_end( std::chrono::steady_clock::now() )
	{
	}

	~ScopedTimer()
	{
		m_end = std::chrono::steady_clock::now();
		TE_ENGINE_LOG_INFO( "ScopedTimer({0}) = {1}ms", m_title, std::chrono::duration_cast<std::chrono::milliseconds>( m_end - m_start ).count());
	}
};

#define TE_DELETE(x) if ( x ) { delete x; x = nullptr; }

#define SCOPED_TIMER(x) ScopedTimer x(#x)

#ifdef TE_PLATFORM_WINDOWS

#include <windows>

#endif	//TE_PLATFORM_WINDOWS
