#pragma once

#include "glm/glm.hpp"
#include <string>

namespace TyphoonEngine
{
	namespace Renderers
	{

		class Shader
		{

		public:
			
			Shader( const std::string& vertexSrc, const std::string& fragmentSrc );
			virtual ~Shader();

			void Bind() const;
			void Unbind() const;

		private:

			glm::uint32 m_shaderId;
		};

	}
}
