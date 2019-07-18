#include "TyphoonPCH.h"
#include "Application.h"
#include "Windows/IWindow.h"
#include "Input/Input.h"
#include "Input/KeyCodes.h"
#include "Layers/Layer.h"
#include "UI/ImGuiLayer.h"
#include "glad/glad.h"
#include "Renderers/Renderer.h"
#include "Renderers/Shader.h"
#include "Renderers/Buffer.h"

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

		glGenVertexArrays( 1, &m_vertexArray );
		glBindVertexArray( m_vertexArray );

		float vertices[3 * 3] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
		 	 0.0f,  0.5f, 0.0f
		};

		Renderers::IRenderer::SetRenderAPI( Renderers::RenderAPI::OpenGL );
		m_vertexBuffer.reset( Renderers::IVertexBuffer::Create( vertices, sizeof( vertices ) ) );

		glEnableVertexAttribArray( 0 );
		glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), nullptr );

		glm::uint32 indices[3] = { 0, 1, 2 };
		m_indexBuffer.reset( Renderers::IIndexBuffer::Create( indices, sizeof(indices) / sizeof(glm::uint32) ) );
		
		const std::string vSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			void main()
			{
				gl_Position = vec4(a_Position, 1);	
			}
		)";

		const std::string fSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			void main()
			{
				color = vec4(0.8, 0.2, 0.3, 1.0);	
			}
		)";

		m_shader.reset( new Renderers::Shader(vSrc, fSrc) );
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
			
			m_shader->Bind();

			glBindVertexArray( m_vertexArray );
			glDrawElements( GL_TRIANGLES, m_indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr );

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