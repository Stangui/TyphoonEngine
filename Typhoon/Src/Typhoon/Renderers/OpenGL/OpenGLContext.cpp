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
		}

		//--------------------------------------------------------//
		void OpenGLContext::SwapBuffers()
		{
			glfwPollEvents();
			glfwSwapBuffers( m_window );
		}
	}
}