#pragma once

namespace TyphoonEngine
{
	namespace Renderers
	{
		class VertexArray;

		class RendererAPI
		{

		public:

			//
			// Rendering API enum
			//
			enum class API : unsigned char
			{
				None = 0, OpenGL, DirectX, Vulkan, Metal
			};

			virtual ~RendererAPI() {};

			virtual void SetClearColour(const glm::vec4& colour = glm::vec4(0.4, 0.4, 0.1, 1.0)) = 0;
			virtual void Clear() = 0;
			virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vArray) = 0;

			static API GetAPI() { return m_API; }
			
		private:

			static API m_API;
		};

	}
}

