#include "TyphoonEngine.h"

#include "imgui.h"

using namespace TyphoonEngine;

class ExampleLayer : public TyphoonEngine::Layer
{
public:

	ExampleLayer()
		: Layer("Test")
		, m_cameraPos( glm::vec3( 0.f ) )
		, m_squarePos( glm::vec3( 0.f ) )
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
			uniform mat4 u_transform;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_vpMat * u_transform * vec4(a_Position, 1.0);	
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

		float sqVertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.f, 0.f,
			 0.5f, -0.5f, 0.0f, 1.f, 0.f,
			 0.5f,  0.5f, 0.0f, 1.f, 1.f,
			-0.5f,  0.5f, 0.0f, 0.f, 1.f
		};

		std::shared_ptr<Renderers::IVertexBuffer> vBufferSq;
		vBufferSq.reset( Renderers::IVertexBuffer::Create( sqVertices, sizeof( sqVertices ) ) );
		vBufferSq->SetLayout(
			{
				{ Renderers::ShaderDataType::Float3, "a_Position" },
				{ Renderers::ShaderDataType::Float2, "a_TexCoord0" }
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
			layout(location = 1) in vec2 a_TexCoord0;

			out vec3 v_Position;
			out vec2 v_TexCoords;

			uniform mat4 u_vpMat;
			uniform mat4 u_transform;
			
			void main()
			{
				v_Position = a_Position;
				v_TexCoords = a_TexCoord0;
				gl_Position = u_vpMat * u_transform * vec4(a_Position, 1.0);	
			}
		)";

		const std::string fSrc2 = R"(
			#version 330 core

			layout(location = 0) out vec4 colour;

			in vec3 v_Position;
			in vec2 v_TexCoords;

			uniform sampler2D u_texture;

			void main()
			{
				colour = texture(u_texture, v_TexCoords);
			}
		)";

		m_blueShader.reset( new Renderers::Shader( vSrc2, fSrc2 ) );

		std::shared_ptr<Renderers::Texture> texture;
		texture.reset( new Renderers::Texture( "resources/test.png" ) );
		std::shared_ptr<Renderers::OpenGLTexture2D> glTexture;
		glTexture.reset( new Renderers::OpenGLTexture2D( texture ) );

		m_blueShader->AddTexture( glTexture, 0 );

		m_camera.reset( new Renderers::Camera() );
		m_camera->Init();
		m_camera->SetRotation( glm::vec3( 0.f, 0.f, 0.f ) );

		m_square = std::make_shared<Renderers::Renderable>( m_squareVA, m_blueShader );
		glm::mat4 scale = glm::scale( glm::mat4( 1.f ), glm::vec3( 1.3f ) );
		glm::mat4 trans = glm::translate( glm::mat4( 1.f ), m_squarePos ) * scale;
		m_square->SetTransform( trans );
		m_square->SetRenderQueue( 10 );

		r.AddRenderObject( m_square );

		m_triangle = std::make_shared<Renderers::Renderable>( m_triangleVA, m_vertexColorShader );
		trans = glm::translate( glm::mat4( 1.f ), glm::vec3( 0.f ) );
		m_triangle->SetTransform( trans );
		r.AddRenderObject( m_triangle );
	}

	virtual ~ExampleLayer() override
	{
	}
	
	void OnUpdate(float deltaTime)
	{
		static float cTime = 0.f;
		static glm::int32 fps = 0;

		cTime += deltaTime;
		++fps;

		/// FPS counter
		if ( cTime >= 1.f )
		{
			cTime = 0.f;
			m_fps = fps;
			fps = 0;
		}

		glm::mat4 trans = m_square->GetTransform();
		glm::mat4 rot = glm::rotate( glm::mat4( 1.f ), glm::radians( 90.f * deltaTime ), glm::vec3( 0.f, 0.f, 1.f ) );

		m_square->SetTransform( trans * rot );

		/// Handle input polling
		_HandleInput(deltaTime);

		/// Render 3D geometry
		_Render();
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

	void _Render()
	{
		Renderers::RenderCommand::SetClearColour( glm::vec4( 0.7f, 0.f, 0.7f, 1.f ) );
		Renderers::RenderCommand::Clear();

		r.RenderFrame( *m_camera );
	}

	void _HandleInput( float deltaTime )
	{
		// Camera
		if ( IInput::IsKeyPressed( TE_KEY_LEFT ) )
		{
			m_cameraPos.x -= 1.f * deltaTime;
		}
		if ( IInput::IsKeyPressed( TE_KEY_RIGHT ) )
		{
			m_cameraPos.x += 1.f * deltaTime;
		}
		if ( IInput::IsKeyPressed( TE_KEY_UP ) )
		{
			m_cameraPos.y += 1.f * deltaTime;
		}
		if ( IInput::IsKeyPressed( TE_KEY_DOWN ) )
		{
			m_cameraPos.y -= 1.f * deltaTime;
		}

		m_camera->SetPosition( m_cameraPos );
	}

	std::shared_ptr<Renderers::VertexArray> m_triangleVA;
	std::shared_ptr<Renderers::VertexArray> m_squareVA;
	std::shared_ptr<Renderers::Shader> m_vertexColorShader;
	std::shared_ptr<Renderers::Shader> m_blueShader;
	std::shared_ptr<Renderers::Camera> m_camera;
	
	glm::vec3 m_squarePos;
	glm::vec3 m_cameraPos;

	glm::int32 m_fps = 0;

	Renderers::RenderablePtr m_square;
	Renderers::RenderablePtr m_triangle;

	Renderers::IRenderer r;
};

//
// Sandbox client application
//
class SandboxApp : public TyphoonEngine::Application
{
public:

	SandboxApp(const TyphoonEngine::WindowProperties& props) : Application(props)
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
	TyphoonEngine::WindowProperties props;
	props.m_bVSync = false;
	props.m_dimensions = glm::ivec2(1600, 900);
	props.m_title = "Test";	
	props.m_type = TyphoonEngine::EWINDOW_TYPE::BorderWindowed;
	return new SandboxApp(props);
}