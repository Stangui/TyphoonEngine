#pragma once

namespace TyphoonEngine
{
	namespace Renderers
	{

		class VertexArray;
		class Shader;

		class Renderable
		{

		public:

			Renderable( std::shared_ptr<VertexArray>& vArray, std::shared_ptr<Shader>& shader, glm::uint8 renderqueue = 128 );
			~Renderable();
			const std::shared_ptr<Shader>& GetShader() const;
			const std::shared_ptr<VertexArray>& GetVertexArray() const;
			void SetTransform( const glm::mat4& transform );
			const glm::mat4& GetTransform() const;
			void SetRenderQueue( const glm::uint8 id );
			const glm::uint8 GetRenderQueue() const;
			void SetEnabled(bool bEnable);
			const bool IsEnabled() const;

		private:

			std::shared_ptr<VertexArray> m_vertexArray;
			std::shared_ptr<Shader> m_shader;
			glm::mat4 m_transform;
			glm::uint8 m_renderQueue;
			bool m_bEnabled;
		};

		typedef std::shared_ptr<Renderable> RenderablePtr;
		typedef std::vector<RenderablePtr> RenderVec;

	}
}

