#pragma once

#include "Typhoon/Renderers/Buffer.h"

namespace TyphoonEngine
{
	namespace Renderers
	{

		class VertexArray
		{

		public:

			virtual ~VertexArray() {}

			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;

			virtual void AddVertexBuffer( const std::shared_ptr<IVertexBuffer>& vBuffer ) = 0;
			virtual void SetIndexBuffer( const std::shared_ptr<IIndexBuffer>& iBuffer ) = 0;

			virtual const std::vector<std::shared_ptr<IVertexBuffer>>& GetVertexBuffers() const = 0;
			virtual const std::shared_ptr<IIndexBuffer>& GetIndexBuffer() const = 0;

			static VertexArray* Create();

		};

	}
}