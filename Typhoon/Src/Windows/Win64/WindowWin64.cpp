#include "TyphoonPCH.h"

#include "WindowWin64.h"
#include "Events/ApplicationEvent.h"

namespace TyphoonEngine
{

	bool WindowWin64::s_glfwInitialised = false;

	//------------------------------------------//
	WindowWin64::WindowWin64( const WindowProperties& props ) : m_glWindow( nullptr )
	{
		init( props );
	}

	//------------------------------------------//
	WindowWin64::~WindowWin64()
	{
		shutdown();
	}

	//------------------------------------------//
	bool WindowWin64::Update()
	{
		if ( s_glfwInitialised )
		{
			glfwPollEvents();
			glfwSwapBuffers( m_glWindow );
		}
		return true;
	}

	//------------------------------------------//
	const Vec2i WindowWin64::GetWindowSize() const
	{
		return m_windowData.m_dims;
	}

	//------------------------------------------//
	bool WindowWin64::IsVSync() const
	{
		return m_windowData.m_vSync;
	}

	//------------------------------------------//
	void WindowWin64::SetVSync(bool bEnable)
	{
		m_windowData.m_vSync = bEnable;
		if ( s_glfwInitialised )
		{
			if ( m_windowData.m_vSync )
			{
				glfwSwapInterval( 1 );
			}
			else
			{
				glfwSwapInterval( 0 );
			}
		}
	}

	//------------------------------------------//
	bool WindowWin64::init( const WindowProperties& props )
	{
		m_windowData.m_dims = props.m_dimensions;

		if ( !s_glfwInitialised )
		{
			bool success = glfwInit();
			TE_ASSERT(success)
			s_glfwInitialised = true;
		}

		TE_ENGINE_LOG_INFO( "Window dimensions: {0} x {1}", m_windowData.m_dims.x, m_windowData.m_dims.y );

		// Create window
		m_glWindow = glfwCreateWindow( (int)m_windowData.m_dims.x, (int)m_windowData.m_dims.y, props.m_title.c_str(), nullptr, nullptr );
		glfwMakeContextCurrent( m_glWindow );
		glfwSetWindowUserPointer( m_glWindow, &m_windowData );
		SetVSync( m_windowData.m_vSync );
		
		// Set callbacks
		glfwSetWindowCloseCallback( m_glWindow, []( GLFWwindow* win )
		{
			WindowData* data = static_cast<WindowData*>( glfwGetWindowUserPointer( win ) );
			if ( data )
			{
				WindowCloseEvent Evt;
				data->m_callback( Evt );
			}
		});

		glfwSetWindowFocusCallback( m_glWindow, []( GLFWwindow* win, int focused )
		{
			WindowData* data = static_cast<WindowData*>( glfwGetWindowUserPointer( win ) );
			if ( data )
			{
				WindowFocusEvent Evt(focused);
				data->m_callback( Evt );
			}

		} );

		return true;
	}

	//------------------------------------------//
	void WindowWin64::SetEventCallback( const EventCallbackFn& callback )
	{
		m_windowData.m_callback = callback;
	}

	//------------------------------------------//
	void WindowWin64::shutdown()
	{
		if ( s_glfwInitialised )
		{
			glfwDestroyWindow( m_glWindow );
		}
	}

	//------------------------------------------//
	//------------------------------------------//
	IWindow* IWindow::Create( const WindowProperties& props )
	{
		return new WindowWin64( props );
	}
	//------------------------------------------//
	//------------------------------------------//

}