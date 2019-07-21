#include "TyphoonPCH.h"
#include "Application.h"
#include "IWindow.h"
#include "Input/Input.h"
#include "Input/KeyCodes.h"
#include "Layers/Layer.h"
#include "UI/ImGuiLayer.h"
#include "glad/glad.h"
#include "Renderers/Renderer.h"
#include "Renderers/RenderCommand.h"
#include "Renderers/Shader.h"
#include "Renderers/Buffer.h"
#include "Renderers/VertexArray.h"
#include "Renderers/Camera.h"

namespace TyphoonEngine
{

	Application* Application::s_instance = nullptr;

	///----------------------------------------------///
	Application::Application( const WindowProperties& props ) :
		m_bRunning( true )
		, m_bFocused( true )
		,m_lastFrameTime( 0.f )
	{
		TE_ASSERT( !s_instance, "Application already exists!" )
		/// Singleton
		s_instance = this;

		/// Create window
		m_window = std::unique_ptr<IWindow>( IWindow::Create( props ) );
		m_window->SetEventCallback( BIND_CB_FUNC( &Application::OnEvent ) );

		/// Add UI debug layer
		m_imgui = new ImGuiLayer();
		PushOverlay( m_imgui );

		m_timestep.reset( Timestep::Create() );
		TE_ASSERT( m_timestep, "Unable to create Platform Timestep!" );
	}
	 
	///----------------------------------------------///
	Application::~Application()
	{
		TE_ENGINE_LOG_INFO( "Application closing..." );
	}

	///----------------------------------------------///
	void Application::OnEvent( Event& Evt )
	{
		EventDispatch dispatch( Evt );
		dispatch.Dispatch<WindowCloseEvent>( BIND_CB_FUNC( &Application::OnWindowClose ) );

		for ( auto it = m_layerStack.end(); it != m_layerStack.begin(); )
		{
			( *--it )->OnEvent( Evt );
			if ( Evt.bHandled )
			{
				break;
			}
		}
	}

	///----------------------------------------------///
	bool Application::OnWindowClose( WindowCloseEvent& Evt )
	{
		QuitApp();
		return true;
	}

	///----------------------------------------------///
	void Application::Run()
	{
		while ( m_bRunning )
		{			
			float cTime = m_timestep->GetSeconds();
			float dTime = cTime - m_lastFrameTime;
			m_lastFrameTime = cTime;

			for ( Layer* layer : m_layerStack )
			{
				layer->OnUpdate( dTime );
			}

			//// UI render			
			m_imgui->OnBegin();

			for ( Layer* layer : m_layerStack )
			{
				layer->OnImGuiRender();
			}
		
			m_imgui->OnEnd();

			m_window->Update();
		}
	}

	///----------------------------------------------///
	void Application::PushLayer( Layer* layer )
	{
		m_layerStack.PushLayer( layer );
	}

	///----------------------------------------------///
	void Application::PushOverlay( Layer* layer )
	{
		m_layerStack.PushOverlay( layer );
	}

	///----------------------------------------------///
	void Application::PopLayer( Layer* layer )
	{
		m_layerStack.PopLayer( layer );
	}

	///----------------------------------------------///
	void Application::PopOverlay( Layer* layer )
	{
		m_layerStack.PopOverlay( layer );
	}

}