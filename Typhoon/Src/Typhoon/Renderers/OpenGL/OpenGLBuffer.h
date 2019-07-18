#pragma once

#include "Typhoon/Renderers/Buffer.h"
#include "glm/glm.hpp"

namespace TyphoonEngine
{

	namespace Renderers
	{
		class OpenGLVertexBuffer : public IVertexBuffer
		{

		public:

			OpenGLVertexBuffer( const float* vertices, glm::uint32 size );
			virtual ~OpenGLVertexBuffer() override;

			virtual void Bind() const override;
			virtual void Unbind() const override;

		private:

			glm::uint32 m_renderId;
		};

		class OpenGLIndexBuffer : public IIndexBuffer
		{

		public:

			OpenGLIndexBuffer( const glm::uint32* indices, glm::uint32 count );
			virtual ~OpenGLIndexBuffer() override;

			virtual void Bind() const override;
			virtual void Unbind() const override;

			virtual const glm::uint32 GetCount() const override;

		private:

			glm::uint32 m_renderId;
			glm::uint32 m_count;
		};
	}
}
