#include "TyphoonPCH.h"
#include "Application.h"

#include "KeyCodes.h"
#include "Input.h"
#include "Windows/IWindow.h"

namespace TyphoonEngine
{

	Application* Application::s_instance = nullptr;

	//----------------------------------------------//
	Application::Application() : 
		 m_bRunning(true)
		,m_bFocused(true)
	{
		WindowProperties wp;
		wp.m_bVSync = true;
		wp.m_monitorId = 1;
		wp.m_title = "Title";
		wp.m_type = WINDOW_TYPE::BorderWindowed;
		wp.m_dimensions = Vec2i( 1280, 720 );
		m_window = std::unique_ptr<IWindow>( IWindow::Create(wp) );
		m_window->SetEventCallback( BIND_CB_FUNC( &Application::OnEvent ) );

		s_instance = this;
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

		if ( IInput::isKeyPressed( TE_KEY_1 ) )
		{
			m_bRunning = false;
			return;
		}
		
		EventDispatch dispatch( Evt );
		dispatch.Dispatch<WindowCloseEvent>( BIND_CB_FUNC( &Application::OnWindowClose ) );
		dispatch.Dispatch<KeyPressedEvent>( BIND_CB_FUNC( &Application::OnKeyPressed ) );
	}

	//----------------------------------------------//
	bool Application::OnWindowClose( WindowCloseEvent& Evt )
	{
		m_bRunning = false;
		return true;
	}

	//----------------------------------------------//
	bool Application::OnKeyPressed( KeyPressedEvent& Evt )
	{
		if ( Evt.getKeyCode() == TE_KEY_ESCAPE )
		{
			m_bRunning = false;
		}
		return true;
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