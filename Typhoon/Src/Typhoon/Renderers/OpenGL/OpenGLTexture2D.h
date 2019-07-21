#pragma once

#include "glm/glm.hpp"
#include "Typhoon/Renderers/Texture.h"

namespace TyphoonEngine
{
	namespace Renderers
	{

		class OpenGLTexture2D
		{
		public:

			OpenGLTexture2D( const std::shared_ptr<Texture>& texture );
			~OpenGLTexture2D();

			void Bind(glm::uint32 slot = 0) const;
			void Unbind() const;

			const std::shared_ptr<Texture>& GetTexture() const;

		private:

			glm::uint32 m_textureId;
			std::shared_ptr<Texture> m_texture;
		};

	}
}

