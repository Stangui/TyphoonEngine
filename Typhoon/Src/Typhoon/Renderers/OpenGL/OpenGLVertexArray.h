#pragma once

#include "Typhoon/Renderers/VertexArray.h"

namespace TyphoonEngine
{

	namespace Renderers
	{

		class OpenGLVertexArray : public VertexArray
		{
		
		public:
		
			OpenGLVertexArray();
			~OpenGLVertexArray() override;

			virtual void Bind() const override;
			virtual void Unbind() const override;

			virtual void AddVertexBuffer( const std::shared_ptr<IVertexBuffer>& vBuffer ) override;
			virtual void SetIndexBuffer( const std::shared_ptr<IIndexBuffer>& iBuffer ) override;

			virtual const std::vector<std::shared_ptr<IVertexBuffer>>& GetVertexBuffers() const { return m_vertexBuffers; }
			virtual const std::shared_ptr<IIndexBuffer>& GetIndexBuffer() const { return m_indexBuffer; }

		private:

			std::vector<std::shared_ptr<IVertexBuffer>> m_vertexBuffers;
			std::shared_ptr<IIndexBuffer> m_indexBuffer;
			glm::uint32 m_bufferId;
		};

	}
}

