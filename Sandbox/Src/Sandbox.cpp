#include "TyphoonEngine.h"

#include "imgui.h"

using namespace TyphoonEngine;

class ExampleLayer : public TyphoonEngine::Layer
{
public:

	ExampleLayer()
		: Layer("Test")
	{
		// Add triangle mesh & shader
		m_triangleVA.reset( Renderers::VertexArray::Create() );;

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 0.f, 1.f, 0.f, 1.f,
			0.5f, -0.5f, 0.0f, 1.f, 1.f, 0.f, 1.f,
			0.0f,  0.5f, 0.0f, 0.f, 1.f, 1.f, 1.f
		};

		std::shared_ptr<Renderers::IVertexBuffer> vBuffer;
		vBuffer.reset( Renderers::IVertexBuffer::Create( vertices, sizeof( vertices ) ) );
		vBuffer->SetLayout(
			{
				{ Renderers::ShaderDataType::Float3, "a_Position" },
			{ Renderers::ShaderDataType::Float4, "a_Color" }
			}
		);

		m_triangleVA->AddVertexBuffer( vBuffer );

		glm::uint32 indices[3] = { 0, 1, 2 };
		std::shared_ptr<Renderers::IIndexBuffer> iBuffer;
		iBuffer.reset( Renderers::IIndexBuffer::Create( indices, sizeof( indices ) / sizeof( glm::uint32 ) ) );
		m_triangleVA->SetIndexBuffer( iBuffer );

		const std::string vSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			uniform mat4 u_vpMat;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_vpMat * vec4(a_Position, 1.0);	
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

		m_vertexColorShader.reset( new Renderers::Shader( vSrc, fSrc ) );

		// Add triangle mesh & shader
		m_squareVA.reset( Renderers::VertexArray::Create() );;

		float sqVertices[3 * 4] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<Renderers::IVertexBuffer> vBufferSq;
		vBufferSq.reset( Renderers::IVertexBuffer::Create( sqVertices, sizeof( sqVertices ) ) );
		vBufferSq->SetLayout(
			{
				{ Renderers::ShaderDataType::Float3, "a_Position" }
			}
		);
		m_squareVA->AddVertexBuffer( vBufferSq );

		glm::uint32 sqIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Renderers::IIndexBuffer> iBufferSq;
		iBufferSq.reset( Renderers::IIndexBuffer::Create( sqIndices, sizeof( sqIndices ) / sizeof( glm::uint32 ) ) );
		m_squareVA->SetIndexBuffer( iBufferSq );

		const std::string vSrc2 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;
			uniform mat4 u_vpMat;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_vpMat * vec4(a_Position, 1.0);	
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

		m_blueShader.reset( new Renderers::Shader( vSrc2, fSrc2 ) );

		m_camera.reset( new Renderers::Camera() );
		m_camera->Init();
		m_camera->SetRotation( glm::vec3( 0.f, 0.f, 0.f ) );
	}

	virtual ~ExampleLayer() override
	{
	}

	void OnUpdate(float delaTime)
	{
		static float cTime = 0.f;
		static int fps = 0;

		cTime += delaTime;
		++fps;
		if ( cTime >= 1.f )
		{
			cTime = 0.f;
			m_fps = fps;
			fps = 0;
		}

		Renderers::RenderCommand::SetClearColour( glm::vec4( 0.7f, 0.f, 0.7f, 1.f ) );
		Renderers::RenderCommand::Clear();

		Renderers::IRenderer::BeginScene();

		m_blueShader->Bind();
		m_blueShader->UploadUniformMat4( "u_vpMat", m_camera->GetViewProjectionMatrix() );
		Renderers::IRenderer::Submit( m_squareVA );

		m_vertexColorShader->Bind();
		m_vertexColorShader->UploadUniformMat4( "u_vpMat", m_camera->GetViewProjectionMatrix() );
		Renderers::IRenderer::Submit( m_triangleVA );

		Renderers::IRenderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin( "Test" );
		ImGui::Text( "FPS: %d", m_fps );
		ImGui::End( );
	}
		
	void OnEvent( Event& Evt )
	{
		TyphoonEngine::EventDispatch Dispatcher( Evt );
		Dispatcher.Dispatch<TyphoonEngine::KeyPressedEvent>( BIND_CB_FUNC( &ExampleLayer::OnKeyPressed ) );
	}

	bool OnKeyPressed( TyphoonEngine::KeyPressedEvent& Evt )
	{
		if ( Evt.GetKeyCode() == TE_KEY_ESCAPE )
		{
			Application::Get().QuitApp();
		}
		return false;
	}

private:

	std::shared_ptr<Renderers::VertexArray> m_triangleVA;
	std::shared_ptr<Renderers::VertexArray> m_squareVA;
	std::shared_ptr<Renderers::Shader> m_vertexColorShader;
	std::shared_ptr<Renderers::Shader> m_blueShader;
	std::shared_ptr<Renderers::Camera> m_camera;

	int m_fps = 0;

};

//
// Sandbox client application
//
class SandboxApp : public TyphoonEngine::Application
{
public:

	SandboxApp() 
	{
		PushLayer( new ExampleLayer );
	}

	virtual ~SandboxApp() override
	{
	};

};

//
// Creates sandbox application
//
TyphoonEngine::Application* CreateApplication() 
{
	return new SandboxApp();
}