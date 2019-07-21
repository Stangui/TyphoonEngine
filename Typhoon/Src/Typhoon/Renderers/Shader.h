#pragma once

#include "glm/glm.hpp"
#include <string>

namespace TyphoonEngine
{
	namespace Renderers
	{
		class OpenGLTexture2D;

		class Shader
		{

		public:
			
			Shader( const std::string& vertexSrc, const std::string& fragmentSrc );
			virtual ~Shader();

			void Bind() const;
			void Unbind() const;

			void AddTexture( std::shared_ptr<OpenGLTexture2D>& texture, glm::uint32 slot );

			void UploadUniformMat4(const std::string& name, const glm::mat4& mat);

		private:

			glm::uint32 m_shaderId;
			glm::uint32 m_slot;
			std::shared_ptr<OpenGLTexture2D> m_texture;
		};

	}
}
