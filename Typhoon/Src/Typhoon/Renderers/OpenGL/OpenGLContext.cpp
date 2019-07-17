#include "TyphoonPCH.h"
#include "OpenGLContext.h"
#include "Typhoon/Core.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace TyphoonEngine
{
	namespace Renderers
	{
		
		//--------------------------------------------------------//
		OpenGLContext::OpenGLContext( GLFWwindow* win ) : m_window( win )
		{
		}

		//--------------------------------------------------------//
		OpenGLContext::~OpenGLContext()
		{
		}

		//--------------------------------------------------------//
		void OpenGLContext::Init()
		{
			glfwMakeContextCurrent( m_window );
			int status = gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress );
			TE_ASSERT( status, "Failed to initialise GLAD" )

			TE_ENGINE_LOG_INFO( "-----------------------------------------" );
			TE_ENGINE_LOG_INFO( "OpenGL Renderer" );
			TE_ENGINE_LOG_INFO( "    Vendor: {0}", glGetString( GL_VENDOR ) );
			TE_ENGINE_LOG_INFO( "    Renderer: {0}", glGetString( GL_RENDERER ) );
			TE_ENGINE_LOG_INFO( "    Version: {0}", glGetString( GL_VERSION ) );
			TE_ENGINE_LOG_INFO( "-----------------------------------------" );
		}

		//--------------------------------------------------------//
		void OpenGLContext::SwapBuffers()
		{
			glfwPollEvents();
			glfwSwapBuffers( m_window );
		}
	}
}