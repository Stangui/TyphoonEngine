#include "TyphoonPCH.h"
#include "Application.h"
#include "Windows/IWindow.h"
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

		// Add triangle mesh & shader
		m_triangleVA.reset(Renderers::VertexArray::Create());;

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 0.f, 1.f, 0.f, 1.f,
			0.5f, -0.5f, 0.0f, 1.f, 1.f, 0.f, 1.f,
			0.0f,  0.5f, 0.0f, 0.f, 1.f, 1.f, 1.f
		};

		std::shared_ptr<Renderers::IVertexBuffer> vBuffer;
		vBuffer.reset( Renderers::IVertexBuffer::Create(vertices, sizeof(vertices) ) );
		vBuffer->SetLayout(
			{
				{ Renderers::ShaderDataType::Float3, "a_Position" },
			{ Renderers::ShaderDataType::Float4, "a_Color" }
			}
		);

		m_triangleVA->AddVertexBuffer(vBuffer);

		glm::uint32 indices[3] = { 0, 1, 2 };
		std::shared_ptr<Renderers::IIndexBuffer> iBuffer;
		iBuffer.reset( Renderers::IIndexBuffer::Create(indices, sizeof(indices) / sizeof(glm::uint32) ) );
		m_triangleVA->SetIndexBuffer(iBuffer);

		const std::string vSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		const std::string fSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;	
			}
		)";

		m_vertexColorShader.reset(new Renderers::Shader(vSrc, fSrc));

		// Add triangle mesh & shader
		m_squareVA.reset(Renderers::VertexArray::Create());;

		float sqVertices[3 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 
			 0.5f, -0.5f, 0.0f, 
			 0.5f,  0.5f, 0.0f, 
			-0.5f,  0.5f, 0.0f 
		};

		std::shared_ptr<Renderers::IVertexBuffer> vBufferSq;
		vBufferSq.reset(Renderers::IVertexBuffer::Create(sqVertices, sizeof(sqVertices)));
		vBufferSq->SetLayout(
			{
				{ Renderers::ShaderDataType::Float3, "a_Position" }
			}
		);
		m_squareVA->AddVertexBuffer(vBufferSq);

		glm::uint32 sqIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Renderers::IIndexBuffer> iBufferSq;
		iBufferSq.reset( Renderers::IIndexBuffer::Create(sqIndices, sizeof(sqIndices) / sizeof(glm::uint32) ) );
		m_squareVA->SetIndexBuffer(iBufferSq);

		const std::string vSrc2 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		const std::string fSrc2 = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.6, 1.0);	
			}
		)";

		m_blueShader.reset(new Renderers::Shader(vSrc2, fSrc2));
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
			Renderers::RenderCommand::SetClearColour(glm::vec4(0.7f, 0.f, 0.7f, 1.f));
			Renderers::RenderCommand::Clear();
			
			Renderers::IRenderer::BeginScene();

			m_blueShader->Bind();
			Renderers::IRenderer::Submit(m_squareVA);

			m_vertexColorShader->Bind();
			Renderers::IRenderer::Submit(m_triangleVA);

			Renderers::IRenderer::EndScene();

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