#include "TyphoonPCH.h"

#include "Typhoon/Application.h"
#include "Windows/IWindow.h"

namespace TyphoonEngine
{
	//----------------------------------------------//
	Application::Application() : 
		 m_bRunning(true)
		,m_bFocused(true)
	{
		m_window = std::unique_ptr<IWindow>( IWindow::Create() );
		m_window->SetEventCallback(BIND_CB_FUNC(&Application::OnEvent));
	}

	//----------------------------------------------//
	Application::~Application()
	{
		TE_ENGINE_LOG_INFO( "Application closing..." );
	}

	//----------------------------------------------//
	void Application::OnEvent( Event& Evt )
	{
		TE_ENGINE_LOG_INFO( "Application::OnEvent() - {0}", Evt.ToString() );

		switch ( Evt.getEventType() )
		{
		case EventType::WindowClose:
		{
			m_bRunning = false;
			break;
		}
		case EventType::WindowFocus:
		{
			m_bFocused = static_cast<WindowFocusEvent&>(Evt).isFocused();
			break;
		}
		case EventType::WindowMoved:
		{
			break;
		}
		case EventType::WindowResize:
		{
			break;
		}
		default:
			break;
		}
	}

	//----------------------------------------------//
	void Application::Run()
	{
		SCOPED_TIMER( Test );

		while ( m_bRunning )
		{
			m_window->Update();
		}
	}
}