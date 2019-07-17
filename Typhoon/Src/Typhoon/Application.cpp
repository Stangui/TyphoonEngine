#include "TyphoonPCH.h"
#include "Application.h"
#include "Windows/IWindow.h"
#include "Input/Input.h"
#include "Input/KeyCodes.h"
#include "Layers/Layer.h"
#include "UI/ImGuiLayer.h"
#include "glad/glad.h"

namespace TyphoonEngine
{

	Application* Application::s_instance = nullptr;

	//----------------------------------------------//
	Application::Application() :
		m_bRunning( true )
		, m_bFocused( true )
	{
		TE_ASSERT( !s_instance, "Application already exists!" )
		// Singleton
		s_instance = this;

		//TODO:- config this..
		WindowProperties wp;
		wp.m_bVSync = true;
		wp.m_monitorId = 1;
		wp.m_type = EWINDOW_TYPE::BorderWindowed;
		wp.m_dimensions = glm::vec2( 1280, 720 );
		m_window = std::unique_ptr<IWindow>( IWindow::Create( wp ) );
		m_window->SetEventCallback( BIND_CB_FUNC( &Application::OnEvent ) );

		// Add UI debug layer
		m_imgui = new ImGuiLayer();
		PushOverlay( m_imgui );

		// Temp GL rendering
		glGenVertexArrays( 1, &m_vertexArray );
		glBindVertexArray( m_vertexArray );

		glGenBuffers( 1, &m_vertexBuffer );
		glBindBuffer( GL_ARRAY_BUFFER, m_vertexBuffer );

		float vertices[3 * 3] =
		{
			-0.5f, -0.5f, 0.f,
			0.5f, -0.5f, 0.f,
			0.f, 0.5f, 0.f
		};

		glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

		glEnableVertexAttribArray( 0 );
		glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), nullptr );

		glGenBuffers( 1, &m_indexBuffer );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer );

		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );
	}

	//----------------------------------------------//
	Application::~Application()
	{
		TE_ENGINE_LOG_INFO( "Application closing..." );
	}

	//----------------------------------------------//
	void Application::OnEvent( Event& Evt )
	{
		EventDispatch dispatch( Evt );
		dispatch.Dispatch<WindowCloseEvent>( BIND_CB_FUNC( &Application::OnWindowClose ) );
		dispatch.Dispatch<KeyPressedEvent>( BIND_CB_FUNC( &Application::OnKeyPressed ) );

		for ( auto it = m_layerStack.end(); it != m_layerStack.begin(); )
		{
			( *--it )->OnEvent( Evt );
			if ( Evt.bHandled )
			{
				break;
			}
		}
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
		if ( Evt.GetKeyCode() == TE_KEY_ESCAPE )
		{
			m_bRunning = false;
		}
		return true;
	}

	//----------------------------------------------//
	void Application::Run()
	{
		while ( m_bRunning )
		{
			glClearColor( 0.1f, 0.1f, 0.1f, 1.f );
			glClear( GL_COLOR_BUFFER_BIT );
			glBindVertexArray( m_vertexArray );
			glDrawElements( GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr );
			
			for ( Layer* layer : m_layerStack )
			{
				layer->OnUpdate();
			}

			// UI render			
			m_imgui->OnBegin();

			for ( Layer* layer : m_layerStack )
			{
				layer->OnImGuiRender();
			}
		
			m_imgui->OnEnd();

			m_window->Update();
		}
	}

	//----------------------------------------------//
	void Application::PushLayer( Layer* layer )
	{
		m_layerStack.PushLayer( layer );
	}

	//----------------------------------------------//
	void Application::PushOverlay( Layer* layer )
	{
		m_layerStack.PushOverlay( layer );
	}

	//----------------------------------------------//
	void Application::PopLayer( Layer* layer )
	{
		m_layerStack.PopLayer( layer );
	}

	//----------------------------------------------//
	void Application::PopOverlay( Layer* layer )
	{
		m_layerStack.PopOverlay( layer );
	}

}