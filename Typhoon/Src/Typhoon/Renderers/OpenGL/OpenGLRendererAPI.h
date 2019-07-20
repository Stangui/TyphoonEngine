#pragma once

#include "Typhoon\Renderers\Renderer.h"

namespace TyphoonEngine
{
	namespace Renderers
	{
		class VertexArray;

		class OpenGLRendererAPI : public RendererAPI
		{

		public:

			OpenGLRendererAPI();
			~OpenGLRendererAPI();

			virtual void SetClearColour(const glm::vec4& colour) override;
			virtual void Clear() override;
			virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vArray) override;

		private:

			glm::vec4 m_colour;
		};

	}
}

