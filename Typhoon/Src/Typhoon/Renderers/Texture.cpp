#include "TyphoonPCH.h"
#include "Texture.h"

#include "Typhoon/Core.h"

#include "stb_image.h"

namespace TyphoonEngine
{
	namespace Renderers
	{

		//------------------------------------------------------//
		Texture::Texture(const std::string& path) : 
			m_filePath(path)
			,m_width(0)
			,m_height(0)
			,m_bpp(0)
			,m_buffer(nullptr)
		{
			stbi_set_flip_vertically_on_load( true );
			m_buffer = stbi_load( path.c_str(), &m_width, &m_height, &m_bpp, 0 );
			TE_ASSERT( m_buffer, "Failed to load texture {0]", path.c_str() );
		}

		//------------------------------------------------------//
		Texture::~Texture()
		{
			stbi_image_free( m_buffer );
		}

		//------------------------------------------------------//
		const glm::int32 Texture::GetWidth() const
		{
			return m_width;
		}

		//------------------------------------------------------//
		const glm::int32 Texture::GetHeight() const
		{
			return m_height;
		}

		//------------------------------------------------------//
		const glm::int32 Texture::GetBits() const
		{
			return m_bpp;
		}

		//------------------------------------------------------//
		const glm::uint8* Texture::GetBuffer() const
		{
			return m_buffer;
		}
		
	}
}