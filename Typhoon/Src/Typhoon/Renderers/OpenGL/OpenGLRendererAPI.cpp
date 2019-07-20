#include "TyphoonPCH.h"
#include "OpenGLRendererAPI.h"

#include "Typhoon/Renderers/Buffer.h"
#include "Typhoon/Renderers/VertexArray.h"
#include "Typhoon/Renderers/Renderer.h"
#include "glad/glad.h"

namespace TyphoonEngine
{
	namespace Renderers
	{

		OpenGLRendererAPI::OpenGLRendererAPI()
		{

		}
		
		OpenGLRendererAPI::~OpenGLRendererAPI()
		{

		}

		void OpenGLRendererAPI::SetClearColour(const glm::vec4& colour)
		{
			m_colour = colour;
		}

		void OpenGLRendererAPI::Clear()
		{
			glClearColor(m_colour.r, m_colour.g, m_colour.b, m_colour.a);
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		}

		void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vArray)
		{
			glDrawElements(GL_TRIANGLES, vArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		}

	}
}
