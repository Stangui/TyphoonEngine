#pragma once

#include "RendererAPI.h"

namespace TyphoonEngine
{
	namespace Renderers
	{

		class RenderCommand
		{
		public:

			static void Clear()
			{
				m_rendererAPI->Clear();
			}

			static void SetClearColour(const glm::vec4& colour)
			{
				m_rendererAPI->SetClearColour(colour);
			}

			static void DrawIndexed(const std::shared_ptr<VertexArray>& vArray)
			{
				m_rendererAPI->DrawIndexed(vArray);
			}

		private:

			static RendererAPI* m_rendererAPI;
		};


	}
}

