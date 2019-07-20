#include "TyphoonPCH.h"
#include "RendererAPI.h"
#include "Typhoon\Core.h"

#include "OpenGL\OpenGLRendererAPI.h"

namespace TyphoonEngine
{
	namespace Renderers
	{

		RendererAPI::API RendererAPI::m_API = RendererAPI::API::OpenGL;
	}
}
