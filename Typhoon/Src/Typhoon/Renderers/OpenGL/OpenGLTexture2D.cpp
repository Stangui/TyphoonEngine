#include "TyphoonPCH.h"
#include "OpenGLTexture2D.h"
#include "Typhoon/Core.h"

#include "glad/glad.h"

namespace TyphoonEngine
{
	namespace Renderers
	{

		OpenGLTexture2D::OpenGLTexture2D(const std::shared_ptr<Texture>& texture)
			: m_texture(texture)
			,m_textureId(0)
		{
			if ( m_texture )
			{
				glGenTextures( 1, &m_textureId );
				glBindTexture( GL_TEXTURE_2D, m_textureId );
				// set the texture wrapping/filtering options (on the currently bound texture object)
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
				// load and generate t
				TE_ASSERT( m_texture->GetBuffer(), "No texture data!" );
				glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, m_texture->GetWidth(), m_texture->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, (const void*)m_texture->GetBuffer() );
				glGenerateMipmap( GL_TEXTURE_2D );
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

		OpenGLTexture2D::~OpenGLTexture2D()
		{
			glDeleteTextures( 1, &m_textureId );
		}

		const std::shared_ptr<Texture>& OpenGLTexture2D::GetTexture() const
		{
			return m_texture;
		}

		void OpenGLTexture2D::Bind( glm::uint32 slot ) const
		{
			glActiveTexture( GL_TEXTURE0 + slot );
			glBindTexture( GL_TEXTURE_2D, m_textureId );
		}

		void OpenGLTexture2D::Unbind() const
		{
			glBindTexture( GL_TEXTURE_2D, 0 );
		}

	}
}
