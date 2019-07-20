#include "TyphoonPCH.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "Typhoon/Renderers/OpenGL/OpenGLVertexArray.h"

namespace TyphoonEngine
{
	namespace Renderers
	{

		VertexArray* VertexArray::Create()
		{
			switch ( IRenderer::GetRenderAPI() )
			{
			case RenderAPI::OpenGL: return new OpenGLVertexArray();
			}

			TE_ASSERT( false, "Unsupported API!" );
			return nullptr;
		}

	}
}
