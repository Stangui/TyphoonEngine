#include "TyphoonPCH.h"
#include "Texture.h"

namespace TyphoonEngine
{
	namespace Renderers
	{

		Texture::Texture(const std::string& path) :
			m_textureId(0)
			,m_filePath(path)
			,m_buffer(nullptr)
			,m_width(0)
			,m_height(0)
			,m_bpp(0)
		{
			stdi_set_flip_vert
		}

		Texture::~Texture()
		{
		}

		const glm::int32 Texture::GetWidth() const
		{
			return m_width;
		}
		
		const glm::int32 Texture::GetHeight() const
		{
			return m_height;
		}
		
		const glm::int32 Texture::GetBits() const
		{
			return m_bpp;
		}
	}
}
