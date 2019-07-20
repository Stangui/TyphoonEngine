#include "TyphoonPCH.h"
#include "Renderer.h"

#include "RenderCommand.h"
#include "VertexArray.h"

namespace TyphoonEngine
{
	namespace Renderers
	{

		void IRenderer::BeginScene()
		{

		}

		void IRenderer::EndScene()
		{

		}

		void IRenderer::Submit(const std::shared_ptr<VertexArray>& vArray)
		{
			vArray->Bind();
			RenderCommand::DrawIndexed(vArray);
		}
	}
}