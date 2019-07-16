#include "TyphoonPCH.h"

#include "WindowWin64.h"
#include "Typhoon/Events/ApplicationEvent.h"
#include "Typhoon/Events/KeyboardEvent.h"
#include "Typhoon/Events/MouseEvent.h"

#include "glad/glad.h"

namespace TyphoonEngine
{
	using namespace glm;

	bool WindowWin64::s_glfwInitialised = false;

	//------------------------------------------//
	static void GLFWErrorCallback( int32 error, const char* msg )
	{
		TE_ENGINE_LOG_ERROR( "GLFWError: {0} - {1}", error, msg );
	}

	//------------------------------------------//
	WindowWin64::WindowWin64( const WindowProperties& props ) : m_glWindow( nullptr )
	{
		_init( props );
	}

	//------------------------------------------//
	WindowWin64::~WindowWin64()
	{
		_shutdown();
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
	const ivec2 WindowWin64::GetWindowSize() const
	{
		return m_windowData.m_dims;
	}

	//------------------------------------------//
	void* WindowWin64::GetNativeWindow() const
	{
		return m_glWindow;
	}

	//------------------------------------------//
	bool WindowWin64::IsVSync() const
	{
		return m_windowData.m_bVSync;
	}

	//------------------------------------------//
	void WindowWin64::SetVSync(bool bEnable)
	{
		m_windowData.m_bVSync = bEnable;
		if ( s_glfwInitialised )
		{
			if ( m_windowData.m_bVSync )
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
	ivec2 WindowWin64::_calculateWindowPos( GLFWmonitor* monitor, int sizeX, int sizeY )
	{
		ivec2 pos(0, 0);
		if ( monitor )
		{
			int x, y, width, height;
			glfwGetMonitorPos( monitor, &x, &y );
			glfwGetMonitorWorkarea( monitor, &x, &y, &width, &height );

			if ( width < sizeX ) { width = sizeX; }
			if ( height  < sizeY ) { height = sizeY; }

			pos.x = x + static_cast<int32>( ( width - sizeX ) * 0.5f );
			pos.y = y + static_cast<int32>( ( height - sizeY ) * 0.5f );
		}
		return pos;
	}

	//------------------------------------------//
	void WindowWin64::_setCallbacks(GLFWwindow* win)
	{
		glfwSetWindowCloseCallback( m_glWindow, []( GLFWwindow* win )
		{
			WindowData* data = static_cast<WindowData*>( glfwGetWindowUserPointer( win ) );
			if ( data )
			{
				WindowCloseEvent Evt;
				data->m_callback( Evt );
			}
		} );
		glfwSetWindowSizeCallback( m_glWindow, [](GLFWwindow* win, int32 width, int32 height)
		{
			WindowData* data = static_cast<WindowData*>( glfwGetWindowUserPointer( win ) );
			if ( data )
			{
				WindowResizeEvent Evt( width, height );
				data->m_callback( Evt );
			}
		} );
		glfwSetWindowFocusCallback( m_glWindow, []( GLFWwindow* win, int focused )
		{
			WindowData* data = static_cast<WindowData*>( glfwGetWindowUserPointer( win ) );
			if ( data )
			{
				WindowFocusEvent Evt( focused );
				data->m_callback( Evt );
			}

		} );
		glfwSetKeyCallback( m_glWindow, []( GLFWwindow* win, int32 key, int32 scancode, int32 action, int32 mod )
		{
			WindowData* data = static_cast<WindowData*>( glfwGetWindowUserPointer( win ) );
			if ( data )
			{
				switch ( action )
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent Evt( key, false );
					data->m_callback( Evt );
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent Evt( key );
					data->m_callback( Evt );
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent Evt( key, true );
					data->m_callback( Evt );
					break;
				}
				}
			}
		} );
		glfwSetMouseButtonCallback( m_glWindow, []( GLFWwindow* win, int32 button, int32 action, int32 mod )
		{
			WindowData* data = static_cast<WindowData*>( glfwGetWindowUserPointer( win ) );
			if ( data )
			{
				switch ( action )
				{
				case GLFW_PRESS:
				{
					MouseButtonPressed Evt( button );
					data->m_callback( Evt );
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleased Evt( button );
					data->m_callback( Evt );
					break;
				}
				}
			}
		} );
		glfwSetScrollCallback( m_glWindow, []( GLFWwindow* win, double offsetX, double offsetY )
		{
			WindowData* data = static_cast<WindowData*>( glfwGetWindowUserPointer( win ) );
			if ( data )
			{
				MouseScroll Evt( static_cast<float>(offsetX), static_cast<float>( (offsetY) ) );
				data->m_callback( Evt );
			}
		} );
		glfwSetCursorPosCallback( m_glWindow, []( GLFWwindow* win, double posX, double posY )
		{
			WindowData* data = static_cast<WindowData*>( glfwGetWindowUserPointer( win ) );
			if ( data )
			{
				MouseMovedEvent Evt( static_cast<float>( posX ), static_cast<float>( posY ) );
				data->m_callback( Evt );
			}
		} );
		glfwSetErrorCallback( GLFWErrorCallback );
	}

	//------------------------------------------//
	bool WindowWin64::_init( const WindowProperties& props )
	{
		m_windowData.m_dims = props.m_dimensions;
		m_windowData.m_monitorId = props.m_monitorId;
		m_windowData.m_bVSync = props.m_bVSync;
		m_windowData.m_type = props.m_type;

		if ( !s_glfwInitialised )
		{
			bool success = glfwInit();
			TE_ASSERT(success, "Error initialising GLFW")
			s_glfwInitialised = true;
		}

		TE_ENGINE_LOG_INFO( "Window dimensions: {0} x {1}", m_windowData.m_dims.x, m_windowData.m_dims.y );

		int count;
		GLFWmonitor** monitors = glfwGetMonitors( &count );
		GLFWmonitor* windowMonitor = glfwGetPrimaryMonitor();
		if ( m_windowData.m_monitorId < count )
		{
			windowMonitor = monitors[m_windowData.m_monitorId];
		}

		// Create window
		switch ( m_windowData.m_type )
		{
			case WINDOW_TYPE::BorderlessWindowed:
			{
				const glm::ivec2 pos = _calculateWindowPos( windowMonitor, m_windowData.m_dims.x, m_windowData.m_dims.y );
				glfwWindowHint( GLFW_DECORATED, GLFW_FALSE );
				m_glWindow = glfwCreateWindow( (int)m_windowData.m_dims.x, (int)m_windowData.m_dims.y, props.m_title.c_str(), nullptr, nullptr );
				glfwSetWindowPos( m_glWindow, pos.x, pos.y );
				break;
			}
			case WINDOW_TYPE::BorderWindowed:
			{
				const glm::ivec2 pos = _calculateWindowPos( windowMonitor, m_windowData.m_dims.x, m_windowData.m_dims.y );
				glfwWindowHint( GLFW_DECORATED, GLFW_TRUE );
				m_glWindow = glfwCreateWindow( (int)m_windowData.m_dims.x, (int)m_windowData.m_dims.y, props.m_title.c_str(), nullptr, nullptr );
				glfwSetWindowPos( m_glWindow, pos.x, pos.y );
				break;
			}
			case WINDOW_TYPE::FullscreenWindowed:
			{
				const GLFWvidmode* mode = glfwGetVideoMode( windowMonitor );
				m_glWindow = glfwCreateWindow( mode->width, mode->height, props.m_title.c_str(), nullptr, nullptr );
				const glm::ivec2 pos = _calculateWindowPos( windowMonitor, mode->width, mode->height );
				glfwSetWindowPos( m_glWindow, pos.x, pos.y );
				break;
			}
			case WINDOW_TYPE::Fullscreen:
			{
				const GLFWvidmode* mode = glfwGetVideoMode( windowMonitor );
				m_glWindow = glfwCreateWindow( mode->width, mode->height, props.m_title.c_str(), windowMonitor, nullptr );
				SetVSync( m_windowData.m_bVSync );
				break;
			}
			default:
			{
				m_glWindow = glfwCreateWindow( 1280, 720, props.m_title.c_str(), nullptr, nullptr );
				break;
			}
		}		
		
		glfwGetWindowSize( m_glWindow, &m_windowData.m_dims.x, &m_windowData.m_dims.y );
		glfwMakeContextCurrent( m_glWindow );
		int status = gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress );
		TE_ASSERT(status, "Failed to initialise GLAD")
		glfwSetWindowUserPointer( m_glWindow, &m_windowData );
		_setCallbacks( m_glWindow );

		return true;
	}

	//------------------------------------------//
	void WindowWin64::SetEventCallback( const EventCallbackFn& callback )
	{
		m_windowData.m_callback = callback;
	}

	//------------------------------------------//
	void WindowWin64::_shutdown()
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