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

	// Type converter
	static GLenum ShaderDataTypeToOpenGLType( Renderers::ShaderDataType type )
	{
		switch ( type )
		{
		case Renderers::ShaderDataType::Int:
		case Renderers::ShaderDataType::Int2:
		case Renderers::ShaderDataType::Int3:
		case Renderers::ShaderDataType::Int4:	return GL_INT;
		case Renderers::ShaderDataType::Float:
		case Renderers::ShaderDataType::Float2:
		case Renderers::ShaderDataType::Float3:
		case Renderers::ShaderDataType::Float4:
		case Renderers::ShaderDataType::Mat3:
		case Renderers::ShaderDataType::Mat4:	return GL_FLOAT;
		case Renderers::ShaderDataType::Bool:	return GL_BOOL;
		}

		TE_ASSERT( false, "Unknown ShaderDataType!" );
		return 0;
	}

	//----------------------------------------------//
	Application::Application() :
		m_bRunning( true )
		, m_bFocused( true )
		,m_lastFrameTime( 0.f )
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

		m_timestep.reset( Timestep::Create() );
		TE_ASSERT( m_timestep, "Unable to create Platform Timestep!" );
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
		QuitApp();
		return true;
	}

	//----------------------------------------------//
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