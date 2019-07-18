#pragma once

#include "glm/glm.hpp"

namespace TyphoonEngine
{
	namespace Renderers
	{

		//
		// Generic vertex buffer class
		//
		class IVertexBuffer
		{

		public:

			virtual ~IVertexBuffer() {};

			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;

			static IVertexBuffer* Create( const float* vertices, glm::uint32 size );
		};

		//
		// Generic index buffer class
		//
		class IIndexBuffer
		{

		public:

			virtual ~IIndexBuffer() {};

			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;

			virtual const glm::uint32 GetCount() const = 0;

			static IIndexBuffer* Create( const glm::uint32* indices, glm::uint32 count );
		};

	}
}