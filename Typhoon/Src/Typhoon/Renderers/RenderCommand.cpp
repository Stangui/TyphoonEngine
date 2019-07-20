#include "TyphoonPCH.h"
#include "RenderCommand.h"

#include "OpenGL/OpenGLRendererAPI.h"

namespace TyphoonEngine
{
	namespace Renderers
	{

		RendererAPI* RenderCommand::m_rendererAPI = new OpenGLRendererAPI();

	}
}